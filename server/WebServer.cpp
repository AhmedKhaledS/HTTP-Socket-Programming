//
// Created by ahmed on 11/6/18.
//

#include "WebServer.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <vector>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>


using namespace boost::interprocess;

const int MAX_QUEUE_SIZE = 10;



WebServer::WebServer(int port_number) : port_number(port_number)
{}

void WebServer::start()
{
    //Remove shared memory on construction and destruction
    struct shm_remove
    {
        shm_remove() { shared_memory_object::remove("SharedMemory"); }
        ~shm_remove(){ shared_memory_object::remove("SharedMemory"); }
    } remover;

    shared_vector *running_processes = initialize_shared_memory();
    std::cout << "Running processes address: " << running_processes << std::endl;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("Setsockopt");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( this->port_number );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, MAX_QUEUE_SIZE) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    while (true)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address,
                                 (socklen_t*) &addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        std::cout << "Accepted new Connection." << std::endl;
        ConnectionHandler connection_handler = ConnectionHandler();
        int pid = fork();
        if (pid == 0)
        {
            // Child
            std::cout << "Child is reached." << std::endl;
            connection_handler.handle(new_socket);
        } else {
            // Parent
            running_processes->push_back({pid, static_cast<long long>(time(NULL))});
            sleep(5);
            std::cout << "Reached Parent" << std::endl;
//            for (auto process : *running_processes)
//            {
//                std::cout << "--Parent-- PID: " << process.first << " | Last Request Time: " << process.second << std::endl;
//            }
        }
        // Destroy the created segment.
        // TODO : Should add Heuristic to close connections.
    }
//    segment->destroy<shared_vector>("shared_vector");
//    delete segment;
}

shared_vector* WebServer::initialize_shared_memory()
{
    //Create a new segment with given name and size
    segment = new managed_shared_memory(create_only, "SharedMemory", 65536);

    //Initialize shared memory STL-compatible allocator
    const ShmemAllocator alloc_inst (segment->get_segment_manager());

    //Construct a vector named "shared_vector" in shared memory with argument alloc_inst
    shared_vector *running_processes = segment->construct<shared_vector>("shared_vector")(alloc_inst);
    return running_processes;
    // If we want to deal with this vector, code goes here.
}