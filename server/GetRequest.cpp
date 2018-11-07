//
// Created by ahmed on 11/7/18.
//

#include "GetRequest.h"

using namespace std;


GetRequest::GetRequest(HttpHeader header, string file_name)
            : request_header(header), file_name(file_name)
{}

void GetRequest::set_file_name(string file_name)
{
    this->file_name = file_name;
}

string GetRequest::get_file_name()
{
    return this->file_name;
}

void GetRequest::set_request_header(HttpHeader header)
{
    this->request_header = header;
}

HttpHeader GetRequest::get_http_header()
{
    return this->request_header;
}

void GetRequest::set_content(string content)
{
    this->content = "";
}

string GetRequest::get_content()
{
    return "";
}