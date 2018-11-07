//
// Created by ahmed on 11/7/18.
//

#ifndef HTTP_CLIENT_SERVER_CONSTANTS_H
#define HTTP_CLIENT_SERVER_CONSTANTS_H

#include <string>

class Header
{
    public:
        static std::string HOST;
        static std::string ACCEPT;
        static std::string USER_AGENT;
        static std::string ACCEPT_LANGUAGE;
        static std::string ACCEPT_ENCODING;
        static std::string ACCEPT_CHARSET;
        static std::string KEEP_ALIVE;
        static std::string CONNECTION;
};
#endif //HTTP_CLIENT_SERVER_CONSTANTS_H
