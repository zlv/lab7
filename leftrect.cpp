#include "func.h"
#include "util.h"
#include <math.h>
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
double leftrect_dynamical(Func *y, double h, int n, double eps) {
    const double alpha = 1.3;
    double i0 = leftrect_even(y,h,n);
    while (1) {
        int n1 = ceil(n*alpha);
        h = h*n/n1;
        double i1 = leftrect_even(y,h,n1);
        if (!equal(i1,0.,eps/1000)) {
            if (lessthen(fabs((i1-i0)/i1),eps,eps/1000))
                break;
        }
        else {
            if (lessthen(fabs(i1-i0),eps,eps/1000))
                break;
        }
    }
}
