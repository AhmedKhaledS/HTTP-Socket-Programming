//
// Created by ahmed on 11/6/18.
//

#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>
#include "RequestParser.h"
#include "PostRequest.h"
#include "GetRequest.h"

using namespace std;

RequestParser::RequestParser(vector<string> message): request_message(message)
{}

Request* RequestParser::parse()
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
            this->connection_type = splited_line[2];
        }
        else if (splited_line.size() == 2)
        {
            header_attributes[splited_line[0].substr(0, splited_line[0].length()-1)] = splited_line[1];
        }
    }
    return get_specified_request();
}

Request* RequestParser::get_specified_request()
{
    Request* request;
    if (request_type == "GET")
    {
        request = new GetRequest(this->header_attributes, this->requested_file_name);
        request->set_request_type("GET");
    }
    else if (request_type == "POST")
    {
        request = new PostRequest(this->header_attributes, this->requested_file_name);
        request->set_request_type("POST");
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