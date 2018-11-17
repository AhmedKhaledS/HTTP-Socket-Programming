//
// Created by ahmednagga19 on 17/11/18.
//

#ifndef HTTP_CLIENT_SERVER_RESPONSEHANDLER_H
#define HTTP_CLIENT_SERVER_RESPONSEHANDLER_H


#include <string>
#include "Response.h"
#include "../RequestCommand.h"

class ResponseHandler
{
public:
    ResponseHandler();
    void handle_response(std::string message, REQ_TYPE request_type, std::string file_name);

protected:
    Response response;
};


#endif //HTTP_CLIENT_SERVER_RESPONSEHANDLER_H
