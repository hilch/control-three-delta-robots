/*************************************************************************************
 *
 * SimpleOPUA
 *
 * Simple C++ wrapper for open62541 https://open62541.org/
 *
 * 2018/06/06 hilchenbachc
 *
 * ************************************************************************************/

#ifndef OPCUA_CLIENT_H
#define OPCUA_CLIENT_H

#include <string>
#include <vector>
#include <functional>

namespace SimpleOPCUA {

struct OPCUA_ClientInternal;

class OPCUA_Client
{
public:
    typedef struct DateTime{
        uint16_t nanoSec;
        uint16_t microSec;
        uint16_t milliSec;
        uint16_t sec;
        uint16_t min;
        uint16_t hour;
        uint16_t day;
        uint16_t month;
        uint16_t year;
    } DateTime;

    OPCUA_Client( );
    ~OPCUA_Client();


    /* stati */
    bool connected(void);
    std::string lastError(void);

    /* methods */
    bool connectTo( std::string url);
    bool disconnect(void);
    bool getNamespaceIndex( const std::string namespaceUri, uint16_t &namespaceIndex );
    bool readValueAttribute(const std::string &identifier, std::string &value  );
    bool writeValueAttribute(const std::string &identifier, const std::string &value );
    bool browse(const std::string &rootIdentifier, std::vector<std::string> &identifier, bool extendedInfo = false );
    bool addSubscription(uint32_t &subscriptionId, double requestedPublishingInterval = 500.0 );
    bool removeSubscription( uint32_t subscriptionId );
    bool addMonitoredItem(const std::string identifier, uint32_t subscriptionId , uint32_t &monitoredItemId, std::function<void(std::string, int64_t)> dataChangeCallback, double samplingInterval = 250);
    bool removeMonitoredItem( uint32_t monitoredItemId );
    bool callMethod( const std::string &contextIdentifier, const std::string &methodIdentifier, std::vector<double> inargs, std::vector<std::string>&outargs);
    void runAsync(void);
    static DateTime toDateTime( const std::string time );


private:
    OPCUA_ClientInternal *internal;
    friend OPCUA_ClientInternal;
};


}


#endif // OPCUA_CLIENT_H

