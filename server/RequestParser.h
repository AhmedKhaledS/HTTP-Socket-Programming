//
// Created by ahmed on 11/6/18.
//

#ifndef HTTP_SOCKET_PROGRAMMING_REQUESTPARSER_H
#define HTTP_SOCKET_PROGRAMMING_REQUESTPARSER_H

#include <vector>
#include <map>
#include "Request.h"
#include "Request.h"

class RequestParser
{
    private:
        std::vector<std::string> request_message;
        std::string request_type;
        std::map<std::string, std::string> header_attributes;
        std::string requested_file_name;
        std::string connection_type;

        Request* get_specified_request();
    public:
        RequestParser(std::vector<std::string> message);
        Request* parse();
        std::string get_request_type();
        std::string get_request_file_name();
        std::string get_connection_type();
};

#endif //HTTP_SOCKET_PROGRAMMING_REQUESTPARSER_H
