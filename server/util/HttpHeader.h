//
// Created by ahmed on 11/7/18.
//

#include <string>
#include <map>

#ifndef UNTITLED_HTTPHEADER_H
#define UNTITLED_HTTPHEADER_H

class HttpHeader
{
    public:
        HttpHeader();
        HttpHeader(std::map<std::string, std::string> header_attributes);
        std::string host;
        std::string user_agent;
        std::string accept;
        std::string accept_language;
        std::string accept_encoding;
        std::string accept_charset;
        std::string keep_alive;
        std::string connection;
};

#endif //UNTITLED_HTTPHEADER_H
