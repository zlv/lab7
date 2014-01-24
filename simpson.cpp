#include <math.h>
#include "func.h"
double simpson_uneven(Func *y, double *x, int n) {
    double sum = 0;
    for (int i=0; i<n/2; i++) {
        double h1 = x[i*2+2]-x[i*2+1];
        double h0 = x[i*2+1]-x[i*2];
        sum += (x[i*2+2]-x[i*2])/6/h1/h0*(h1*(2*h0-h1)*y->eval(i*2)+pow(h1+h0,2)*y->eval(i*2+1)+h0*(2*h1-h0)*y->eval(i*2+2));
    }
    return sum;
}
double simpson_even(Func *y, double h, int n) {
    double sum = 0;
    for (int i=0; i<n/2; i++) {
        sum += 4*y->eval(i*2+1,h)+2*y->eval(i*2,h);
    }
    return (y->eval(0,h)+sum+y->eval(n,h))*h/3;
}
