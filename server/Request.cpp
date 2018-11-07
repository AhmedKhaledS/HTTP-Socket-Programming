//
// Created by ahmed on 11/7/18.
//

#include "Request.h"

using namespace std;


Request::Request(HttpHeader header, string file_name)
            : request_header(header), file_name(file_name)
{}

void Request::set_file_name(string file_name)
{
    this->file_name = file_name;
}

string Request::get_file_name()
{
    return this->file_name;
}

void Request::set_request_header(HttpHeader header)
{
    this->request_header = header;
}

HttpHeader Request::get_http_header()
{
    return this->request_header;
}

void Request::set_content(string content)
{
    this->content = "";
}

string Request::get_content()
{
    return "";
}