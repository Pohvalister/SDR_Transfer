#include <iostream>
#include "connection_handler.h"
#include "device_listener.h"


int main() {



    std::cout << "Server preparing to start" << std::endl;

    device_listener listener;
    if (listener.connect_to_device()){
        std::cout<<"Device connection failed"<<'\n';
    }else{
        listener.change_settings(95000000,2400000,2000000);
        int buff_size = 10;

        char* buffer[buff_size];
        listener.receive_data(buffer,buff_size);

        std::cout<<"output"<<'\n';
        for (int i=0; i< 4; i++)
            std::cout<<buffer[i]<<'\n';
        //connection_handler server;
        //server.start_server(2289, &listener);
    }
    return 0;
}
