//
// Created by ahmed on 11/6/18.
//

#ifndef HTTP_SOCKET_PROGRAMMING_FILEHANDLER_H
#define HTTP_SOCKET_PROGRAMMING_FILEHANDLER_H

#include "string"

class FileHandler
{
    public:
        virtual std::string read_file(std::string path) = 0;
        virtual void write_file(std::string path, std::string content) = 0;
};

#endif //HTTP_SOCKET_PROGRAMMING_FILEHANDLER_H
