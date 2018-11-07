//
// Created by ahmed on 11/6/18.
//

#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>
#include "RequestParser.h"
#include "PostRequest.h"

using namespace std;

RequestParser::RequestParser(vector<string> message): request_message(message)
{}

GetRequest* RequestParser::parse()
{
    for (string line : this->request_message)
    {
        istringstream iss(line);
        vector<string> splited_line(istream_iterator<std::string>{iss},
                                    istream_iterator<std::string>());
        if (splited_line.size() > 2)
        {
            this->request_type = splited_line[0];
            this->requested_file_name = splited_line[1];
            this->connection_type = splited_line.back();
        }
        else
            header_attributes[splited_line[0].substr(0, splited_line[0].length()-1)] = splited_line.back();
    }
    return this->get_specified_request();

/*    HttpHeader x;
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
    return get;*/
}

GetRequest* RequestParser::get_specified_request()
{
    GetRequest* request;
    if (this->request_type == "GET")
    {
        request = new GetRequest(this->header_attributes, this->requested_file_name);
    }
    else if (request_type == "POST")
    {
        request = new PostRequest(this->header_attributes, this->requested_file_name);
        // TODO: Set the content here.
    }
    else
    {
        //throw exception;
    }

    return request;

}

string RequestParser::get_request_type()
{
    return this->request_type;
}