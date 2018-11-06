//
// Created by ahmed on 11/6/18.
//
#include <iostream>
#include "server/HttpHeader.h"
#include "server/GetRequest.h"
#include "server/PostRequest.h"
#include "server/RequestParser.h"

using namespace std;


int main(int argc, char **argv)
{
//    HttpHeader x;
//    x.accept = "Accept";
//    x.host = "Host";
//    x.user_agent = "User-Agent";
//    x.accept_language = "Accept-Language";
//    x.accept_encoding = "Accept-Encoding";
//    x.accept_charset = "Accept-Charset";
//    x.keep_alive = "Keep-Alive";
//    x.connection = "Connection";
//    GetRequest get(x);
//    get.set_file_name("test.txt");
//    cout << get.get_file_name() << "   " << get.get_http_header().accept << "  " << get.get_http_header().accept_charset;
//
//    PostRequest post(x);
//    post.set_content("This is a testing content.");
//    cout << post.get_file_name() << "   " << post.get_http_header().accept << "  " << post.get_content() << endl;

    RequestParser requestParser("ahmed");
    Request *post_test = requestParser.parse();
//    post_test.set_file_name("Changed_file_name");
//    cout << post_test.get_file_name() << endl;
    cout << post_test->get_content();
}
