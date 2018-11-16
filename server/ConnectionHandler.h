//
// Created by ahmednagga19 on 07/11/18.
//

#ifndef HTTP_CLIENT_SERVER_CONNECTIONHANDLER_H
#define HTTP_CLIENT_SERVER_CONNECTIONHANDLER_H

class ConnectionHandler
{
public:
    ConnectionHandler();

    void handle(int socket_fd);
};

#endif //HTTP_CLIENT_SERVER_CONNECTIONHANDLER_H
