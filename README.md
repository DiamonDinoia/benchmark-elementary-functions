## benchmark-elementary-functions

this repo aims to test the performance and accuracy different elementary functions (e.g. log, sin, cos..)

# logarithm results:

STD DOUBLE 65.458 us

STD SINGLE 50.739 us ERROR: AVG 1.38617e-08 MAX 5.86492e-08

FAST LOGF 47.7693 us ERROR: AVG 1.43832e-08 MAX 7.55761e-08

APPROXIMATE LOGF  2.5359 us ms ERROR: AVG 5.74123e-06 MAX 1.49805e-05

FASTER LOGF  1.14601 us ERROR: AVG  0.0125169 MAX 0.0401875
### On my machine only approximate logf and std::log seems to be worth

# sincos results:

STD SIN COS 34.9386 ms  
STD SINCOS 34.8707 ms

### It seems that gcc-11 optimises two different calls to sin and cos to the fast function sincos that computes both at the same time