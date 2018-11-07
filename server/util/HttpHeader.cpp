//
// Created by ahmed on 11/7/18.
//

#include "HttpHeader.h"
#include "Constants.h"

using namespace std;

HttpHeader::HttpHeader() {}

HttpHeader::HttpHeader(map<string, string> header_attributes)
{
    host = header_attributes[Header::HOST];
    user_agent = header_attributes[Header::USER_AGENT];
    accept = header_attributes[Header::ACCEPT];
    accept_language = header_attributes[Header::ACCEPT_LANGUAGE];
    accept_encoding = header_attributes[Header::ACCEPT_ENCODING];
    accept_charset = header_attributes[Header::ACCEPT_CHARSET];
    keep_alive = header_attributes[Header::KEEP_ALIVE];
    connection = header_attributes[Header::CONNECTION];
}