//
// Created by ahmed on 11/6/18.
//

#ifndef HTTP_SOCKET_PROGRAMMING_FILEREADER_H
#define HTTP_SOCKET_PROGRAMMING_FILEREADER_H

#include "FileHandler.h"

class FileReader: public FileHandler
{
    public:
        FileReader();
        bool file_exist(std::string path) override;
        std::string read_file(std::string path) override;
        void write_file(std::string path, std::string content) override;
};

#endif //HTTP_SOCKET_PROGRAMMING_FILEREADER_H
