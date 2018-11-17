//
// Created by ahmednagga19 on 17/11/18.
//

#include <vector>
#include "Response.h"
#include "../StringUtils.h"

#define OK "200"



using namespace std;

Response::Response(std::string response) {
    parse_response(response);
}

void Response::parse_response(std::string response) {
    vector<string> lines = split_string(response, "\r\n");
    set_response_type(lines[0]);
    // room for parsing headers;
    if (lines.size() >= 1)
        this->data = lines[lines.size() - 1];
    return;
}

void Response::set_response_type(std::string first_line) {
    vector<string> args = split_string(first_line, " ");
    if (args.size() != 3)
    {
        perror("INVALID FIRST LINE OF RESPONSE : FEW NUMBER OF ARGUMENTS");
    }
    this->http_version = args[0];
    this->response_type = (args[1] == OK ? RES_TYPE::OKAY : RES_TYPE::NOT_FOUND);
    if ( (RES_TYPE::OKAY == this->response_type && args[2] != "OK") ||
            (RES_TYPE::NOT_FOUND == this->response_type && args[2] != "NOT_FOUND") )
    {
        perror("STATUS CODE AND PHRASE DO NOT MATCH");
    }
    return;
}

const map<string, string> &Response::getHeaders() const {
    return headers;
}

RES_TYPE Response::getResponse_type() const {
    return response_type;
}

const string &Response::getData() const {
    return data;
}

const string &Response::getHttp_version() const {
    return http_version;
}
