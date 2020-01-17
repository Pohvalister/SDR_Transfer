#ifndef SIGNAL_PROCESSING_H
#define SIGNAL_PROCESSING_H

#include "vector"

namespace sig_proc {

void convert_data(const char * raw_data, int rd_len, std::vector<double> * buffer_for_converted);

double enspec_logarithm_scale(double val_I, double val_Q);


}

#endif // SIGNAL_PROCESSING_H

