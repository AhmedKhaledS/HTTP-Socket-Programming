//
// Created by ahmed on 11/6/18.
//

#include "GetRequest.h"

#ifndef HTTP_SOCKET_PROGRAMMING_POSTREQUEST_H
#define HTTP_SOCKET_PROGRAMMING_POSTREQUEST_H

class PostRequest: public GetRequest
{
    private:
        std::string content;
    public:
        PostRequest(HttpHeader header);
        void set_content(std::string content);
        std::string get_content();
};

#endif //HTTP_SOCKET_PROGRAMMING_POSTREQUEST_H
