//
// Created by ahmednagga19 on 17/11/18.
//

#ifndef HTTP_CLIENT_SERVER_REQUESTCOMMAND_H
#define HTTP_CLIENT_SERVER_REQUESTCOMMAND_H

#include <string>

enum REQ_TYPE{POST, GET};

class RequestCommand {
public:
    RequestCommand();

    RequestCommand(REQ_TYPE type, const std::string &file_name, const std::string &host_name, int port_number);

    RequestCommand(REQ_TYPE type, const std::string &file_name, const std::string &host_name);

    REQ_TYPE getType() const;

    const std::string &getFile_name() const;

    const std::string &getHost_name() const;

    int getPort_number() const;

    void setType(REQ_TYPE type);

    void setFile_name(const std::string &file_name);

    void setHost_name(const std::string &host_name);

    void setPort_number(int port_number);

    void display_request_args();

    const std::string &getData() const;

    void setData(const std::string &data);

private:
    REQ_TYPE type;
    std::string file_name;
    std::string host_name;
    int port_number = -1;
    std::string data;
};


#endif //HTTP_CLIENT_SERVER_REQUESTCOMMAND_H
