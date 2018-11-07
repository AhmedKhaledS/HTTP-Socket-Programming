//
// Created by ahmednagga19 on 07/11/18.
//

#ifndef HTTP_CLIENT_SERVER_CONNECTIONSTRACKER_H
#define HTTP_CLIENT_SERVER_CONNECTIONSTRACKER_H


#include <mutex>

class ConnectionsTracker {
private:
    static int connections_count;
    static std::mutex lock;
public:
    static void increment_connections();
    static void decrement_connections();
    static bool check_connections();
};


#endif //HTTP_CLIENT_SERVER_CONNECTIONSTRACKER_H
