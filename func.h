#ifndef FUNC_H_
#define FUNC_H_
#include <string>
#include "PolStr.h"
using namespace std;
class Func {
    string g_, s_;
    char *sexpr_c_;
    double a_, b_, *x_, *y_;
public:
    Func(const string &g, double a, double b, double *x, const string &s, double *y, char* sexpr_c) : g_(g), a_(a), b_(b), x_(x), s_(s), y_(y), sexpr_c_(sexpr_c) {}
    double eval(int i, double h = 0) {
        if (s_=="t") {
            return y_[i];
        }
        else {
            if (g_=="u") {
                return EvalPolStr(sexpr_c_,x_[i],0);
            }
            else {
                return EvalPolStr(sexpr_c_,a_+h*i,0);
            }
        }
    }
    ~Func() {
        if (g_=="u") {
            delete[] x_;
        }
        if (s_=="t") {
            delete[] y_;
        }
        else 
            delete[] sexpr_c_;
    }
};
#endif //FUNC_H_
