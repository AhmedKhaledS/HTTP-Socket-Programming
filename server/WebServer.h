//
// Created by ahmed on 11/6/18.
//

#ifndef HTTP_SOCKET_PROGRAMMING_WEBSERVER_H
#define HTTP_SOCKET_PROGRAMMING_WEBSERVER_H

class WebServer
{
    public :
        WebServer(int port_number);
        void start();
    private :
        int port_number;
        int connections_count = 0;
};

#endif //HTTP_SOCKET_PROGRAMMING_WEBSERVER_H
