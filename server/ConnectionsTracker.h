//
// Created by ahmednagga19 on 07/11/18.
//

#ifndef HTTP_CLIENT_SERVER_CONNECTIONSTRACKER_H
#define HTTP_CLIENT_SERVER_CONNECTIONSTRACKER_H


#include <mutex>
#include <set>

class ConnectionsTracker {

private:
    /* A set containing each process alongside with its last request time. */
    std::set<std::pair<int, int>> processes_tracker;

public:
    static void update_last_transaction_time(int pid);
    static int get_least_recently_used_pid();
    static bool insert_process(int pid);
};


#endif //HTTP_CLIENT_SERVER_CONNECTIONSTRACKER_H
