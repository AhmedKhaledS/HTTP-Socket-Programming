//
// Created by ahmednagga19 on 17/11/18.
//

#include "ResponseHandler.h"
#include "../../fileServices/FileWriter.h"

using namespace std;

const string FOLDER = "../client/client_files/";


void ResponseHandler::handle_response(std::string message, REQ_TYPE request_type, std::string file_name)
{
    this->response = Response(message);
    if (request_type == REQ_TYPE::GET && this->response.getResponse_type() == RES_TYPE::OKAY) {
        FileWriter* writer = new FileWriter();
        writer->write_file(FOLDER + file_name, this->response.getData());
    }
}

