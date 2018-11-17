//
// Created by ahmednagga19 on 17/11/18.
//

#ifndef HTTP_CLIENT_SERVER_REQUESTBUILDER_H
#define HTTP_CLIENT_SERVER_REQUESTBUILDER_H


#include "RequestCommand.h"

class RequestBuilder
{
public:
    RequestBuilder();

    /**
     * Build a string request message from a Request Command Object
     * @param command request command object containing request args
     * @return string containing the request
     */
    std::string build_request_message(RequestCommand command);
private:
};


#endif //HTTP_CLIENT_SERVER_REQUESTBUILDER_H
