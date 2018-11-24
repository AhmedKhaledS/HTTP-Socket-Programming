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
        vector<string> splitted_line(istream_iterator<std::string>{iss},
                                    istream_iterator<std::string>());
        if (accept_body) // Body
            msg_body += line + "\r\n";
        else if (splitted_line.size() > 2) // Request header
        {
            if(splitted_line[0] != "GET" && splitted_line[0] != "POST")
                continue;

            this->request_type = splitted_line[0];
            this->requested_file_name = splitted_line[1];
            this->connection_type = splitted_line[2];

            cout << "REQUEST TYPE:" << this->request_type << endl;
        }
        else if (splitted_line.size() == 2) // Header attributes
            header_attributes[splitted_line[0].substr(0, splitted_line[0].length()-1)] = splitted_line[1];
        else if (line.empty())
            accept_body = true;
    }
    msg_body = msg_body.substr(0, msg_body.length() - 2);
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