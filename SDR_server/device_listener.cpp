#include "rtl-sdr.h"
#include "convenience.h"

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


device_listener::device_listener(int device_index){
    if (device_index == DEFAULT_DEVICE_INDEX){
        device_index = verbose_device_search("0");
    }
    if (rtlsdr_open(&device_ptr, device_index)){
        ELOG("Error opening rtlsdr device ("+ std::to_string(device_index) + ")");
    }
}
//returns required buffer length to write data from "device_listener::receive_data"
int device_listener::change_settings(int center_frequency, int frequency_width, int sample_rate){
    if (center_frequency != device_center_frequency)
        rtlsdr_set_center_freq(device_ptr, center_frequency);
    if (sample_rate != device_sample_rate)
        rtlsdr_set_sample_rate(device_ptr, sample_rate);
    if (frequency_width != device_frequency_width)
        ;//TODO
}

void device_listener::receive_data(void* buffer, int buffer_size){
    if (rtlsdr_reset_buffer(device_ptr))
        ELOG("Failed to reset device buffer");
    int received_size;
    rtlsdr_read_sync(device_ptr,buffer,buffer_size, &received_size);
}

void device_listener::receive_data(void *buffer){
    receive_data(buffer, device_buffer_size);
}
