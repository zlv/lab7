#include "PolStr.h"
#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <stdexcept>
#include <vector>
using namespace std;
double leftrect_uneven(double *y, double *x, int n);
double leftrect_even(double *y, double h, int n);
double rightrect_uneven(double *y, double *x, int n);
double rightrect_even(double *y, double h, int n);
int main(int argc, char **argv) {
    try {
        int m; //формула интегрирования (в порядке их перечисления в п. 2.7.1), при m = 5 используется дополнительный метод;
        cin >> m;
        string g; //равномерная, неравномерная, динамическая
        getline(cin,g);
        getline(cin,g);
        int n; //количество интервалов интегрирования
        cin >> n;
        double a,b;
        if (g=="e")
            cin >> a >> b;
        double *x;
        if (g=="u") {
            x = new double[n+1];
            for (int i=0; i<n+1; i++) {
                cin >> x[i];
            }
        }
        string s; //табличная, аналитическая
        getline(cin,s);
        getline(cin,s);
        double *y;
        char *sexpr_c;
        if (s=="t") {
            y = new double[n+1];
            for (int i=0; i<n+1; i++) {
                cin >> y[i];
            }
        }
        else {
            sexpr_c = new char[1024+1];
            string sexpr;
            getline(cin,sexpr);
            strcpy(sexpr_c,sexpr.c_str());
            sexpr_c=CreatePolStr(sexpr_c,0);
        }
        double deviation;
        cin >> deviation;
        double result;
        if (m==1) {
            if (g=="e")
                result = leftrect_even(y,(b-a)/n,n);
            else if (g=="u")
                result = leftrect_uneven(y,x,n);
        }
        if (m==2) {
            if (g=="e")
                result = rightrect_even(y,(b-a)/n,n);
            else if (g=="u")
                result = rightrect_uneven(y,x,n);
        }
        cout << result << endl;
        if (g=="u") {
            delete[] x;
        }
        if (s=="t") {
            delete[] y;
        }
        if (s=="a") {
            delete[] sexpr_c;
        }
    }
    catch (invalid_argument &e) {
        cerr << e.what() << endl;
    }
            
    return 0;
}
