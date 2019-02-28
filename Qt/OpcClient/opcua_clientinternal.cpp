/*************************************************************************************
 *
 * SimpleOPUA
 *
 * Simple C++ wrapper for open62541 https://open62541.org/
 *
 * 2018/06/06 hilchenbachc
 *
 * ************************************************************************************/

#include "opcua_clientinternal.h"
#include "opcua_client.h"
#include <sstream>
#include <regex>

using namespace SimpleOPCUA;

template <class Container>
void split(const std::string& str, Container& cont, char delim = ' ')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}


void OPCUA_ClientInternal::subscriptionStatusChangeNotification(UA_Client *client, UA_UInt32 subId, void* subContext, UA_StatusChangeNotification *notification )
{
    std::ignore = client;
    std::ignore = subId;
    std::ignore = subContext;
    std::ignore = notification;
}

void OPCUA_ClientInternal::deleteSubscriptionCallback(UA_Client *client, UA_UInt32 subId, void* subContext )
{
    std::ignore = client;
    std::ignore = subId;
    std::ignore = subContext;
}


void OPCUA_ClientInternal::dataChangeNotificationCallback(UA_Client *client, UA_UInt32 subId, void *subContext, UA_UInt32 monId, void *monContext, UA_DataValue *value)
{
    std::ignore = client;
    std::ignore = subId;
    std::ignore = subContext;
    std::ignore = monId;
    std::ignore = monContext;
    std::ignore = value;

    uint64_t sourceTimeStamp = 0;
    if( value->hasSourceTimestamp )
        sourceTimeStamp = value->sourceTimestamp;

    OPCUA_Client *uaClient = static_cast<OPCUA_Client*>(subContext);

    MonitoredItem &monItem = uaClient->internal->monitoredItems.at(monId);
    monItem.callback(getVariantValue(value->value), sourceTimeStamp);

}

void OPCUA_ClientInternal::eventNotificationCallback(UA_Client *client, UA_UInt32 subId, void *subContext, UA_UInt32 monId, void *monContext, size_t nEventFields, UA_Variant *eventFields)
{
    std::ignore = client;
    std::ignore = subId;
    std::ignore = subContext;
    std::ignore = monId;
    std::ignore = monContext;
    std::ignore = nEventFields;
    std::ignore = eventFields;
}

void OPCUA_ClientInternal::deleteMonitoredItemCallback(UA_Client *client, UA_UInt32 subId, void *subContext, UA_UInt32 monId, void *monContext)
{
    std::ignore = client;
    std::ignore = subId;
    std::ignore = subContext;
    std::ignore = monId;
    std::ignore = monContext;

}

std::string OPCUA_ClientInternal::getVariantValue(UA_Variant &variant)
{
    string result;

    if( UA_Variant_isScalar(&variant))
    {
        if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_BYTE]) )
        {
            result = std::to_string(*(UA_Byte*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_SBYTE]) )
        {
            result = std::to_string(*(UA_SByte*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_BOOLEAN]) )
        {
            result = std::to_string(*(UA_Boolean*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_INT16]) )
        {
            result = std::to_string(*(UA_Int16*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_UINT16]) )
        {
            result = std::to_string(*(UA_UInt16*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_INT32]) )
        {
            result = std::to_string(*(UA_Int32*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_UINT32]) )
        {
            result = std::to_string(*(UA_UInt32*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_INT64]) )
        {
            result = std::to_string(*(UA_Int64*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_UINT64]) )
        {
            result = std::to_string(*(UA_UInt64*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_DATETIME]) )
        {
            result = std::to_string(*(UA_Int64*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_FLOAT]) )
        {
            result = std::to_string(*(UA_Float*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_DOUBLE]) )
        {
            result = std::to_string(*(UA_Double*)variant.data);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_STRING]) )
        {
            UA_String *p = (UA_String*) variant.data;
            result.assign( (char*) p->data, p->length);
        }
        else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]) )
        {
            string locale;
            UA_LocalizedText *lt = (UA_LocalizedText*) variant.data;
            result.assign((char*) lt->text.data, lt->text.length);
            locale.assign((char*) lt->locale.data, lt->locale.length);
            if( !locale.empty() )
                result += "/" + locale;
        }
    }
    else  /* Arrays */
    {
        if( UA_Variant_hasArrayType(&variant, &UA_TYPES[UA_TYPES_BYTE]))
        {
            result.assign( (char*)variant.data, variant.arrayLength );
        }
    }

    return result;
}




