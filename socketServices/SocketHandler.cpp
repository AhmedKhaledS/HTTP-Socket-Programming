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

const string termination_string = "END";

int SocketHandler::send(int socket, char *header, string data) {

    int offset = 0;
//            strlen(header);
    int length = data.size() + strlen(header) + termination_string.length();
    int bytes_left = length;

    string global_buffer = header + data + termination_string;
    cout << "Global Buffer " << global_buffer << endl;
//    char* global_buffer = (char*) malloc(sizeof(char) * 2048);
//    int sent_bytes = ::send(socket, global_buffer.c_str(), strlen(header), 0);
//    bytes_left -= sent_bytes;

    while (bytes_left > 0)
    {
        cout << "Index: " << offset << " bytes left: " << bytes_left << endl;
        int data_sent = ::send(socket, global_buffer.c_str() + offset, bytes_left, 0);
        offset += data_sent;
        bytes_left -= data_sent;

        if (data_sent == -1)
            return 0; // Failure
    }
    return 1; // success
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

    while (bytesRead > 0)
    {
        char received_buffer[MESSAGE_SIZE] = {0};

        cout << "---Received Buffer(Before): " << received_buffer << endl;
        bytesRead = recv(socket, received_buffer, MESSAGE_SIZE, 0);

        for (int i = 0; i < bytesRead; i++) {
            data.push_back(received_buffer[i]);
        }
        cout << "---Received Buffer(After): " << data << endl;
        if (has_suffix(string(data), termination_string))
            break;
    }

    data = data.substr(0, data.length() - termination_string.length());

    cout << "Terminated" << endl;

    buffer = data;
}
