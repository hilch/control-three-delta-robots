/*************************************************************************************
 *
 * SimpleOPUA
 *
 * Simple C++ wrapper for open62541 https://open62541.org/
 *
 * 2018/06/06 hilchenbachc
 *
 * ************************************************************************************/

#include "opcua_client.h"
#include "open62541.h"

#include <set>
#include <map>
#include <algorithm>
#include <tuple>
#include <cstring>
#include <iostream>
#include <iomanip>

#include "opcua_clientinternal.h"

using namespace SimpleOPCUA;
using std::string;
using std::vector;
using std::function;




/* -----------------------------------------------------------------------------
 *
 *  ctor
 *
 * ------------------------------------------------------------------------------
*/


OPCUA_Client::OPCUA_Client() : internal( new OPCUA_ClientInternal )
{
    internal->configuration = UA_ClientConfig_default;
    internal->uaClient = UA_Client_new(internal->configuration);
}

/* -----------------------------------------------------------------------------
 *
 *  dtor
 *
 * ------------------------------------------------------------------------------
*/


SimpleOPCUA::OPCUA_Client::~OPCUA_Client()
{
    UA_Client_delete(internal->uaClient);
    delete internal;
}


/* -----------------------------------------------------------------------------
 *
 *  connection
 *
 * ------------------------------------------------------------------------------
*/


bool OPCUA_Client::connected()
{
    return ( internal->connected );
}

bool OPCUA_Client::connectTo(std::string url)
{
    internal->serverUrl = url;
    internal->status = UA_Client_connect(internal->uaClient, url.c_str()  );

    if( internal->status == UA_STATUSCODE_GOOD )
    {
        internal->connected = true;
        return true;
    }
    internal->connected = false;
    return false;

}

bool OPCUA_Client::disconnect()
{
    internal->status = UA_Client_disconnect(internal->uaClient);
    return true;
}


/* -----------------------------------------------------------------------------
 *
 *  namespace
 *
 * ------------------------------------------------------------------------------
*/

bool OPCUA_Client::getNamespaceIndex(const std::string namespaceUri, uint16_t &namespaceIndex)
{
    UA_String uri;
    uri.data = (UA_Byte*) namespaceUri.c_str();
    uri.length = namespaceUri.length();

    internal->status = UA_Client_NamespaceGetIndex( internal->uaClient, &uri, &namespaceIndex );

    if( internal->status == UA_STATUSCODE_GOOD )
    {
        return true;
    }
    return false;
}

/* -----------------------------------------------------------------------------
 *
 *  read operations
 *
 * ------------------------------------------------------------------------------
*/


bool OPCUA_Client::readValueAttribute(const std::string &identifier, std::string &value  )
{
    /* Read the value attribute of the node. UA_Client_readValueAttribute is a
    * wrapper for the raw read service available as UA_Client_Service_read. */
    bool result = false;
    UA_NodeId nodeId;
    OPCUA_ClientInternal::getNodeId( nodeId, identifier);

    UA_Variant variant; /* Variants can hold scalar values and arrays of any type */
    UA_Variant_init(&variant);

    internal->status = UA_Client_readValueAttribute( internal->uaClient, nodeId, &variant);
    if (internal->status == UA_STATUSCODE_GOOD )
    {
        value = OPCUA_ClientInternal::getVariantValue(variant);
        result = true;
    }
    /* Clean up */
    UA_Variant_deleteMembers(&variant);
    if( nodeId.identifierType == UA_NODEIDTYPE_STRING )
        UA_NodeId_deleteMembers(&nodeId);
    return result;
}



/* -----------------------------------------------------------------------------
 *
 *  write operations
 *
 * ------------------------------------------------------------------------------
*/

