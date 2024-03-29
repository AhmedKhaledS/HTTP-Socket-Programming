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
#include <mutex>
#include "RequestParser.h"
#include "../fileServices/FileReader.h"
#include "../fileServices/FileWriter.h"
#include "../socketServices/SocketHandler.h"
#include "../client/StringUtils.h"
#include <signal.h>



using namespace std;

const int BUFFER_SIZE = 1024;


mutex ConnectionHandler::lock;

ConnectionHandler::ConnectionHandler()
{
    allowPost = false;
}

bool isConnected(int socket_fd)
{
    int optval;
    socklen_t optlen = sizeof(optval);
    int res = getsockopt(socket_fd, SOL_SOCKET, SO_ERROR, &optval,  &optlen);
    if (optval == 0 && res == 0)  return true;
    return false;
}


void ConnectionHandler::handle(int socket_fd)
{
    boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, "SharedMemory");
    shared_vector *running_processes = segment.find<shared_vector>("shared_vector").first;
    int process_index = get_process_index(running_processes);

    while (true)
    {
//        if(!isConnected(socket_fd))
//            exit(0);
        std::vector<string> requests;
        SocketHandler::recieve(socket_fd, requests);
        // Updating the time for the last request in this connection.
        (*running_processes)[process_index].second = static_cast<long long>(time(NULL));

        // Here we create the handler threads.
        for (string request : requests)
        {
            cout << "Requests : " << request.c_str() << endl;
            std::thread request_handler (&ConnectionHandler::handle_request, this, request, socket_fd);
            request_handler.detach();
        }
    }
}

int ConnectionHandler::get_process_index(shared_vector *running_processes)
{
    for(int i = 0; i < running_processes->size(); i++)
    {
        if ((*running_processes)[i].first == (int) getpid())
            return i;
    }

}


void ConnectionHandler::handle_request(string buffer, int socket_fd)
{
    const char* buffer_copy = buffer.c_str();
    cout << "--Reached Handler" << endl;
    printf("Buffer : %s\n", buffer_copy);

    // Convert the buffer to vector of strings
    std::stringstream ss(buffer_copy);
    std::string to;
    std::vector<string> message_lines;
    if (buffer_copy != NULL)
    {
        message_lines = split_string(buffer, "\r\n");
    }

    // Get the file path
    RequestParser request_parser = RequestParser(message_lines);
    Request* request = request_parser.parse();

    string resources_path = "../resources";
    string file_path = resources_path + request->get_file_name();
    char* found_response = "HTTP/1.1 200 OK\r\n";
    char* not_found_response = "HTTP/1.1 404 NOT_FOUND\r\n";

    FileReader* file_reader = new FileReader();
    FileWriter* file_writer = new FileWriter();


    // Check GET or POST ...
    if (request->get_request_type() == "GET")
    {
        if (file_reader->file_exist(file_path))
        {
            string content = file_reader->read_file(file_path);
            cout << "---Found Response: " << found_response << endl;
            cout << "---Content: " << content << endl;
//            char* found_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\n";
            SocketHandler::send(socket_fd, found_response, content);
        }
        else
        {
            // return not_found_response
            cout << not_found_response << endl;
            SocketHandler::send(socket_fd, not_found_response, "");
        }
    }
    else if (request->get_request_type() == "POST")
    {
        if(request->get_content() == "")
        {
            allowPost = true;
            cout << "Sending ACK to client to send data";
            SocketHandler::send(socket_fd, found_response, "");
        }
        else if(allowPost)
        {
            allowPost = false;
            cout << "file path: " << file_path << " Content: " << request->get_content() << "\n";
            file_writer->write_file(file_path, request->get_content());
            // return found_response
            cout << found_response << endl;
            SocketHandler::send(socket_fd, found_response, "");
        }

    }

    // handler thread goes here
    cout << "Ended Handler" << endl;
}