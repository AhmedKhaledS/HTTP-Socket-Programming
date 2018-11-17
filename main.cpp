//
// Created by ahmed on 11/6/18.
//
#include <iostream>
#include "server/util/HttpHeader.h"
#include "server/Request.h"
#include "server/PostRequest.h"
#include "server/RequestParser.h"
#include "server/WebServer.h"
#include "fileServices/FileReader.h"
#include "fileServices/FileWriter.h"
#include "client/WebClient.h"
#include <time.h>
#include <vector>


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
//    Request get(x);
//    get.set_file_name("test.txt");
//    cout << get.get_file_name() << "   " << get.get_http_header().accept << "  " << get.get_http_header().accept_charset;
//
//    PostRequest post(x);
//    post.set_content("This is a testing content.");
//    cout << post.get_file_name() << "   " << post.get_http_header().accept << "  " << post.get_content() << endl;

//    RequestParser requestParser(std::vector<string>({"GET /kurose_ross/interactive/quotation1.html HTTP/1.0\r\n",
//                                                     "Host: gaia.cs.umass.edu\r\n",
//                                                     "\r\n"}));
//    Request *post_test = requestParser.parse();
//////    post_test.set_file_name("Changed_file_name");
//////    cout << post_test.get_file_name() << endl;
//    cout << "content: " + post_test->get_content() << endl;
//    cout << "file_name: " + post_test->get_file_name() << endl;
//    cout << post_test->get_http_header().host << endl;

    WebServer server(8080);
    server.start();


/*

    FileReader* file_reader = new FileReader();
    FileWriter* file_writer = new FileWriter();

    string content = file_reader->read_file("../resources/html_version.html");
    file_writer->write_file("../resources/html_version_test.html", content);
*/
}
