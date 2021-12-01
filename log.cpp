//
// Created by mbarbone on 12/1/21.
//
#include "utils.h"
#include "logarithms.h"

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <random>

using real_type = float;

std::vector<real_type> inputs;

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
    auto seed = std::random_device()();
    std::cout << "Seed " << seed << std::endl;
    std::default_random_engine rng{seed};
    std::uniform_real_distribution<real_type> distribution{0, 1};
    inputs.resize(TESTS);
    for (int i = 0; i < TESTS; ++i) {
        inputs[i] = distribution(rng);
    }
    return Catch::Session().run(argc, argv);
}