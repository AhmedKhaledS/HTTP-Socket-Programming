//
// Created by ahmed on 11/6/18.
//

#include <string>
#include "HttpHeader.h"

#ifndef HTTP_SOCKET_PROGRAMMING_GETREQUEST_H
#define HTTP_SOCKET_PROGRAMMING_GETREQUEST_H

#endif //HTTP_SOCKET_PROGRAMMING_GETREQUEST_H

class GetRequest
{
    private:
        HttpHeader request_header;
        std::string file_name;
    public:
        GetRequest();
        void set_request_header(HttpHeader header);
        HttpHeader get_http_header();
        void set_file_name(std::string file_name);
        std::string get_file_name();
};