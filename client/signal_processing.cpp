#include "signal_processing.h"

#include "math.h"
#include "vector"


double sig_proc::enspec_logarithm_scale(double val_I, double val_Q){
    return 10.0 * std::log10(std::sqrt(val_I * val_I + val_Q * val_Q));
}

void sig_proc::convert_data(const char* raw_data, int rd_len, std::vector<double> * buffer_for_converted_data){
    for (int i = 0; i< rd_len; i+=2){
        int I_value = raw_data[i];
        int Q_value = raw_data[i+1];

        buffer_for_converted_data->resize(rd_len/2);

        double d = enspec_logarithm_scale(I_value, Q_value);
        buffer_for_converted_data->operator[](i/2) = d;
    }
}

