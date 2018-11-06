//
// Created by ahmed on 11/6/18.
//

#include "GetRequest.h"
#include "Request.h"

#ifndef HTTP_SOCKET_PROGRAMMING_POSTREQUEST_H
#define HTTP_SOCKET_PROGRAMMING_POSTREQUEST_H

class PostRequest: public Request
{
    public:
        PostRequest(HttpHeader header);
        void set_content(std::string content) override;
        std::string get_content() override;
};

#endif //HTTP_SOCKET_PROGRAMMING_POSTREQUEST_H
