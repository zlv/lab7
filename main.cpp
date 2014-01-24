#include "PolStr.h"
#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <stdexcept>
#include <vector>
#include "func.h"
using namespace std;
double leftrect_uneven(Func *y, double *x, int n);
double leftrect_even(Func *y, double h, int n);
double leftrect_dynamical(Func *y, double h, int n, double);
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
        double *x=NULL;
        if (g=="u") {
            x = new double[n+1];
            for (int i=0; i<n+1; i++) {
                cin >> x[i];
            }
        }
        else {
            cin >> a >> b;
        }
        string s; //табличная, аналитическая
        getline(cin,s);
        getline(cin,s);
        double *y = NULL;
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
        Func f(g,a,b,x,s,y,sexpr_c);
        double deviation;
        if (g=="d")
            cin >> deviation;
        double result;
        if (m==1) {
            if (g=="e")
                result = leftrect_even(&f,(b-a)/n,n);
            else if (g=="u")
                result = leftrect_uneven(&f,x,n);
            else if (g=="d")
                result = leftrect_dynamical(&f,(b-a)/n,n,deviation);
        }
        if (m==2) {
            if (g=="e")
                result = rightrect_even(y,(b-a)/n,n);
            else if (g=="u")
                result = rightrect_uneven(y,x,n);
        }
        cout << result << endl;
    }
    catch (invalid_argument &e) {
        cerr << e.what() << endl;
    }
            
    return 0;
}
