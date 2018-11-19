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


using namespace std;

const int BUFFER_SIZE = 1024;

mutex ConnectionHandler::lock;

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
//         handle_request(buffer_copy, socket_fd);
        std::thread first (&ConnectionHandler::handle_request, this, buffer_copy, socket_fd);
        first.detach();
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


int sendall(char *buf, int *len, int s)
{
    size_t total = 0;        // how many bytes we've sent
    int  bytes_left = *len; // how many we have left to send
    size_t  n;

    while(total < *len) {
        n = send(s, buf+total, bytes_left, 0);
        if (n == -1) { break; }
        total += n;
        bytes_left -= n;
    }

    *len = total; // return number actually sent here

    return n==-1?-1:0; // return -1 onm failure, 0 on success
}

void ConnectionHandler::handle_request(char buffer_copy[], int socket_fd)
{
    lock.lock();
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
        message_lines.pop_back();
    }
    printf("Biuffer : %s\n", buffer_copy);
    // Get the file path
    RequestParser request_parser = RequestParser(message_lines);
    Request* request = request_parser.parse();

    string resources_path = "../resources";
    string file_path = resources_path + request->get_file_name();
    cout << file_path << endl;

    char* found_response = "HTTP/1.1 200 OK\r\n";
    char* not_found_response = "HTTP/1.1 404 NOT_FOUND\r\n";

    FileReader* file_reader = new FileReader();
    FileWriter* file_writer = new FileWriter();

    printf("File Name %s \n", request->get_file_name().c_str());

    // Check GET or POST ...
    if(request->get_request_type() == "GET")
    {
        if(file_reader->file_exist(file_path))
        {
            string content = file_reader->read_file(file_path);
            char *mod_content = &content[0u];
//            found_response += content;
            // return found_response
//            cout << "===SIZE=====" << found_response.length() << endl;
//            char *cstr = new char[found_response.length() + 1];
//            strcpy(cstr, found_response.c_str());
//            int length = found_response.length();
//            sendall(cstr, &length, socket_fd);
//            send(socket_fd, cstr, (30000), 0);
            cout << "---Found Response: " << found_response << endl;
            cout << "---Content: " << mod_content << endl;
            SocketHandler::send(socket_fd, found_response, mod_content);
        }
        else
        {
            // return not_found_response
            cout << not_found_response << endl;
//            printf("Again : %s\n", not_found_response.c_str());
//            send(socket_fd, not_found_response.c_str(),
//                 strlen(not_found_response.c_str()), 0);

        }
    }
    else if (request->get_request_type() == "POST")
    {
        file_writer->write_file(file_path, request->get_content());
        // return found_response
        cout << found_response << endl;
//        send(socket_fd, found_response.c_str(), strlen(found_response.c_str()), 0);
    }

    // handler thread goes here
    cout << "Ended Handler" << endl;
    lock.unlock();
}