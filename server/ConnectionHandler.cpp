//
// Created by ahmednagga19 on 07/11/18.
//

#include "ConnectionHandler.h"
#include "ConnectionsTracker.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

using namespace std;

const int BUFFER_SIZE = 1024;

ConnectionHandler::ConnectionHandler() {}


void ConnectionHandler::handle(int socket_fd)
{
    while (true)
    {
        // read request -> parse request -> create request handler in a thread
        char buffer[BUFFER_SIZE] = {0};
        read(socket_fd, buffer, BUFFER_SIZE);
        // RequestParser request_parser = RequestParser(buffer);
        // request_parser.parse();
        printf("\n Message : %s\n", buffer);
        return; // TODO : Need to finish parsing and handling requests.
        // check
//        if (!ConnectionsTracker::check_connections()) {
//            return;
//        }
    }
}
