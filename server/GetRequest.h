//
// Created by ahmed on 11/6/18.
//

#include <string>
#include "HttpHeader.h"
#include "Request.h"

#ifndef HTTP_SOCKET_PROGRAMMING_GETREQUEST_H
#define HTTP_SOCKET_PROGRAMMING_GETREQUEST_H

class GetRequest: public Request
{
    public:
        GetRequest(HttpHeader header);
//        void set_content(std::string content) override;
//        std::string get_content() override;
};

#endif //HTTP_SOCKET_PROGRAMMING_GETREQUEST_H
