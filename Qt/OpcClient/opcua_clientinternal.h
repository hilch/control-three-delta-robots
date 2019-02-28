/*************************************************************************************
 *
 * SimpleOPUA
 *
 * Simple C++ wrapper for open62541 https://open62541.org/
 *
 * 2018/06/06 hilchenbachc
 *
 * ************************************************************************************/

#ifndef OPCUA_CLIENTINTERNAL_H
#define OPCUA_CLIENTINTERNAL_H

extern "C" {
#include "open62541.h"
}

#include <vector>
#include <string>


#include <map>
#include <set>
#include <functional>
#include <algorithm>
#include <tuple>

using std::string;
using std::vector;
using std::function;

namespace SimpleOPCUA {

/* internal struct for handling callbacks */

struct OPCUA_ClientInternal
{
    UA_StatusCode status;
    UA_ClientConfig configuration;
    UA_Client *uaClient;
    string serverUrl;
    bool connected;
    struct MonitoredItem
    {
        UA_UInt32 subscriptionId;
        function<void(string,int64_t)> callback;
    };
    std::set<UA_UInt32> subscriptionIds;
    std::map<UA_UInt32, MonitoredItem > monitoredItems;

    /* callbacks */
    static void subscriptionStatusChangeNotification(UA_Client *client, UA_UInt32 subId, void* subContext, UA_StatusChangeNotification *notification );
    static void deleteSubscriptionCallback(UA_Client *client, UA_UInt32 subId, void* subContext );

    static void dataChangeNotificationCallback(UA_Client *client, UA_UInt32 subId, void *subContext, UA_UInt32 monId, void *monContext, UA_DataValue *value);
    static void eventNotificationCallback(UA_Client *client, UA_UInt32 subId, void *subContext, UA_UInt32 monId, void *monContext, size_t nEventFields, UA_Variant *eventFields);
    static void deleteMonitoredItemCallback(UA_Client *client, UA_UInt32 subId, void *subContext, UA_UInt32 monId, void *monContext);

    /* helper */
    static string getVariantValue(UA_Variant &variant );
    static bool setVariantValue(UA_Variant &variant, string value);
    static bool getNodeId( UA_NodeId& nodeId, string xml_notation );
};

}

#endif // OPCUA_CLIENTINTERNAL_H
