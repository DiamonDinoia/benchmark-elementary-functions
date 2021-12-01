//
// Created by mbarbone on 12/1/21.
//

#ifndef BENCHMARK_ELEMENTARY_FUNCTIONS_INC_SINCOS_H_
#define BENCHMARK_ELEMENTARY_FUNCTIONS_INC_SINCOS_H_

#define _GNU_SOURCE /* See feature_test_macros(7) */
#include <math.h>

template<typename T>
void mySinCos(const T x, T& sin, T& cos){
    sin = std::sin(x);
    cos = std::cos(x);
}

#endif  // BENCHMARK_ELEMENTARY_FUNCTIONS_INC_SINCOS_H_
