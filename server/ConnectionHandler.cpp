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
#include <thread>
#include "RequestParser.h"



using namespace std;

const int BUFFER_SIZE = 1024;

ConnectionHandler::ConnectionHandler() {}


void ConnectionHandler::handle(int socket_fd)
{
    boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, "SharedMemory");
    shared_vector *running_processes = segment.find<shared_vector>("shared_vector").first;
    int process_index = get_process_index(running_processes);

    while (true)
    {
        // read request -> parse request -> create request handler in a thread
        char buffer[BUFFER_SIZE] = {0};
        read(socket_fd, buffer, BUFFER_SIZE);
        char buffer_copy[BUFFER_SIZE];
        strcpy(buffer_copy, buffer);

        // Updating the time for the last request in this connection.
        (*running_processes)[process_index].second = static_cast<long long>(time(NULL));

        // Here we create the handler threads.
         handle_request(buffer_copy);
        //        std::thread first (handle_request, buffer_copy);
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
    cout << "--Reached Handler" << endl;

    // Convert the buffer to vector of strings
    std::stringstream ss(buffer_copy);
    std::string to;
    std::vector<string> message_lines;
    if (buffer_copy != NULL)
    {
        while(std::getline(ss,to,'\n')){
           message_lines.push_back(to);
        }
    }


    // Get the file path
    RequestParser request_parser = RequestParser(message_lines);
    Request* request = request_parser.parse();

    string resources_path = "../resources";
    string file_path = resources_path + request->get_file_name();
    cout << file_path << endl;

    // Check GET or POST ...

    // handler thread goes here
    cout << "Ended Handler" << endl;
}

