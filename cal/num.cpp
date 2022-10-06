#include "num.h"


double num::derive(double x)
{
    double h = 1;
    double a = gen::order(x) / 2 - 26;
    a = a < -1023 ? -1023 : a;
    gen::exput(h, a);
    try {
        return (2 * calc::sin(x + h) - 2 * calc::sin(x - h)) / (2 * h);
    }
    catch(OutOfDomain()) {

        try {
            return gen::x2((2 * calc::sin(x + h) - 2 * calc::sin(x - h)), -a - 1);
        }
        catch (OutOfDomain()) {
            return gen::x2((2 * calc::sin(x + h) - 2 * calc::sin(x)), -a);
        }
    }
}
double num::derive2(double x)
{
    double h = 1;
    double a = gen::order(x) / 2 - 26;
    a = a < -1023 ? -1023 : a;
    gen::exput(h, a);
    try {
        return (calc::sin(x + h) + calc::ln(x + h) - calc::sin(x - h) - calc::ln(x - h)) / (2 * h);
    }
    catch (OutOfDomain()) {

        try {
            return gen::x2((calc::sin(x + h) + calc::ln(x + h) - calc::sin(x - h) - calc::ln(x - h)), -a - 1);
        }
        catch (OutOfDomain()) {
            return gen::x2((calc::sin(x + h) + calc::ln(x + h) - calc::sin(x) - calc::ln(x)), -a);
        }
    }
}
double num::derive3(double x)
{
    double h = 1;
    double a = gen::order(x) / 2 - 26;
    a = a < -1023 ? -1023 : a;
    gen::exput(h, a);
    try {
        return (calc::exp(x + h) - calc::exp(x - h)) / (2 * h);
    }
    catch (OutOfDomain()) {
        try {
            return gen::x2((calc::exp(x + h) - calc::exp(x - h)), -a - 1);
        }
        catch (OutOfDomain()) {
            return gen::x2((calc::exp(x + h) - calc::exp(x)), -a);
        }
    }
}

double num::derive(double x, unsigned char n)
{
    if (n < 1 || n > 255) throw OutOfDomain();
    return 0.0;
}

double num::solve(double a, double b)
{
    return 0.0;
}

double num::integrate(double a, double b)
{
    return 0.0;
}

void num::test()
{
    using namespace num;
    test1to1err(derive, ARR(1, 2.6, 14.9), ARR(1.080604, -1.71378, -1.38194), 0.0001);
    test1to1err(derive2, ARR(1.1, 2.6, 14.9), ARR(1.36269, -0.472273, -0.623859), 0.0001);
    test1to1err(derive3, ARR(1.1, 2.6, 5.7), ARR(3.00417, 13.4637, 298.8674), 0.0001);
}
