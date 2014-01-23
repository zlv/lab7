double rightrect_uneven(double *y, double *x, int n) {
    double sum = 0;
    for (int i=0; i<n; i++) {
        sum += y[i+1]*(x[i+1]-x[i]);
    }
    return sum;
}
double rightrect_even(double *y, double h, int n) {
    double sum = 0;
    for (int i=0; i<n; i++) {
        sum += y[i+1];
    }
    return sum*h;
}
