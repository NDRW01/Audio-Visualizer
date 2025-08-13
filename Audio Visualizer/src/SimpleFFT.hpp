// SimpleFFT.hpp
#pragma once
#include <vector>

namespace SimpleFFT {
    void compute(const std::vector<float>& input, std::vector<float>& magnitudes, unsigned long size);
}

