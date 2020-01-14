#ifndef RECEIVER_LISTENER_H
#define RECEIVER_LISTENER_H

#include "rtl-sdr.h"

extern "C"{
    #include "convenience.h"
}

//sdr receiver wrapper
struct device_listener{

    //DEFAULT_DEVICE - listener will try to find devic by its own
    device_listener();
    ~device_listener();

    int connect_to_device(int device_index = DEFAULT_DEVICE_INDEX);

    //set device receive settings
    //returns buffer size required for data
    int change_settings(int center_frequency, int frequency_width, int sample_rate);

    int receive_data(void* buffer);
    int receive_data(void* buffer, int buffer_size);

private:

    static const int DEFAULT_DEVICE_INDEX = 0;
    //pointer to device to listen to
    rtlsdr_dev_t *device_ptr;

    //device receive settings
    int device_center_frequency;
    int device_frequency_width;
    int device_sample_rate;

    int device_buffer_size;

};

#endif // RECEIVER_LISTENER_H