bool OPCUA_Client::writeValueAttribute( const string &identifier, const string &value)
{
    UA_NodeId nodeId;
    OPCUA_ClientInternal::getNodeId( nodeId, identifier);
    bool result = false;


    UA_Variant variant; /* Variants can hold scalar values and arrays of any type */
    UA_Variant_init(&variant);

    internal->status = UA_Client_readValueAttribute( internal->uaClient, nodeId, &variant);

    if ( internal->status == UA_STATUSCODE_GOOD )
    {
        OPCUA_ClientInternal::setVariantValue(variant, value);

        internal->status = UA_Client_writeValueAttribute( internal->uaClient, nodeId, &variant );
        if ( internal->status == UA_STATUSCODE_GOOD )
        {
            result = true;
        }
    }
    /* Clean up */
    UA_Variant_deleteMembers(&variant);
    if( nodeId.identifierType == UA_NODEIDTYPE_STRING )
        UA_NodeId_deleteMembers(&nodeId);

    return result;
}





/* -----------------------------------------------------------------------------
 *
 *  Browsing
 *
 * ------------------------------------------------------------------------------
*/

bool OPCUA_Client::browse(const std::string &rootIdentifier,  vector<string> &identifier , bool extendedInfo)
{
    bool result = false;

    UA_NodeId nodeId;
    OPCUA_ClientInternal::getNodeId( nodeId, rootIdentifier);


    UA_BrowseRequest req;
    UA_BrowseRequest_init(&req);

    req.requestedMaxReferencesPerNode = 0;
    req.nodesToBrowse = UA_BrowseDescription_new();
    req.nodesToBrowseSize = 1;
    req.nodesToBrowse[0].nodeId = nodeId;
    req.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; //return everything

    UA_BrowseResponse resp = UA_Client_Service_browse( internal->uaClient, req);

    internal->status = resp.responseHeader.serviceResult;

    if ( internal->status == UA_STATUSCODE_GOOD )
    {

        for (size_t i = 0; i < resp.resultsSize; ++i)
        {
            UA_BrowseResult* browseResult = &resp.results[i];
            internal->status = browseResult->statusCode;

            if( internal->status == UA_STATUSCODE_GOOD )
            {
                for (size_t j = 0; j < browseResult->referencesSize; ++j)
                {
                    UA_ReferenceDescription* ref = &browseResult->references[j];
                    string idString = "ns=" + std::to_string(ref->nodeId.nodeId.namespaceIndex);

                    switch( ref->nodeId.nodeId.identifierType )
                    {

                        case UA_NODEIDTYPE_NUMERIC:
                            idString = idString + ";i=" + std::to_string( ref->nodeId.nodeId.identifier.numeric);
                        break;

                        case UA_NODEIDTYPE_GUID:
                            idString = idString + ";g=";
                        break;

                        case UA_NODEIDTYPE_STRING:
                        {
                            string s;
                            s.assign( reinterpret_cast<const char*>(ref->nodeId.nodeId.identifier.string.data), ref->nodeId.nodeId.identifier.string.length);
                            idString = idString + ";s=" + s;
                        }
                        break;

                        case UA_NODEIDTYPE_BYTESTRING:
                        {
                            string s;
                            s.assign( reinterpret_cast<const char*>(ref->nodeId.nodeId.identifier.string.data), ref->nodeId.nodeId.identifier.string.length);
                            idString = idString + ";b=" + s;
                        }
                        break;

                    }

                    string nodeClass;

                    if( extendedInfo )
                    {

                        switch( ref->nodeClass )
                        {
                            case UA_NODECLASS_VARIABLE:
                                nodeClass += "Variable";
                            break;

                            case UA_NODECLASS_METHOD:
                                nodeClass +="Method";
                            break;

                            case UA_NODECLASS_DATATYPE:
                                nodeClass += "Datatype";
                            break;

                            case UA_NODECLASS_OBJECT:
                                nodeClass += "Object";
                            break;

                            case UA_NODECLASS_OBJECTTYPE:
                                nodeClass += "Objecttype";
                            break;

                            case UA_NODECLASS_VARIABLETYPE:
                                nodeClass += "Variabletype";
                            break;

                            case UA_NODECLASS_REFERENCETYPE:
                                nodeClass = "Referencetype";
                            break;

                            case UA_NODECLASS_UNSPECIFIED:
                                nodeClass = "Unspecified";
                            break;

                            case UA_NODECLASS_VIEW:
                                nodeClass = "View";
                            break;

                            case __UA_NODECLASS_FORCE32BIT:
                            break;
                        }

                        string browseName;
                        browseName.assign( reinterpret_cast<const char*>(ref->browseName.name.data), ref->browseName.name.length );

                        idString = idString + ";NodeClass=" + nodeClass + ";BrowseName=" + browseName;

                    }
                    identifier.push_back(idString);

                }
                result = true;
            }
            else
            {
                break;
            }
        }
    }


    UA_BrowseRequest_deleteMembers(&req);
    UA_BrowseResponse_deleteMembers(&resp);
    return result;

}


