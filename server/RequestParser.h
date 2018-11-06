//
// Created by ahmed on 11/6/18.
//

#ifndef HTTP_SOCKET_PROGRAMMING_REQUESTPARSER_H
#define HTTP_SOCKET_PROGRAMMING_REQUESTPARSER_H

#include "Request.h"
#include "GetRequest.h"

class RequestParser
{
    public:
        RequestParser(std::string message);
        Request* parse();
};

#endif //HTTP_SOCKET_PROGRAMMING_REQUESTPARSER_H
