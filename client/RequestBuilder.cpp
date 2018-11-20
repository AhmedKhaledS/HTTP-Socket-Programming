//
// Created by ahmednagga19 on 17/11/18.
//

#include "RequestBuilder.h"
#include "../fileServices/FileReader.h"


#define LINE_END "\r\n"
#define VERSION "HTTP/1.1"

using namespace std;

const string HEADERS = "Host: www.tutorialspoint.com\r\n"
                       "User-Agent: Mozilla/4.0(compatible;MSIE5.01;WindowsNT)\r\n"
                       "Accept: text/html,application/xhtml+xml\r\n"
                       "Accept-Language: en-us\r\n"
                       "Accept-Encoding: gzip,deflate\r\n"
                       "Accept-Charset: ISO-8859-1,utf-8;q=0.7\r\n"
                       "Connection: Keep-Alive\r\n"
                       "\r\n";

RequestBuilder::RequestBuilder() {

}

std::string RequestBuilder::build_request_message(RequestCommand &command) {
    string request = "";
    request += (command.getType() == REQ_TYPE::GET ? "GET " : "POST ");
    request += (command.getFile_name());
    request += (" ");
    request += VERSION;
    request += LINE_END;
    request += HEADERS;
    if (command.getType() == REQ_TYPE::POST) {
        FileReader* reader = new FileReader();
        if (reader->file_exist(command.getFile_name()))
            command.setData(reader->read_file(command.getFile_name()));
        else
            perror("FILE NOT FOUND TO INCLUDE IN POST");
    }
    return request;
}
