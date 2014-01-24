#include "PolStr.h"
#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <stdexcept>
#include <vector>
#include "func.h"
#include "dynamical.h"
using namespace std;
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
        int k;
        double eps0;
        if (g=="d") {
            result = dynamical(&f,(b-a)/n,n,deviation,k,eps0,m);
        }
        else {
            if (m==1) {
                if (g=="e")
                    result = leftrect_even(&f,(b-a)/n,n);
                else if (g=="u")
                    result = leftrect_uneven(&f,x,n);
            }
            if (m==2) {
                if (g=="e")
                    result = rightrect_even(&f,(b-a)/n,n);
                else if (g=="u")
                    result = rightrect_uneven(&f,x,n);
            }
            if (m==4) {
                if (g=="e")
                    result = simpson_even(&f,(b-a)/n,n);
                else if (g=="u")
                    result = simpson_uneven(&f,x,n);
            }
        }
        if (g=="d")
            cout.precision(-log10(deviation));
        cout << "Integral: "<< result << endl;
        if (g=="d") {
            cout << "Iteration count: " << k << "\neps0: " << eps0 << endl;
        }
    }
    catch (invalid_argument &e) {
        cerr << e.what() << endl;
    }
            
    return 0;
}
