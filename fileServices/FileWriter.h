//
// Created by ahmed on 11/6/18.
//

#ifndef HTTP_SOCKET_PROGRAMMING_FILEWRITER_H
#define HTTP_SOCKET_PROGRAMMING_FILEWRITER_H

#include "FileHandler.h"

class FileWriter: public FileHandler
{
    public:
        FileWriter();
        bool file_exist(std::string path) override;
        std::string read_file(std::string path) override;
        void write_file(std::string path, std::string content) override;
};

#endif //HTTP_SOCKET_PROGRAMMING_FILEWRITER_H
