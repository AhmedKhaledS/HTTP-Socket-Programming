//
// Created by ahmednagga19 on 17/11/18.
//

#ifndef HTTP_CLIENT_SERVER_STRINGUTILS_H
#define HTTP_CLIENT_SERVER_STRINGUTILS_H

#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> split_string(std::string s, std::string delimiter)
{
    std::vector<std::string> splitted_strings;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        splitted_strings.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    splitted_strings.push_back(s);
    return splitted_strings;
}

#endif //HTTP_CLIENT_SERVER_STRINGUTILS_H
