#include "func.h"
#include <math.h>
using namespace std;
double trapeze_uneven(Func *y, double *x, int n) {
    double sum = 0;
    for (int i=0; i<n; i++) {
        sum += 0.5*(y->eval(i+1)+y->eval(i))*(x[i+1]-x[i]);
    }
    return sum;
}
double trapeze_even(Func *y, double h, int n) {
    double sum = 0;
    for (int i=0; i<n; i++) {
        sum += y->eval(i,h)+y->eval(i+1,h);
    }
    return sum*h*0.5;
}
