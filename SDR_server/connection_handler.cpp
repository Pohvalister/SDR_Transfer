#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>

#include <cerrno>
#include <cassert>
#include <iostream>
#include <cstring>


#include "connection_handler.h"

#define SERV_LOG true

#ifdef SERV_LOG
#define LOG(a) std::cout<<"connection message: "<<(a)<<'\n'
#else
#define LOG(a)
#endif

#define ELOG(a) std::cout<<"\n--\n"<<(a)<<", error:\n"<<'['<<std::string(strerror(errno))<<']'<<"\n--\n\n"

connection_handler::connection_handler(device_listener* l)
    : listener(l)
    {
}

int connection_handler::create_socket(int port) {
    //Для создания сокета типа stream с протоколом TCP, обеспечивающим коммуникационную поддержку, вызов функции socket должен быть следующим:
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        ELOG("Failed creating socket");
        assert(false);
    }
    LOG("Socket created:" + std::to_string(socket_fd));

    //bind socket to port and addresses
    sockaddr_in addr;
    addr.sin_family = AF_INET; //using ipv4
    addr.sin_port = htons(port); //select port
    addr.sin_addr.s_addr = htonl(INADDR_ANY); //listen to all ips

    if (bind(socket_fd, (sockaddr *) &addr, sizeof(sockaddr)) != 0) {
        ELOG("Failed binding socket");
        assert (false);
    }
    LOG("Socket binded to port:"+ std::to_string(port));

    //add listening to socket
    if (listen(socket_fd, REQUEST_QUEUE_SIZE)) {
        ELOG("Failed setting listen to socket");
        assert(false);
    }
    LOG("Added listening");
    return socket_fd;
}

int connection_handler::create_epoll(int socket_fd) {

    int epoll_fd = epoll_create(EPOLL_QUEUE_LEN);

    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = socket_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &ev) == -1) {
        ELOG("Failed creating epoll");
        assert(false);
    }
    LOG("Epoll on socket " + std::to_string(socket_fd) + " created:" + std::to_string(epoll_fd));
    return epoll_fd;
}

void connection_handler::new_client_accepting(int socket_fd, int epoll_fd) {
    int client_socket_fd = accept(socket_fd, nullptr, nullptr);
    if (client_socket_fd == -1) {
        ELOG("Failed getting new client");
        return;
    }

    epoll_event client_ready;
    client_ready.events = EPOLLIN | EPOLLET;
    client_ready.data.fd = client_socket_fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket_fd, &client_ready)) {
        ELOG("Failed adding new client");
        return;
    }

    LOG("Client with " + std::to_string(client_socket_fd) + " socket created");
}

void connection_handler::get_client_request(int client_fd){
    const int LEN_BYTES = sizeof (int16_t);
    char len_size_buffer[LEN_BYTES];
    ssize_t data_length = read(client_fd, len_size_buffer, LEN_BYTES);
    if (data_length == -1){
        ELOG("Failed reading from client");//REINTR!!
        return;
    }
    if (data_length == 0){
        LOG("Client on socket " + std::to_string(client_fd) + " closed connection");
        return;
    }
    if (data_length != LEN_BYTES){
        ELOG("Data wasn't received correctly");
    }

    ssize_t read_buffer_value = *((int16_t*)len_size_buffer);
    LOG("Client" + std::to_string(client_fd) + "request received: initial value is "+ std::to_string(read_buffer_value));

    char* answer_buffer;


    if(read_buffer_value > 0){
        LOG("Client sending data, amount of bytes received: " + std::to_string(read_buffer_value));

        char buffer[read_buffer_value];
        data_length += read(client_fd, buffer,read_buffer_value);

        sdr_request request = *((sdr_request *)(buffer));
        answer_buffer = new char[LEN_BYTES + read_buffer_value];
       // try {
            listener->change_settings(request.center_frequency, request.frequency_width, request.sample_rate);

            listener->receive_data((void*)(answer_buffer + LEN_BYTES), read_buffer_value);

       // } catch () {

       // }


    }else{
        if (read_buffer_value == -1)
            LOG("Client is pinging, sending answer");
        else
            ELOG("Wrong initial value received");

        answer_buffer = new char[LEN_BYTES];
        memcpy(answer_buffer, len_size_buffer, LEN_BYTES);
        data_length = LEN_BYTES;
    }

    ssize_t sent_length = 0;
    while (sent_length != data_length) {
        ssize_t writen = write(client_fd, answer_buffer, (size_t) (data_length - sent_length));
        if (writen == -1) {
            ELOG("Failed writing to client");
            return;
        }
        sent_length += writen;
    }

    LOG("Data from client on socket " + std::to_string(client_fd) + " was returned");

}

/*void connection_handler::get_client_request(int client_fd) {
    const int BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];

    ssize_t data_length = read(client_fd, buffer, BUFFER_SIZE);
    if (data_length == -1) {
        ELOG("Failed reading from client");//REINTR!!
        return;
    }
    if (data_length == 0) {
        LOG("Client on socket " + std::to_string(client_fd) + " closed connection");
        return;
    }

    ssize_t sent_length = 0;
    while (sent_length != data_length) {//redircting data for now
        ssize_t writen = write(client_fd, buffer, (size_t) (data_length - sent_length));
        if (writen == -1) {
            ELOG("Failed writing to client");
            return;
        }
        sent_length += writen;
    }
    LOG("Data from client on socket " + std::to_string(client_fd) + " was returned");
}*/

void connection_handler::start_server(int port){

    int socket_fd = create_socket(port);
    int epoll_fd = create_epoll(socket_fd);

    epoll_event events[MAX_EVENTS_GRABBED_PER_TICK];
    while (true) {
        int event_amount = epoll_wait(epoll_fd, events, MAX_EVENTS_GRABBED_PER_TICK, -1);
        if (event_amount == -1) {
            ELOG("Failed waiting events");
                assert(false);
            }
            LOG("Got " + std::to_string(event_amount) + " events while waiting:");
            for (int i = 0; i < event_amount; i++) {
                if (events[i].data.fd == socket_fd) {//got new client
                    LOG(std::to_string(i+1) + ") Got new client");
                    new_client_accepting(socket_fd, epoll_fd);
                } else {
                    LOG(std::to_string(i+1) + ") Got new info from " + std::to_string(events[i].data.fd));
                    get_client_request(events[i].data.fd);
                }
            }
        }
}
