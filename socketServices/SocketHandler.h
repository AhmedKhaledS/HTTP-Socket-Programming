//
// Created by hisham on 18/11/18.
//

#ifndef HTTP_CLIENT_SERVER_SOCKETHANDLER_H
#define HTTP_CLIENT_SERVER_SOCKETHANDLER_H

#include <string>
#include <mutex>
#include <vector>

class SocketHandler {

public:
    static int send (int socket, char* header, std::string data);
    static int send (int socket, char* header);
    static void recieve (int socket, std::vector<std::string> &buffer);

private:
    static std::mutex lock;
};


#endif //HTTP_CLIENT_SERVER_SOCKETHANDLER_H
