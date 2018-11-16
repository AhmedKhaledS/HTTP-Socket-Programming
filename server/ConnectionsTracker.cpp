//
// Created by ahmednagga19 on 07/11/18.
//

#include "ConnectionsTracker.h"

using namespace std;

const int MAX_CONNECTIONS = 100;

int ConnectionsTracker::connections_count = 0;
mutex ConnectionsTracker::lock;

void ConnectionsTracker::increment_connections()
{
    ConnectionsTracker::lock.lock();
    ConnectionsTracker::connections_count++;
    ConnectionsTracker::lock.unlock();
}

void ConnectionsTracker::decrement_connections()
{
    ConnectionsTracker::lock.lock();
    ConnectionsTracker::connections_count--;
    ConnectionsTracker::lock.unlock();
}

bool ConnectionsTracker::check_connections()
{
    ConnectionsTracker::lock.lock();
    if (ConnectionsTracker::connections_count > MAX_CONNECTIONS)
    {
        ConnectionsTracker::connections_count--;
        ConnectionsTracker::lock.unlock();
        return false;
    }
    ConnectionsTracker::lock.unlock();
    return true;
}
