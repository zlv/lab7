#ifndef UTIL_H_
#define UTIL_H_
#include <math.h>
bool equal(double a, double b, double eps) {
    return fabs(a-b)<eps;
}
bool lessthen(double a, double b, double eps) {
    return !equal(a,b,eps) && a<b;
}
#endif
