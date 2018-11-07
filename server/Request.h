//
// Created by ahmed on 11/7/18.
//

#ifndef HTTP_CLIENT_SERVER_REQUEST_H
#define HTTP_CLIENT_SERVER_REQUEST_H

#include "util/HttpHeader.h"

class Request
{
    protected:
        std::string content;

    private:
        HttpHeader request_header;
        std::string file_name;

    public:
        Request(HttpHeader header, std::string file_name);
        void set_request_header(HttpHeader header);
        HttpHeader get_http_header();
        void set_file_name(std::string file_name);
        std::string get_file_name();
        virtual std::string get_content();
        virtual void set_content(std::string content);
};


#endif //HTTP_CLIENT_SERVER_REQUEST_H
