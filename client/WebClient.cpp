//
// Created by ahmed on 11/6/18.
//

#include <sstream>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include "WebClient.h"
#include "../fileServices/FileReader.h"
#include <arpa/inet.h>

#include "StringUtils.h"

#define MAX_BUFF_SIZE 1024

using namespace std;



FILE *WebClient::get_file(std::string file_name, int socket_fd) {
    return nullptr;
}

void WebClient::post_file(std::string file_path, int socket_fd) {

}

void WebClient::send_requests(std::string requests_file_name, std::string host_name, int port_number,
                              CONNECTION_TYPE connection_type) {
    vector<RequestCommand> requests = parse_request_commands_file(requests_file_name);
    send_requests_non_persistent(requests, host_name, port_number);
}

std::vector<RequestCommand> WebClient::parse_request_commands_file(std::string file_name) {
    FileReader* file_reader = new FileReader();
    string content = file_reader->read_file(file_name);
    vector<string> request_lines = split_string(content, '\n');
    vector<RequestCommand> request_commands;
    for (auto request_line : request_lines)
    {
        RequestCommand command = parse_request_command_line(request_line);
        request_commands.push_back(command);
    }
    return request_commands;
}

RequestCommand WebClient::parse_request_command_line(std::string request_line) {
    vector<string> args = split_string(request_line, ' ');
    if (args.size() < 3)
    {
        perror("INVALID NUMBER OF ARGUMENTS");
        return RequestCommand();
    }
    RequestCommand request_command = RequestCommand();
    if (args[0] != "POST" && args[0] != "GET")
    {
        perror("INVALID REQUEST TYPE");
    }
    else
    {
        request_command.setType(args[0] == "GET" ? REQ_TYPE::GET : REQ_TYPE::POST);
    }
    request_command.setFile_name(args[1]);
    request_command.setHost_name(args[2]);
    if (args.size() == 4) {
        request_command.setPort_number(stoi(args[3]));
    }
    return request_command;
}

void
WebClient::send_requests_non_persistent(std::vector<RequestCommand> commands, std::string host_name, int port_number) {
    char buffer[MAX_BUFF_SIZE] = {0};
//    for (auto command : commands)
    {
        /// TODO use which hostname and port number !
        int socket = connect(host_name, port_number);
        /// TODO : Fill in buffer
        char* request = "GET /kurose_ross/interactive/quotation1.htm HTTP/1.0\r\n"
                        "Host: gaia.cs.umass.edu\r\n"
                        "\r\n";
        send(socket, request, strlen(request), 0);
        /// TODO : close Socket
    }
}

void WebClient::send_requests_persistent(std::vector<RequestCommand> commands, std::string host_name, int port_number) {

}

void WebClient::send_requests_pipelined(std::vector<RequestCommand> commands, std::string host_name, int port_number) {

}

int WebClient::connect(std::string hostname, int port_number) {
    struct sockaddr_in address;
    int sock = 0;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_number);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, hostname.c_str(), &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (::connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    return sock;
}
