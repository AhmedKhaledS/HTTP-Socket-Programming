//
// Created by ahmednagga19 on 17/11/18.
//

#ifndef HTTP_CLIENT_SERVER_STRINGUTILS_H
#define HTTP_CLIENT_SERVER_STRINGUTILS_H

#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> split_string(std::string s, char delimiter)
{
    std::stringstream iss(s);
    std::vector<std::string> splitted_strings;
    while(iss.good())
    {
        std::string single_line;
        getline(iss,single_line,delimiter);
        splitted_strings.push_back(single_line);
    }
    return splitted_strings;
}

#endif //HTTP_CLIENT_SERVER_STRINGUTILS_H
