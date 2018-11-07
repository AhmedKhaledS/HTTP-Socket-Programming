//
// Created by ahmed on 11/6/18.
//

#include "FileWriter.h"
#include <fstream>

using namespace std;

FileWriter::FileWriter()
{
}

std::string FileWriter::read_file(std::string path)
{
}

void FileWriter::write_file(std::string path, std::string content)
{
    ofstream file;
    file.open (path);
    file << content;
    file.close();
}
