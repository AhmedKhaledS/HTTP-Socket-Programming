//
// Created by ahmed on 11/7/18.
//

#ifndef HTTP_CLIENT_SERVER_GETREQUEST_H
#define HTTP_CLIENT_SERVER_GETREQUEST_H

#include "Request.h"

class GetRequest: public Request
{
    public:
        GetRequest(HttpHeader header, std::string file_name);
};
#endif //HTTP_CLIENT_SERVER_GETREQUEST_H
