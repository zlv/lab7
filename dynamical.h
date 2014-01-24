#ifndef RECT_H_
#define RECT_H_
class Func;
double dynamical(Func *y, double h, int n, double eps, int&, double&,int);
double leftrect_uneven(Func *y, double *x, int n);
double leftrect_even(Func *y, double h, int n);
double rightrect_uneven(Func *y, double *x, int n);
double rightrect_even(Func *y, double h, int n);
double simpson_uneven(Func *y, double *x, int n);
double simpson_even(Func *y, double h, int n);
#endif
