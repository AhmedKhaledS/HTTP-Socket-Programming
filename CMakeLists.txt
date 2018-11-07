cmake_minimum_required(VERSION 3.12)
project(http_client_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(run client/WebClient.cpp
                    client/WebClient.h
        server/PostRequest.h
                    server/RequestParser.cpp
                    server/RequestParser.h
                    server/WebServer.cpp
                    server/WebServer.h
                    fileServices/FileHandler.cpp
                    fileServices/FileHandler.h
                    fileServices/FileReader.cpp
                    fileServices/FileReader.h
                    fileServices/FileWriter.cpp
                    fileServices/FileWriter.h
        server/util/HttpHeader.h
        server/PostRequest.cpp
        server/Request.h
        server/Request.cpp
                    main.cpp server/util/Constants.h server/util/Constants.cpp server/util/HttpHeader.cpp server/GetRequest.cpp server/GetRequest.h)