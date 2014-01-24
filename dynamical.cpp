#include "dynamical.h"
#include "util.h"
double dynamical(Func *y, double h, int n, double eps, int& k, double& eps0, int m) {
    const double alpha = 1.3;
    double i0;
    if (m==1)
       i0 = leftrect_even(y,h,n);
    else if (m==2)
       i0 = rightrect_even(y,h,n);
    else if (m==4)
       i0 = simpson_even(y,h,n);
    k = 0;
    while (1) {
        int n1 = ceil(n*alpha);
        h = h*n/n1;
        double i1;
        if (m==1)
           i1 = leftrect_even(y,h,n1);
        else if (m==2)
           i1 = rightrect_even(y,h,n1);
        else if (m==4)
           i1 = simpson_even(y,h,n1);
        k++;
        if (!equal(i1,0.,eps/1000)) {
            eps0 = fabs((i1-i0)/i1);
            if (lessthen(eps0,eps,eps/1000))
                return i1;
        }
        else {
            eps0 = fabs(i1-i0);
            if (lessthen(eps0,eps,eps/1000))
                return i1;
        }
        n = n1;
        i0 = i1;
    }
}
