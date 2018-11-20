//
// Created by ahmed on 11/7/18.
//

#include "PostRequest.h"

using namespace std;

PostRequest::PostRequest(HttpHeader header, string file_name) : Request(header, file_name)
{}

void PostRequest::set_content(string content)
{
    this->content = content;
}

string PostRequest::get_content()
{
    return this->content;
}
