
#include "sincos.h"

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <random>

#include "utils.h"
using real_type = double;

std::vector<real_type> inputs;

std::vector<real_type> sinResult;
std::vector<real_type> cosResult;

TEST_CASE("SINCOS") {
    sinResult.resize(TESTS);
    cosResult.resize(TESTS);
    BENCHMARK("STD SIN COS") {
        for (int i = 0; i < TESTS; ++i) {
            mySinCos(inputs[i], sinResult[i], cosResult[i]);
        }
    };
    BENCHMARK("STD SINCOS") {
        for (int i = 0; i < TESTS; ++i) {
            sincos(inputs[i], &sinResult[i], &cosResult[i]);
        }
    };
}

int main(int argc, char *argv[]) {
    auto seed = std::random_device()();
    std::cout << "Seed " << seed << std::endl;
    std::default_random_engine rng{seed};
    std::uniform_real_distribution<real_type> distribution{0, 2 * M_PI};
    inputs.resize(TESTS);
    for (int i = 0; i < TESTS; ++i) {
        inputs[i] = distribution(rng);
    }
    return Catch::Session().run(argc, argv);
}