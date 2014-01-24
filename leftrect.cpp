#include "func.h"
#include <math.h>
using namespace std;
double leftrect_uneven(Func *y, double *x, int n) {
    double sum = 0;
    for (int i=0; i<n; i++) {
        sum += y->eval(i)*(x[i+1]-x[i]);
    }
    return sum;
}
double leftrect_even(Func *y, double h, int n) {
    double sum = 0;
    for (int i=0; i<n; i++) {
        sum += y->eval(i,h);
    }
    return sum*h;
}
