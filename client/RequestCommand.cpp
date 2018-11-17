//
// Created by ahmednagga19 on 17/11/18.
//

#include <iostream>
#include "RequestCommand.h"

RequestCommand::RequestCommand() {}

RequestCommand::RequestCommand(REQ_TYPE type, const std::string &file_name, const std::string &host_name,
                               int port_number) : type(type), file_name(file_name), host_name(host_name),
                                                  port_number(port_number) {}

RequestCommand::RequestCommand(REQ_TYPE type, const std::string &file_name, const std::string &host_name) : type(type),
                                                                                                            file_name(
                                                                                                                    file_name),
                                                                                                            host_name(
                                                                                                                    host_name) {}

void RequestCommand::setType(REQ_TYPE type) {
    RequestCommand::type = type;
}

void RequestCommand::setFile_name(const std::string &file_name) {
    RequestCommand::file_name = file_name;
}

void RequestCommand::setHost_name(const std::string &host_name) {
    RequestCommand::host_name = host_name;
}

void RequestCommand::setPort_number(int port_number) {
    RequestCommand::port_number = port_number;
}

REQ_TYPE RequestCommand::getType() const {
    return type;
}

const std::string &RequestCommand::getFile_name() const {
    return file_name;
}

const std::string &RequestCommand::getHost_name() const {
    return host_name;
}

int RequestCommand::getPort_number() const {
    return port_number;
}

void RequestCommand::display_request_args() {
    std::cout << type << std::endl;
    std::cout << file_name << std::endl;
    std::cout << host_name << std::endl;
    std::cout << port_number << std::endl;
}
