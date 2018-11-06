//
// Created by ahmed on 11/6/18.
//

#include "RequestParser.h"
#include "PostRequest.h"

using namespace std;

RequestParser::RequestParser(string message) {}

Request* RequestParser::parse()
{
    HttpHeader x;
    x.accept = "Accept";
    x.host = "Host";
    x.user_agent = "User-Agent";
    x.accept_language = "Accept-Language";
    x.accept_encoding = "Accept-Encoding";
    x.accept_charset = "Accept-Charset";
    x.keep_alive = "Keep-Alive";
    x.connection = "Connection";
    GetRequest *get = new GetRequest(x);
    get->set_file_name("test.txt");
    get->set_content("This is a testing content.");
    return get;
}