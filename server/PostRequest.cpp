//
// Created by ahmed on 11/7/18.
//

#include "PostRequest.h"

using namespace std;

PostRequest::PostRequest(HttpHeader header) : GetRequest(header)
{}

void PostRequest::set_content(string content)
{
    this->content = content;
}

string PostRequest::get_content()
{
    return this->content;
}