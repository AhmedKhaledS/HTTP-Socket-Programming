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
    bool accept_body = false;
    string msg_body = "";
    int lines_count = 0;
    for (string line : this->request_message)
    {
        cout << lines_count++ << ": " << line << '\n';
        istringstream iss(line);
        vector<string> splited_line(istream_iterator<std::string>{iss},
                                    istream_iterator<std::string>());
        if (accept_body) // Body
            msg_body += line;
        else if (splited_line.size() > 2) // Request header
        {
            this->request_type = splited_line[0];
            this->requested_file_name = splited_line[1];
            this->connection_type = splited_line[2];
        }
        else if (splited_line.size() == 2) // Header attributes
            header_attributes[splited_line[0].substr(0, splited_line[0].length()-1)] = splited_line[1];
        else if (line.empty())
            accept_body = true;

    }
    return get_specified_request(msg_body);
}

Request* RequestParser::get_specified_request(string msg_body)
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
        request->set_content(msg_body);
    }
    else
        perror("Unsupported request type.");

    return request;

}

string RequestParser::get_request_type()
{
    return this->request_type;
}