//
// Created by mbarbone on 12/1/21.
//

#include <bit>
#include <cmath>

#ifndef BENCHMARK_ELEMENTARY_FUNCTIONS_INC_LOGARITHMS_H_
#define BENCHMARK_ELEMENTARY_FUNCTIONS_INC_LOGARITHMS_H_

/* compute natural logarithm, maximum error 0.85089 ulps
 * source https://stackoverflow.com/questions/39821367/very-fast-approximate-logarithm-natural-log-function-in-c
 */
float approximate_logf(float a) {
    float m, r, s, t, i, f;
    int32_t e;

    e = (std::bit_cast<int32_t>(a) - 0x3f2aaaab) & 0xff800000;
    m = std::bit_cast<float>(std::bit_cast<int32_t>(a) - e);
    i = (float)e * 1.19209290e-7f;  // 0x1.0p-23
    /* m in [2/3, 4/3] */
    f = m - 1.0f;
    s = f * f;
    /* Compute log1p(f) for f in [-1/3, 1/3] */
    r = fmaf(0.230836749f, f, -0.279208571f);  // 0x1.d8c0f0p-3, -0x1.1de8dap-2
    t = fmaf(0.331826031f, f, -0.498910338f);  // 0x1.53ca34p-2, -0x1.fee25ap-2
    r = fmaf(r, s, t);
    r = fmaf(r, s, f);
    r = fmaf(i, 0.693147182f, r);  // 0x1.62e430p-1 // log(2)
    return r;
}

/* compute natural logarithm, maximum error 0.85089 ulps \
 * source https://stackoverflow.com/questions/39821367/very-fast-approximate-logarithm-natural-log-function-in-c
 */
float fast_logf(float a) {
    float i, m, r, s, t;
    int e;

    i = 0.0f;
    if (a < 1.175494351e-38f) {  // 0x1.0p-126
        a = a * 8388608.0f;      // 0x1.0p+23
        i = -23.0f;
    }
    e = (std::bit_cast<int32_t>(a) - std::bit_cast<int32_t>(0.666666667f)) & 0xff800000;
    m = std::bit_cast<float>(std::bit_cast<int32_t>(a) - e);
    i = fmaf((float)e, 1.19209290e-7f, i);  // 0x1.0p-23
    /* m in [2/3, 4/3] */
    m = m - 1.0f;
    s = m * m;
    /* Compute log1p(m) for m in [-1/3, 1/3] */
    r = -0.130310059f;              // -0x1.0ae000p-3
    t = 0.140869141f;               //  0x1.208000p-3
    r = fmaf(r, s, -0.121483512f);  // -0x1.f198b2p-4
    t = fmaf(t, s, 0.139814854f);   //  0x1.1e5740p-3
    r = fmaf(r, s, -0.166846126f);  // -0x1.55b36cp-3
    t = fmaf(t, s, 0.200120345f);   //  0x1.99d8b2p-3
    r = fmaf(r, s, -0.249996200f);  // -0x1.fffe02p-3
    r = fmaf(t, m, r);
    r = fmaf(r, m, 0.333331972f);   //  0x1.5554fap-2
    r = fmaf(r, m, -0.500000000f);  // -0x1.000000p-1
    r = fmaf(r, s, m);
    r = fmaf(i, 0.693147182f, r);  //  0x1.62e430p-1 // log(2)
    if (!((a > 0.0f) && (a < INFINITY))) {
        r = a + a;                              // silence NaNs if necessary
        if (a < 0.0f) r = INFINITY - INFINITY;  //  NaN
        if (a == 0.0f) r = -INFINITY;
    }
    return r;
}

/* compute natural logarithm,
 * source https://github.com/ekmett/approximate/blob/dc1ee7cef58a6b31661edde6ef4a532d6fc41b18/cbits/fast.c#L127
 */
constexpr float faster_logf(const float a) noexcept {
    return (std::bit_cast<int32_t>(a) - 1064866805) * 8.262958405176314e-8f; /* 1 / 12102203.0; */
}

#endif  // BENCHMARK_ELEMENTARY_FUNCTIONS_INC_LOGARITHMS_H_
