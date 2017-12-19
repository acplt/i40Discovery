#include <iostream>
#include <boost/asio/write.hpp>
#include <boost/asio/io_service.hpp>
#include "ds_types.h"

using namespace std;
using namespace boost::asio;

class CommunicationEndpoint {
public:
    virtual void request(REQUEST_HEADER requestHeader) = 0;
    virtual void response(RESPONSE_HEADER responseHeader) = 0;
    virtual void startServer() = 0;
    CommunicationEndpoint() {
        cout<<"created comm endpoint!"<<endl;
    }
};

class DiscoveryServer_CommunicationEndpoint : public CommunicationEndpoint {
public:
    boost::asio::io_service io_service;

    void request(REQUEST_HEADER requestHeader) {};
    void response(RESPONSE_HEADER responseHeader) {};
    void startServer();
    DiscoveryServer_CommunicationEndpoint() {
        cout << "starting discovery server..." << endl;
    }
};

void DiscoveryServer_CommunicationEndpoint::startServer() {

};


int main() {
    DiscoveryServer_CommunicationEndpoint *ds = new DiscoveryServer_CommunicationEndpoint();

    return 0;
}