/* -----------------------------------------------------------------------------
 *
 *  Subscriptions
 *
 * ------------------------------------------------------------------------------
*/


bool OPCUA_Client::addSubscription(uint32_t &subscriptionId, double requestedPublishingInterval)
{
    UA_CreateSubscriptionRequest request = UA_CreateSubscriptionRequest_default();
    request.requestedPublishingInterval = requestedPublishingInterval;
    UA_CreateSubscriptionResponse response = UA_Client_Subscriptions_create( internal->uaClient, request, this,
                                                                             internal->subscriptionStatusChangeNotification,
                                                                             internal->deleteSubscriptionCallback
                                                                             );

    internal->status = response.responseHeader.serviceResult;

    if (internal->status == UA_STATUSCODE_GOOD )
    {
        auto ret = internal->subscriptionIds.insert(response.subscriptionId);
        subscriptionId = *ret.first;
        return true;
    }
    return false;

}



bool OPCUA_Client::removeSubscription(uint32_t subscriptionId)
{
    if ( internal->subscriptionIds.find(subscriptionId) == internal->subscriptionIds.end() )
        return false;

    internal->status = UA_Client_Subscriptions_deleteSingle( internal->uaClient, subscriptionId);

    if (internal->status == UA_STATUSCODE_GOOD )
    {
        internal->subscriptionIds.erase(subscriptionId);  /* remove from subscription list */

        auto it = internal->monitoredItems.begin();  /* remove all elements from monitored Item list */
        while ( it != internal->monitoredItems.end() )
        {
            if ( it->second.subscriptionId == subscriptionId )
                it = internal->monitoredItems.erase(it);
            else
                ++it;
        }
        return true;
    }
    else
    {
        return false;
    }
}



bool OPCUA_Client::addMonitoredItem(const std::string identifier, uint32_t subscriptionId, uint32_t &monitoredItemId, std::function<void(std::string, int64_t)> dataChangeCallback, double samplingInterval)
{
    if ( internal->subscriptionIds.find(subscriptionId) == internal->subscriptionIds.end() )
    {
        internal->status = UA_STATUSCODE_BADNOSUBSCRIPTION;
        return false;
    }

    UA_NodeId nodeId;
    OPCUA_ClientInternal::getNodeId( nodeId, identifier);

    UA_MonitoredItemCreateRequest request = UA_MonitoredItemCreateRequest_default(nodeId);
    request.requestedParameters.samplingInterval = samplingInterval;

    UA_MonitoredItemCreateResult response = UA_Client_MonitoredItems_createDataChange( internal->uaClient, subscriptionId,
                                                                                       UA_TIMESTAMPSTORETURN_SOURCE, request, this,
                                                                                       internal->dataChangeNotificationCallback,
                                                                                       internal->deleteMonitoredItemCallback   );
    internal->status = response.statusCode;

    UA_NodeId_deleteMembers(&nodeId);

    if (internal->status == UA_STATUSCODE_GOOD )
    {
        OPCUA_ClientInternal::MonitoredItem item;
        item.subscriptionId = subscriptionId;
        item.callback = dataChangeCallback;

        internal->monitoredItems.insert( std::pair<UA_UInt32, OPCUA_ClientInternal::MonitoredItem>(response.monitoredItemId, item)  );
        monitoredItemId = response.monitoredItemId;
        return true;
    }
    return false;

}


