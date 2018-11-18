//
// Created by hisham on 18/11/18.
//

#include "SocketHandler.h"

#include <string.h>
#include <sys/socket.h>
#include <algorithm>
#include <iostream>

using namespace std;

const int MESSAGE_SIZE = 1024;

int SocketHandler::send(int socket, char *header, char *data) {


   ::send(socket, header, strlen(header), 0);


    int index = 0;
    int length = strlen(data);

    char* global_buffer = "";

    // Header
    strcpy(global_buffer, header);
    cout << "GLOBAL BUFFER1: " << global_buffer << endl;
    ::send(socket, global_buffer, strlen(global_buffer), 0);

    // Data
    strcpy(global_buffer, data);
    cout << "GLOBAL BUFFER2: " << global_buffer << endl;
//    ::send(socket, global_buffer, strlen(global_buffer), 0);


//    ::send(socket, header, strlen(header), 0);

    while (index < length)
    {
        int data_size = min(MESSAGE_SIZE, length - index);
        int data_sent = ::send(socket, global_buffer + index, strlen(global_buffer), 0);
//        int data_sent = ::send(socket, data+index, data_size, 0);
        index += MESSAGE_SIZE;

        if(data_sent != data_size || data_sent == -1)
            return 0;
    }

    string termination_string = "\r\r\r\n\n\r";
//    ::send(socket, termination_string.c_str(), strlen(termination_string.c_str()), 0);

    return 1;
}

int SocketHandler::send(int socket, char *header) {
    size_t data_size = strlen(header);
    ssize_t data_sent = ::send(socket, header, data_size, 0);
    return data_sent != data_size || data_sent == -1;
}

bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

void SocketHandler::recieve(int socket, std::string &buffer) {

    // Receiving Data
    string data = "";
    int bytesRead = 1;

    while(bytesRead > 0)
    {
        char received_buffer[MESSAGE_SIZE] = {0};

        cout << "---Received Buffer(Before): " << received_buffer << endl;
        bytesRead = recv(socket, received_buffer, MESSAGE_SIZE, 0);

        if(has_suffix(string(received_buffer), "\r\r\r\n\n\r"))
        {
            cout << "Termination Must have occured here!!!" << endl;
        }

        data += string(received_buffer);
        cout << "---Received Buffer(After): " << received_buffer << endl;
    }

    cout << "Terminated" << endl;

   buffer = data;
}
