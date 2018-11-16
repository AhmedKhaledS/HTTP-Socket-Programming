//
// Created by ahmed on 11/6/18.
//

#include "FileReader.h"
#include <fstream>

using namespace std;

FileReader::FileReader()
{
}

std::string FileReader::read_file(std::string path)
{
    ifstream file(path);
    if (file.is_open())
    {
        std::string line((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
        file.close();

        return line;
    }
    else
    {
        return "";
    }
}

void FileReader::write_file(std::string path, std::string content)
{
}
