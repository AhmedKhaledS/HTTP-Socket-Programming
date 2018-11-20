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
#include <unistd.h>
#include <thread>
#include "RequestBuilder.h"
#include "response/ResponseHandler.h"
#include "../socketServices/SocketHandler.h"

const int MAX_BUFF_SIZE = 50000;

using namespace std;


mutex WebClient::lock;


FILE *WebClient::get_file(std::string file_name, int socket_fd) {
    return nullptr;
}

void WebClient::post_file(std::string file_path, int socket_fd) {

}

std::vector<std::string> WebClient::receive_response(int socket) {
    vector<string> responses;
    SocketHandler::recieve(socket, responses);
    return responses;
}

void WebClient::send_requests(std::string requests_file_name, std::string host_name, int port_number,
                              CONNECTION_TYPE connection_type) {
    vector<RequestCommand> requests = parse_request_commands_file(requests_file_name);
    vector<string> request_messages = build_request_messages(requests);
    if (connection_type == CONNECTION_TYPE::NON_PERSISTENT)
        send_requests_non_persistent(request_messages, requests, host_name, port_number);
    else if (connection_type == CONNECTION_TYPE::PERSISTENT)
        send_requests_persistent(request_messages, requests, host_name, port_number);
    else
        send_requests_pipelined(request_messages, requests, host_name, port_number);
}

std::vector<std::string> WebClient::build_request_messages(std::vector<RequestCommand> &commands) {
    vector<string> messages;
    RequestBuilder request_builder = RequestBuilder();
    for (RequestCommand &command : commands)
    {
        messages.push_back(request_builder.build_request_message(command));
        cout << "DEBUG: " << command.getData() << '\n';
    }
    return messages;
}

std::vector<RequestCommand> WebClient::parse_request_commands_file(std::string file_name) {
    FileReader* file_reader = new FileReader();
    string content = file_reader->read_file(file_name);
    vector<string> request_lines = split_string(content, "\n");
    vector<RequestCommand> request_commands;
    for (auto request_line : request_lines)
    {
        RequestCommand command = parse_request_command_line(request_line);
        request_commands.push_back(command);
    }
    return request_commands;
}

RequestCommand WebClient::parse_request_command_line(std::string request_line) {
    vector<string> args = split_string(request_line, " ");
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
    request_command.setHost_name(args[2]);
    request_command.setFile_name(args[1]);
    if (args.size() == 4) {
        request_command.setPort_number(stoi(args[3]));
    }
    return request_command;
}

void WebClient::send_requests_non_persistent(std::vector<std::string> request_messages, std::vector<RequestCommand> commands,
        std::string host_name, int port_number)
{
    int commands_index = 0;
    for (string message : request_messages)
    {
        int socket = connect(host_name, port_number);
        char msg[1024] = {0};
        strcpy(msg, message.c_str());
        cout << "Length: " << commands[commands_index].getData().length() << "\n";
        SocketHandler::send(socket, msg, commands[commands_index].getData());
        vector<string> response = receive_response(socket);
        ResponseHandler response_handler = ResponseHandler();
        response_handler.handle_response(response[0], commands[commands_index].getType(), commands[commands_index].getFile_name());
        cout << "RESPONSE FOR " << message << "\n====\n" << response[0] << endl;
        commands_index++;
        close(socket);
    }
}

void WebClient::send_requests_persistent(std::vector<std::string> request_messages, std::vector<RequestCommand> commands,
                                         std::string host_name, int port_number)
{
    int socket = connect(host_name, port_number);
    int commands_index = 0;
    for (string message : request_messages)
    {
        char msg[1024] = {0};
        strcpy(msg, message.c_str());
        SocketHandler::send(socket, msg, commands[commands_index].getData());
        vector<string> response = receive_response(socket);
        ResponseHandler response_handler = ResponseHandler();
        response_handler.handle_response(response[0], commands[commands_index].getType(), commands[commands_index].getFile_name());
        cout << "RESPONSE FOR " << message << "\n====\n" << response[0] << endl;
        commands_index++;
    }
    close(socket);
}


void WebClient::send_requests_pipelined(std::vector<std::string> request_messages, std::vector<RequestCommand> commands,
                                        std::string host_name, int port_number)
{
    int socket = connect(host_name, port_number);
    int commands_index = 0;
    vector<thread*> request_threads;
    for (string message : request_messages)
    {
        char msg[1024] = {0};
        strcpy(msg, message.c_str());
        SocketHandler::send(socket, msg, commands[commands_index].getData());

    }
    for (size_t i = 0; i < request_messages.size(); i++)
    {
        cout << "Resp " << i << " ";
        for (string resp : receive_response(socket))
        {
            ResponseHandler response_handler = ResponseHandler();
            response_handler.handle_response(resp, commands[i].getType(), commands[i].getFile_name());
        }
    }
    close(socket);
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
