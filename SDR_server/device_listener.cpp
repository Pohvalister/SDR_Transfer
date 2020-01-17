#include <cerrno>
#include <cassert>
#include <iostream>
#include <cstring>

#include "device_listener.h"

#define LIST_LOG true

#ifdef LIST_LOG
#define LOG(a) std::cout<<"listener message: "<<(a)<<'\n'
#else
#define LOG(a)
#endif

#define ELOG(a) std::cout<<"\n--\n"<<(a)<<", error:\n"<<'['<<std::string(strerror(errno))<<']'<<"\n--\n\n"


device_listener::device_listener(){

}
device_listener::~device_listener(){
    rtlsdr_close(device_ptr);
}


int device_listener::connect_to_device(int device_index){

    if (device_index == DEFAULT_DEVICE_INDEX){
        std::string def = "0";
        char* p = new char[def.size()+1];
        std::copy(def.begin(),def.end(),p);
        p[def.size()]='\0';

        device_index = verbose_device_search(p);

        delete [] p;

    }
    if (rtlsdr_open(&device_ptr, device_index)){
        ELOG("Error opening rtlsdr device ("+ std::to_string(device_index) + ")");
        return -1;
    }
    return 0;
}
//returns required buffer length to write data from "device_listener::receive_data"
int device_listener::change_settings(int center_frequency, int frequency_width, int sample_rate){
    if (center_frequency != device_center_frequency)
        rtlsdr_set_center_freq(device_ptr, center_frequency);
    if (sample_rate != device_sample_rate)
        rtlsdr_set_sample_rate(device_ptr, sample_rate);
    if (frequency_width != device_frequency_width){
        int val = 1;
        //rtlsdr_get_tuner_gains(device_ptr, &val);
        ;//TODO
    }
    return 0;
}

int device_listener::receive_data(void* buffer, int buffer_size){

    if (rtlsdr_reset_buffer(device_ptr)){
        LOG("WARNING: Failed to reset buffers\n");
    }

    int received_size;
    return rtlsdr_read_sync(device_ptr,buffer,buffer_size, &received_size);
}

int device_listener::receive_data(void *buffer){
    return receive_data(buffer, device_buffer_size);
}
