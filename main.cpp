#include "PolStr.h"
#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <stdexcept>
#include <vector>
using namespace std;
void solve(double *x, double *y, int n, int k, double **l, double bI, double bN);
double eval(double *x, double **result, int n, int k, double xres);
int main(int argc, char **argv) {
    try {
        int k; // порядок сплайна (1 – линейный, 2 – параболический, 3 – кубический)
        int n; //количество сплайнов
        
        cin >> k >> n;
        double *x = new double[n+1];
        double *y = new double[n+1];
        double aI,aN;
        for (int i=0; i<n+1; i++) {
            cin >> x[i];
        }
        for (int i=0; i<n+1; i++) {
            cin >> y[i];
        }
        if(k==2||k==3)
            cin>>aI>>aN;
        int m; //количество интервалов в результирующей сетке (т.е. количество узлов – m + 1, что сделано для унификации с узлами исходной сетки);
        cin >> m;
        double *xres = new double[m+1];
        for (int i=0; i<m+1; i++) {
            cin >> xres[i];
        }
        string t; //'y' -- expression known, 'n' -- otherwise
        getline(cin,t);
        getline(cin,t);
        string sexpr;
        char* sexpr_c = new char[1024+1];
        if (t=="y") {
            getline(cin,sexpr);
            strcpy(sexpr_c,sexpr.c_str());
            sexpr_c=CreatePolStr(sexpr_c,0);
            
            
        }
        double **result = new double*[n];
        for (int i=0; i<n; i++) {
            result[i] = new double[k+1];
        }
        solve(x,y,n,k,result,aI,aN);
        for (int i=0; i<n; i++) {
            cerr << i << ") ";
            for (int j=0; j<k+1; j++) {
                cerr << result[i][j] << ' ';
            }
            cerr << "; " << x[i] << " <= x <= " << x[i+1] << endl;
        }
        double *resnum = new double[m+1];
        for (int i=0; i<m+1; i++) {
            double resT=eval(x,result,n,k,xres[i]);
            resnum[i] = resT;
            cout << "x" << i << " S" << "(" << xres[i] << ") = " << resT << endl;
        }
        if (t=="y") {
                double *resfuncnum = new double[m+1];
                double sum = 0;
                for (int i=0; i<m+1; i++) {
                        resfuncnum[i]=EvalPolStr(sexpr_c,xres[i],0);
                        sum += sqrt(pow(resnum[i]-resfuncnum[i],2));
                }
                sum /= m+1;
                cout << "Deviation: " << sum << endl;
                delete[] resfuncnum;
        }
        for (int i=0; i<n; i++) {
            delete[] result[i];
        }
        delete[] result;
        delete[] resnum;
        delete[] x;
        delete[] y;
        delete[] xres;
    }
    catch (invalid_argument &e) {
        cerr << e.what() << endl;
    }
            
    return 0;
}

void tri_matrix_alg(int n, double **a, double *x, double *b) {
    double *r = new double[n];
    double *v = new double[n];
    v[n-1] = a[n-1][n-1];
    r[n-1] = b[n-1];
    for (int i=n-2; i>=0; i--) {
        v[i] = a[i][i]-a[i][i+1]*a[i+1][i]/v[i+1];
        r[i] = b[i]-a[i][i+1]*r[i+1]/v[i+1];
    }
    for (int i=0; i<n; i++) {
        double res = r[i];
        if (i!=0) res -= a[i][i-1]*x[i-1];
        x[i] = res/v[i];
    }
    delete[] v;
    delete[] r;
}

void findM(double *x, double *y, double *m, int n) {
    double **a = new double*[n-1];
    double *g = new double[n-1];
    for (int i=0; i<n-1; i++) {
        a[i] = new double[n-1];
    }
    for (int i=0; i<n-1; i++) {
        a[i][i] = (x[i+2]-x[i])/3;
        if (i!=n-2)
            a[i][i+1] = a[i+1][i] = (x[i+2]-x[i+1])/6;
        g[i] = (y[i+2]-y[i+1])/(x[i+2]-x[i+1])-(y[i+1]-y[i])/(x[i+1]-x[i]);
        if (i==0) {
            g[i] -= m[i]*(x[i+1]-x[i])/6;
        }
        if (i==n-2) {
            g[i] -= m[n]*(x[n]-x[n-1])/6;
        }
    }
    tri_matrix_alg(n-1,a,&m[1],g);
    for (int i=0; i<n-1; i++) {
        delete a[i];
    }
    delete g;
    delete a;
}

void solve(double *x, double *y, int n, int k, double **l,double bI,double bN) {
    if (k==1) {
        for (int i=0; i<n; i++) {
            double a = y[i];
            double b = (y[i+1]-y[i])/(x[i+1]-x[i]);
            l[i][0] = b;
            l[i][1] = a-b*x[i];
            cout << a << ' ' << b << "; " << x[i] << " <= x <= " << x[i+1] << endl;
        }
    }
    else if(k==2){
        
        int j=n;
        double *b=new double[n+1];
        bool zero=1;
        if(int(bI)==0){
            zero=0;
            j=0;
        }
        b[j]=bN;
//        cout<<n;
        for(int i=0;i<n;i++) {
        int ind=i-zero*(n);
        int ip=abs(ind+1);
        int im=abs(ind);
        double delt=2*(y[ip]-y[im])/(x[ip]-x[im]);
        
        b[ip]=delt-b[im];
        }
        for (int i=0; i<n; i++) {
            double a = y[i];
            double bb = b[i];
            double c = (b[i+1]-b[i])/2/(x[i+1]-x[i]);
            l[i][0] = c;
            l[i][1] = bb-2*c*x[i];
            l[i][2] = a-bb*x[i]+c*x[i]*x[i];
            cout << a << ' ' << bb << ' ' << c << "; " << x[i] << " <= x <= " << x[i+1] << endl;
        }
        delete[] b;
    }
    else if (k==3) {
        double *m = new double[n+1];
        m[0] = bI;
        m[n] = bN;
        for (int i=0; i<n+1; i++)
            cerr << m[i] << ' ';
        cerr << endl;
        if (n!=1)
            findM(x,y,m,n);
        for (int i=0; i<n; i++) {
            double dx = (x[i+1]-x[i]);
            double a = y[i];
            double b = (y[i+1]-y[i])/dx-dx*(2*m[i]+m[i+1])/6;
            double c = m[i]/2;
            double d = (m[i+1]-m[i])/6/dx;
            l[i][0] = d;
            l[i][1] = c-3*d*x[i];
            l[i][2] = b-2*c*x[i]+3*d*pow(x[i],2);
            l[i][3] = a-b*x[i]+c*pow(x[i],2)-d*pow(x[i],3);
            cout << a << ' ' << b << ' ' << c << ' ' << d << "; " << x[i] << " <= x <= " << x[i+1] << endl;
        }
        delete[] m;
    }
}

double eval(double *x, double **result, int n, int k, double xres) {
    int i = 0;
    for (; i<n; i++) {
        if (xres<x[i+1] || i==n-1)
            break;
    }
    int index_in_spline = i;
    cerr << "index in spline : " << i << endl;
    double sum = 0;
    for (i=0; i<k+1; i++) {
        sum += result[index_in_spline][i]*pow(xres,k-i);
    }
    return sum;
}
