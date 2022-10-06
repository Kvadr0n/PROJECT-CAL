#include "num.h"


double num::derive(double x)
{
    double h = 1;
    double a = gen::order(x) / 2 - 26;
    a = a < -1023 ? -1023 : a;
    gen::exput(h, a);
    try {
        return gen::x2((2 * calc::sin(x + h) - 2 * calc::sin(x - h)), -a - 1);
    }
    catch (OutOfDomain()) {
        return gen::x2((2 * calc::sin(x + h) - 2 * calc::sin(x)), -a);
    }
}
double num::derive2(double x)
{
    double h = 1;
    double a = gen::order(x) / 2 - 26;
    a = a < -1023 ? -1023 : a;
    gen::exput(h, a);
    try {
        return gen::x2((calc::sin(x + h) + calc::ln(x + h) - calc::sin(x - h) - calc::ln(x - h)), -a - 1);
    }
    catch (OutOfDomain()) {
        return gen::x2((calc::sin(x + h) + calc::ln(x + h) - calc::sin(x) - calc::ln(x)), -a);
    }
}
double num::derive3(double x)
{
    double h = 1;
    double a = gen::order(x) / 2 - 26;
    a = a < -1023 ? -1023 : a;
    gen::exput(h, a);
    try {
        return gen::x2((calc::exp(x + h) - calc::exp(x - h)), -a - 1);
    }
    catch (OutOfDomain()) {
        return gen::x2((calc::exp(x + h) - calc::exp(x)), -a);
    }
}

double num::derive(double x, unsigned char n)
{
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
    std::cout << derive3(2.6);
    //Тесты писать сюда
    //Обратить внимание на макросы test1to1errfunc и test2to1errfunc в testmacros.h
}
