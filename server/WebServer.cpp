//
// Created by ahmed on 11/6/18.
//

#include "WebServer.h"
#include "ConnectionHandler.h"

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
    initialize_shared_memory();

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int true_ = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,&true_,sizeof(int)) == -1)
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
        ConnectionHandler connection_handler = ConnectionHandler();
        int pid = fork();
        if (pid == 0)
        {
            // Child
            connection_handler.handle(new_socket);

        } else {
            // Parent
//            this->child_pids.push_back(pid);
            std::cout << "Reached Parent" << std::endl;

        }
        // Destroy the created segment.
        segment->destroy<shared_vector>("shared_vector");
        delete segment;
        // TODO : Should add Heuristic to close connections.
    }
}

void WebServer::initialize_shared_memory()
{
    //Remove shared memory on construction and destruction
    struct shm_remove
    {
        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;

    //Create a new segment with given name and size
    segment = new managed_shared_memory(create_only, "MySharedMemory", 65536);

    //Initialize shared memory STL-compatible allocator
    const ShmemAllocator alloc_inst (segment->get_segment_manager());

    //Construct a vector named "shared_vector" in shared memory with argument alloc_inst
    shared_vector *myvector = segment->construct<shared_vector>("shared_vector")(alloc_inst);

    // If we want to deal with this vector, code goes here.
}