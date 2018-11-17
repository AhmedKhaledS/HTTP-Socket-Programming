//
// Created by ahmednagga19 on 17/11/18.
//

#include "ResponseHandler.h"
#include "../../fileServices/FileWriter.h"

using namespace std;

const string FOLDER = "../client/client_files/";

ResponseHandler::ResponseHandler() {

}

void ResponseHandler::handle_response(std::string message, REQ_TYPE request_type, std::string file_name)
{
    Response response = Response(message);
    if (request_type == REQ_TYPE::GET && response.getResponse_type() == RES_TYPE::OKAY) {
        FileWriter* writer = new FileWriter();
        writer->write_file(FOLDER + file_name, response.getData());
    }
}

