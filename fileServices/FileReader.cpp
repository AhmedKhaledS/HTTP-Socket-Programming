//
// Created by ahmed on 11/6/18.
//

#include "FileReader.h"
#include <fstream>

using namespace std;

FileReader::FileReader()
{
}

bool FileReader::file_exist(std::string path)
{
    ifstream file(path);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    else
    {
        return false;
    }
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
