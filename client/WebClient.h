//
// Created by ahmed on 11/6/18.
//

#ifndef HTTP_SOCKET_PROGRAMMING_WEBCLIENT_H
#define HTTP_SOCKET_PROGRAMMING_WEBCLIENT_H

#include <string>
#include <vector>
#include "RequestCommand.h"

enum CONNECTION_TYPE {PERSISTENT, PIPELINED, NON_PERSISTENT};

class WebClient
{
public:
    /**
     * Requests single file from server through the given socket.
     * @param file_name name of the file to be requested from server
     * @param socket_fd socket number to send request on
     * @return pointer to the requested file after saving it in current directory
     */
    FILE* get_file(std::string file_name, int socket_fd);
    /**
     * Posts a file to a server through the given socket.
     * @param file_path path of the file to be fetched and sent to server
     * @param socket_fd socket number to send requests and file on
     */
    void post_file(std::string file_path, int socket_fd);

    /**
     * Receives response on socket and returns a string containing the response.
     * @param socket socket to receive response from.
     * @return response
     */
    std::string receive_response(int socket);
    /**
     * Sends requests from a a given file containing list of requests.
     * @param requests_file_name name of the file containing requests
     * @param host_name name of server
     * @param port_number port number to which connection should be made
     * @param connection_type type of connections used
     */
    void send_requests(std::string requests_file_name ,std::string host_name, int port_number,
            CONNECTION_TYPE connection_type);

private:
    /**
     * Parses a request commands file and returns a list of Request Command objects.
     * @param file_name name of the request commands file
     * @return vector of RequestCommands objects
     */
    std::vector<RequestCommand> parse_request_commands_file(std::string file_name);

    /**
     * Parses request command string and produces RequestCommand object
     * @param request_line the request command line
     * @return RequestCommand object
     */
    RequestCommand parse_request_command_line(std::string request_line);

    /**
     * Builds list of string messages from Request Command Objects.
     * @param commands list of request commands
     * @return vector of request messages
     */
    std::vector<std::string> build_request_messages(std::vector<RequestCommand> commands);

    /**
     * Connects to a server on given host and port and sends requests using non-persistent connections.
     * @param commands vector of commands to be issued
     * @param host_name name of host
     * @param port_number port number
     */
    void send_requests_non_persistent(std::vector<std::string> request_messages, std::string host_name, int port_number);

    /**
     * Connects to a server on given host and port and sends requests using non-persistent connections.
     * @param commands vector of commands to be issued
     * @param host_name name of host
     * @param port_number port number
     */
    void send_requests_persistent(std::vector<RequestCommand> commands, std::string host_name, int port_number);

    /**
     * Connects to a server on given host and port and sends requests using pipelining.
     * @param commands vector of commands to be issued
     * @param host_name name of host
     * @param port_number port number
     */
    void send_requests_pipelined(std::vector<RequestCommand> commands, std::string host_name, int port_number);

    /**
     * Connects to a server on given host and port.
     * @param host_name name of host
     * @param port_number port number
     */
    int connect(std::string hostname, int port_number);
};

#endif //HTTP_SOCKET_PROGRAMMING_WEBCLIENT_H
