//
// Created by mbarbone on 12/1/21.
//

#ifndef BENCHMARK_ELEMENTARY_FUNCTIONS_INC_UTILS_H_
#define BENCHMARK_ELEMENTARY_FUNCTIONS_INC_UTILS_H_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

constexpr auto TESTS = 16384;

void checkError(const std::vector<double> &reference, const std::vector<float> &result) {
    double error     = 0;
    double max_error = 0;
    for (int i = 0; i < TESTS; ++i) {
        const auto current_result    = std::abs(static_cast<double>(result[i]));
        const auto current_reference = std::abs(static_cast<double>(reference[i]));
        const auto current_error =
            std::abs(current_reference - current_result) / std::max({current_reference, current_result, 1.});
        error += current_error;
        max_error = std::max(max_error, current_error);
    }
    std::cout << "ERROR: AVG  " << (error / TESTS) << " MAX " << max_error << std::endl;
}

#endif  // BENCHMARK_ELEMENTARY_FUNCTIONS_INC_UTILS_H_
