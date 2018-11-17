//
// Created by ahmednagga19 on 07/11/18.
//

#include "ConnectionHandler.h"

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>



using namespace std;

const int BUFFER_SIZE = 1024;

ConnectionHandler::ConnectionHandler() {}


void ConnectionHandler::handle(int socket_fd)
{
    boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, "SharedMemory");
    shared_vector *running_processes = segment.find<shared_vector>("shared_vector").first;
    int process_index = get_process_index(running_processes);
    int count = 1;
    while (true)
    {
        // read request -> parse request -> create request handler in a thread
        cout << count++ << endl;
        char buffer[BUFFER_SIZE] = {0};
        read(socket_fd, buffer, BUFFER_SIZE);
        char buffer_copy[BUFFER_SIZE];
        strcpy(buffer_copy, buffer);
        handle_request(buffer_copy);

        // Updating the time for the last request in this connection.
        (*running_processes)[process_index].second = static_cast<long long>(time(NULL));
//        for (auto process : *running_processes)
//        {
//            std::cout << "--In Child -- PID: " << process.first << " | Last Request Time: " << process.second << std::endl;
//        }
        // Here we create the handler threads.


        printf("\n Message : %s\n", buffer);
    }
    return;
}

int ConnectionHandler::get_process_index(shared_vector *running_processes)
{
    for(int i = 0; i < running_processes->size(); i++)
    {
        if ((*running_processes)[i].first == (int) getpid())
            return i;
    }

}

void ConnectionHandler::handle_request(char buffer_copy[])
{
    // RequestParser request_parser = RequestParser(buffer);
    // request_parser.parse();

    // handler thread goes here
}

