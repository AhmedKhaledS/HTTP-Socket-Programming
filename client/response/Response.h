//
// Created by ahmednagga19 on 17/11/18.
//

#ifndef HTTP_CLIENT_SERVER_RESPONSE_H
#define HTTP_CLIENT_SERVER_RESPONSE_H

#include <map>

enum RES_TYPE {OKAY, NOT_FOUND};

class Response
{
public:
    Response(std::string response);

    const std::map<std::string, std::string> &getHeaders() const;

    RES_TYPE getResponse_type() const;

    const std::string &getData() const;

    const std::string &getHttp_version() const;

private:
    std::map<std::string ,std::string> headers;
    RES_TYPE response_type;
    std::string data;
    std::string http_version;

    void parse_response(std::string response);
    void set_response_type(std::string first_line);
};


#endif //HTTP_CLIENT_SERVER_RESPONSE_H
