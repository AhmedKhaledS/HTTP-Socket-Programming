//
// Created by ahmed on 11/6/18.
//

#include "GetRequest.h"
#include "GetRequest.h"

#ifndef HTTP_SOCKET_PROGRAMMING_POSTREQUEST_H
#define HTTP_SOCKET_PROGRAMMING_POSTREQUEST_H

class PostRequest: public GetRequest
{
    public:
        PostRequest(HttpHeader header, std::string file_name);
        void set_content(std::string content) override;
        std::string get_content() override;
};

#endif //HTTP_SOCKET_PROGRAMMING_POSTREQUEST_H
