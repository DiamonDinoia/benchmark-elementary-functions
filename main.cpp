//
// Created by mbarbone on 12/1/21.
//

#include "logarithms.h"

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <random>

constexpr auto TESTS = 16384;

#ifdef SINGLE
using real_type = float;
#else
using real_type = double;
#endif

std::vector<real_type> inputs;

void checkError(const std::vector<double> &reference, const std::vector<float> &result) {
    double error     = 0;
    double max_error = 0;
    for (int i = 0; i < TESTS; ++i) {
        auto current_result    = std::abs(static_cast<double>(result[i]));
        auto current_reference = std::abs(static_cast<double>(reference[i]));
        const auto current_error =
            std::abs(current_reference - current_result) / std::max({current_reference, current_result, 1.});
        error += current_error;
        max_error = std::max(max_error, current_error);
    }
    std::cout << "ERROR: AVG  " << (error / TESTS) << " MAX " << max_error << std::endl;
}

std::vector<double> reference;
std::vector<float> result;
TEST_CASE("Logarithm") {
    reference.resize(TESTS);
    BENCHMARK("STD DOUBLE") {
        for (int i = 0; i < TESTS; ++i) {
            reference[i] = std::log(static_cast<double>(inputs[i]));
        }
    };
    result.resize(TESTS);
    BENCHMARK("STD SINGLE") {
        for (int i = 0; i < TESTS; ++i) {
            result[i] = std::log(inputs[i]);
        }
    };
    checkError(reference, result);
    BENCHMARK("FAST LOGF") {
        for (int i = 0; i < TESTS; ++i) {
            result[i] = fast_logf(inputs[i]);
        }
    };
    checkError(reference, result);
    BENCHMARK("APPROXIMATE LOGF") {
        for (int i = 0; i < TESTS; ++i) {
            result[i] = approximate_logf(inputs[i]);
        }
    };
    checkError(reference, result);
}

int main(int argc, char *argv[]) {
    // your setup ...
    auto seed = std::random_device()();
    std::cout << "Seed " << seed << std::endl;
    std::default_random_engine rng{seed};
    std::uniform_real_distribution<real_type> distribution{0, 1};
    inputs.resize(TESTS);
    for (int i = 0; i < TESTS; ++i) {
        inputs[i] = distribution(rng);
    }
    int result = Catch::Session().run(argc, argv);

    return result;
}