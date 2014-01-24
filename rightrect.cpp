#include "func.h"
#include <math.h>
using namespace std;
double rightrect_uneven(Func *y, double *x, int n) {
    double sum = 0;
    for (int i=0; i<n; i++) {
        sum += y->eval(i+1)*(x[i+1]-x[i]);
    }
    return sum;
}
double rightrect_even(Func *y, double h, int n) {
    double sum = 0;
    for (int i=0; i<n; i++) {
        sum += y->eval(i+1,h);
    }
    return sum*h;
}
