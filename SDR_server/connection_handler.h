#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include "device_listener.h"
#include "../connection_structure.h"

struct connection_handler{

    connection_handler(device_listener* l);
    void start_server(int port);

private:

    const int REQUEST_QUEUE_SIZE = 16;
    const int EPOLL_QUEUE_LEN = 16;
    const int MAX_EVENTS_GRABBED_PER_TICK = 16;

    device_listener* listener;

    //connection creation
    int create_socket(int port);
    int create_epoll(int socket_fd);
    //client communication
    void new_client_accepting(int socket_fd, int epoll_fd);
    void get_client_request(int client_fd);

};

#endif // CONNECTION_HANDLER_H
