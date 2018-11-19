//
// Created by hisham on 18/11/18.
//

#ifndef HTTP_CLIENT_SERVER_SOCKETHANDLER_H
#define HTTP_CLIENT_SERVER_SOCKETHANDLER_H

#include <string>

class SocketHandler {

    public:
        static int send (int socket, char* header, char* data);
        static int send (int socket, char* header);
        static void recieve (int socket, std::string &buffer);

};


#endif //HTTP_CLIENT_SERVER_SOCKETHANDLER_H
