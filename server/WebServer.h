//
// Created by ahmed on 11/6/18.
//

#ifndef HTTP_SOCKET_PROGRAMMING_WEBSERVER_H
#define HTTP_SOCKET_PROGRAMMING_WEBSERVER_H

#include "ConnectionHandler.h"

#include <vector>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <string>
#include <cstdlib> //std::system
#include <sys/shm.h>


class WebServer
{
    public :
        WebServer(int port_number);
        void start();
    private :
        std::vector<int> child_pids;
        int port_number;
        int connections_count = 0;
        boost::interprocess::managed_shared_memory *segment;

        shared_vector * initialize_shared_memory();
        void kill_connection_process(shared_vector* running_process);
};

#endif //HTTP_SOCKET_PROGRAMMING_WEBSERVER_H
