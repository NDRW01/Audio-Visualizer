#ifndef KISS_FFT_H
#define KISS_FFT_H

#include <vector>
#include <cstddef>  // for size_t

class SimpleFFT {
public:
    static void compute(const std::vector<float>& in, std::vector<float>& out, size_t size);
};

#endif