bool OPCUA_ClientInternal::setVariantValue(UA_Variant &variant, std::string value)
{
    if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_BYTE]) )
    {
        UA_Byte v = std::stoi(value);
        UA_Variant_setScalarCopy(&variant,&v,&UA_TYPES[UA_TYPES_BYTE]);
        return true;
    }
    else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_SBYTE]) )
    {
        UA_SByte v = std::stoi(value);
        UA_Variant_setScalar(&variant,&v,&UA_TYPES[UA_TYPES_SBYTE]);
    }
    else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_BOOLEAN]) )
    {
        UA_Boolean v = std::stoi(value);
        UA_Variant_setScalarCopy(&variant,&v,&UA_TYPES[UA_TYPES_BOOLEAN]);
    }
    else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_INT16]) )
    {
        UA_Int16 v = std::stoi(value);
        UA_Variant_setScalarCopy(&variant,&v,&UA_TYPES[UA_TYPES_INT16]);
    }

    else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_UINT16]) )
    {
        UA_UInt16 v = std::stoi(value);
        UA_Variant_setScalarCopy(&variant,&v,&UA_TYPES[UA_TYPES_UINT16]);
    }

    else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_INT32]) )
    {
        UA_Int32 v = std::stoi(value);
        UA_Variant_setScalarCopy(&variant,&v,&UA_TYPES[UA_TYPES_INT32]);
    }
    else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_UINT32]) )
    {
        UA_UInt32 v = std::stoi(value);
        UA_Variant_setScalarCopy(&variant,&v,&UA_TYPES[UA_TYPES_UINT32]);
    }
    else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_INT64]) )
    {
        UA_Int64 v = std::stol(value);
        UA_Variant_setScalarCopy(&variant,&v,&UA_TYPES[UA_TYPES_INT64]);
    }
    else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_UINT64]) )
    {
        UA_UInt64 v = std::stol(value);
        UA_Variant_setScalarCopy(&variant,&v,&UA_TYPES[UA_TYPES_UINT64]);
    }
    else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_FLOAT]) )
    {
        UA_Float v = std::stol(value);
        UA_Variant_setScalarCopy(&variant,&v,&UA_TYPES[UA_TYPES_FLOAT]);
        return true;
    }
    else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_DOUBLE]) )
    {
        UA_Double v = std::stol(value);
        UA_Variant_setScalarCopy(&variant,&v,&UA_TYPES[UA_TYPES_DOUBLE]);
        return true;

    }
    else if( UA_Variant_hasScalarType(&variant, &UA_TYPES[UA_TYPES_STRING]) )
    {
        UA_String v;
        v.data = (UA_Byte*) value.c_str();
        v.length = strlen(value.c_str());

        UA_Variant_setScalarCopy(&variant,&v,&UA_TYPES[UA_TYPES_STRING]);
        return true;

    }
    return false;
}


/* get NodeId from OPC UA XML notation

Examples:
ns=2;s=MyTemperature
namespace index 2, string identifier

i=2045
namespace index 0, numeric identifier

ns=1;g=09087e75-8e5e-499b-954f-f2a9603db28a
namespace index 1, GUID identifier

ns=1;b=M/RbKBsRVkePCePcx24oRA=='
namespace index 1, Opaque/ByteString identifier

*/


bool OPCUA_ClientInternal::getNodeId(UA_NodeId &nodeId, std::string xml_notation)
{
    std::regex rxns(R"((ns\s*=\s*)([[:digit:]]{1,5}))");
    std::regex rxs(R"((s\s*=\s*)(.+))");
    std::regex rxi(R"((i\s*=\s*)([[:digit:]]{1,9}))");

    int namespaceIndex=-1;
    uint32_t numericIdentifier = 0xffffffff;
    string stringIdentifier = "";

    vector<string> fields;
    split( xml_notation, fields, ';');
    for( string field : fields )
    {

        std::smatch smatch;

        if( std::regex_search( field, smatch, rxns ))
        {
            namespaceIndex = std::stoi(smatch[2]);
        }
        else if( std::regex_search( field, smatch, rxs ))
        {
            stringIdentifier = smatch[2];
        }
        else if( std::regex_search( field, smatch, rxi ))
        {
            numericIdentifier = std::stol(smatch[2]);
        }
    }

    if( !stringIdentifier.empty() )
    {
          nodeId = UA_NODEID_STRING_ALLOC( namespaceIndex, stringIdentifier.c_str() );
    }
    else
    {
        nodeId = UA_NODEID_NUMERIC(namespaceIndex,numericIdentifier);
    }
    return true;
}

