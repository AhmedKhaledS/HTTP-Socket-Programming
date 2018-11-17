cmake_minimum_required(VERSION 3.9)
project(http_client_server)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(run client/WebClient.cpp
                    client/WebClient.h
                    server/PostRequest.h
                    server/RequestParser.cpp
                    server/RequestParser.h
                    server/WebServer.cpp
                    server/WebServer.h
                     fileServices/FileHandler.h
                    fileServices/FileReader.cpp
                    fileServices/FileReader.h
                    fileServices/FileWriter.cpp
                    fileServices/FileWriter.h
                    server/util/HttpHeader.h
                    server/PostRequest.cpp
                    server/Request.h
                    server/Request.cpp
                    main.cpp server/util/Constants.h
                    server/util/Constants.cpp
                    server/util/HttpHeader.cpp
                    server/GetRequest.cpp
                    server/GetRequest.h
                    server/ConnectionHandler.h
                    server/ConnectionHandler.cpp
                    server/ConnectionsTracker.cpp
                    server/ConnectionsTracker.h client/RequestCommand.cpp client/RequestCommand.h client/StringUtils.h)

add_executable(runClient client/WebClient.cpp
        client/RequestCommand.cpp client/RequestCommand.h client/StringUtils.h fileServices/FileHandler.h
        fileServices/FileReader.cpp
        fileServices/FileReader.h
        fileServices/FileWriter.cpp
        fileServices/FileWriter.h client/main.cpp client/RequestBuilder.cpp client/RequestBuilder.h client/response/ResponseHandler.cpp client/response/ResponseHandler.h client/response/Response.cpp client/response/Response.h)

target_link_libraries(run ${Boost_LIBRARIES} -lrt)
