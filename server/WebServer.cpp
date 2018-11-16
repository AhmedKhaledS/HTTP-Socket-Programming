//
// Created by ahmed on 11/6/18.
//

#include "WebServer.h"
#include "ConnectionHandler.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include <vector>
#include <pthread.h>
#include <thread>
#include <iostream>

using namespace std;

const int MAX_QUEUE_SIZE = 10;

WebServer::WebServer(int port_number) : port_number(port_number)
{}

void WebServer::start()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int true_ = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,&true_,sizeof(int)) == -1)
    {
        perror("Setsockopt");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( this->port_number );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, MAX_QUEUE_SIZE) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while (true)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address,
                                 (socklen_t*) &addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        ConnectionHandler connection_handler = ConnectionHandler();
        thread connection_thread(&ConnectionHandler::handle, connection_handler, new_socket);
        connection_thread.join(); // TODO : Should not wait for this to finish
        // TODO : Should add Heuristic to close connections.
    }
}
