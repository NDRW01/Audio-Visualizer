#include "SimpleFFT.hpp"
#include <cmath>
extern "C" {
    #include "kiss_fft.h"
}
#include <vector>

void SimpleFFT::compute(const std::vector<float>& input, std::vector<float>& magnitudes, unsigned long size) {
    if (input.size() < size) return;

    kiss_fft_cfg cfg = kiss_fft_alloc(size, 0, nullptr, nullptr);
    std::vector<kiss_fft_cpx> in(size), out(size);

    for (size_t i = 0; i < size; ++i) {
        in[i].r = input[i];
        in[i].i = 0;
    }

    kiss_fft(cfg, in.data(), out.data());
    free(cfg);

    magnitudes.resize(size);
    for (size_t i = 0; i < size; ++i)
        magnitudes[i] = std::sqrt(out[i].r * out[i].r + out[i].i * out[i].i);
}

