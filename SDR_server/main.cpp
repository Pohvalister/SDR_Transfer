#include <iostream>
#include "connection_handler.h"

int main() {
    std::cout << "Server preparing to start" << std::endl;

    connection_handler server;
    server.start_server(2289);

    return 0;
}