bool OPCUA_Client::removeMonitoredItem(uint32_t monitoredItemId)
{
    if ( monitoredItemId != 0 )
    {

        return true;
    }
    else
        return false;

}

/* -----------------------------------------------------------------------------
 *
 * call a method
 *
 * ------------------------------------------------------------------------------
*/


bool OPCUA_Client::callMethod(const std::string &contextIdentifier, const std::string &methodIdentifier, std::vector<double> inargs, std::vector<std::string> &outargs)
{
    UA_NodeId methodId;
    OPCUA_ClientInternal::getNodeId( methodId, methodIdentifier);
    bool result = false;

    UA_NodeId nodeId;
    OPCUA_ClientInternal::getNodeId( nodeId, contextIdentifier);  /* test */

    std::vector<UA_Variant> in;

    size_t inargCnt = inargs.size();
    UA_Variant *input = new UA_Variant[inargCnt];
    for( size_t i = 0; i < inargCnt; ++i )
    {
        UA_Variant_init(&input[i]);
        UA_Variant_setScalarCopy( &input[i], &inargs.at(i), &UA_TYPES[UA_TYPES_DOUBLE] );
    }

    size_t outargCnt = 0;
    UA_Variant *output = new UA_Variant[10];

    internal->status = UA_Client_call( internal->uaClient,  nodeId, methodId, inargCnt, input, &outargCnt, &output );

    if ( internal->status == UA_STATUSCODE_GOOD )
    {
        UA_Array_delete( output, outargCnt, &UA_TYPES[UA_TYPES_VARIANT]);
    }
    else {
        std::cout << "Status: " << std::setbase(16) << internal->status << std::endl;
    }
    /* Clean up */
    for( size_t i = 0; i < inargCnt; ++i )
    {
        UA_Variant_deleteMembers(&input[i]);
    }
    if( nodeId.identifierType == UA_NODEIDTYPE_STRING )
        UA_NodeId_deleteMembers(&nodeId);

    return result;
}




/* -----------------------------------------------------------------------------
 *
 *  handling cyclic refresh and callbacks
 *
 * ------------------------------------------------------------------------------
*/


void OPCUA_Client::runAsync()
{
    UA_Client_runAsync( internal->uaClient, 100);


    UA_ClientState state = UA_Client_getState(internal->uaClient);

    switch ( state )
    {
        case UA_CLIENTSTATE_DISCONNECTED: // The client is disconnected
            internal->connected = false;
        break;

        case UA_CLIENTSTATE_CONNECTED: // A TCP connection to the server is open
            internal->connected = true;
        break;

        case UA_CLIENTSTATE_SECURECHANNEL: // A SecureChannel to the server is open
            internal->connected = true;
        break;

        case UA_CLIENTSTATE_SESSION: // A session with the server is open
            internal->connected = true;
        break;

        case UA_CLIENTSTATE_SESSION_RENEWED: // A session with the server is open (renewed)
            internal->connected = true;
        break;

        default: // unknown
        break;

    }
}



/* -----------------------------------------------------------------------------
 *
 *  handling errors
 *
 * ------------------------------------------------------------------------------
*/


string OPCUA_Client::lastError()
{
    return( UA_StatusCode_name(internal->status) );
}


/* -----------------------------------------------------------------------------
 *
 *  helpers
 *
 * ------------------------------------------------------------------------------
*/

OPCUA_Client::DateTime OPCUA_Client::toDateTime(const std::string time)
{
   UA_DateTime dt = std::stoll(time);
   UA_DateTimeStruct dts = UA_DateTime_toStruct(dt);
   DateTime result;
   result.year = dts.year;
   result.month = dts.month;
   result.day = dts.day;
   result.hour = dts.hour;
   result.min = dts.min;
   result.sec = dts.sec;
   result.milliSec = dts.milliSec;
   result.microSec = dts.microSec;
   result.nanoSec = dts.nanoSec;

   return result;
}
