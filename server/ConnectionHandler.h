//
// Created by ahmednagga19 on 07/11/18.
//

#ifndef HTTP_CLIENT_SERVER_CONNECTIONHANDLER_H
#define HTTP_CLIENT_SERVER_CONNECTIONHANDLER_H
#include <vector>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>

using namespace boost::interprocess;

typedef allocator<int, managed_shared_memory::segment_manager>  ShmemAllocator;

//Alias a vector that uses the previous STL-like allocator so that allocates
//its values from the segment
typedef std::vector<std::pair<int, long long>, ShmemAllocator> shared_vector;

class ConnectionHandler
{
public:
    ConnectionHandler();

    void handle(int socket_fd);

private:
    void handle_request(char buffer_copy[], int socket_fd);
    int get_process_index(shared_vector *running_processes);
};

#endif //HTTP_CLIENT_SERVER_CONNECTIONHANDLER_H
