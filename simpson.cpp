#include <math.h>
double simpson_uneven(double *y, double *x, int n) {
    double sum = 0;
    for (int i=0; i<n/2; i++) {
        double h1 = x[i*2+2]-x[i*2+1];
        double h0 = x[i*2+1]-x[i*2];
        sum += (x[i*2+2]-x[i*2])/6/h1/h0*(h1*(2*h0-h1)*y[i*2]+pow(h1+h0,2)*y[i*2+1]+h0*(2*h1-h0)*y[i*2+2]);
    }
    return sum;
}
double simpson_even(double *y, double h, int n) {
    double sum = 0;
    for (int i=0; i<n/2; i++) {
        sum += 4*y[2*i+1]+2*y[2*i];
    }
    return (y[0]+sum+y[n])*h/3;
}
