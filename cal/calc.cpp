#include "calc.h"

bool calc::negAllow = false;

uint64_t a = 0b0011111111100110001011100100001011111111001111110000101011010001;
double calc::ln2 = *(double*)&a;
double calc::e =   2.718281;
double calc::pi =  3.141592;

void calc::ln_22()
{
    double sum = 1;
    double n = 1;
    double now = 5000;
    double sign = -1;
    while (abs(now) >= 0.000000001) {
        n++;
        now = sign / n;
        sum += now;
        sign = -sign;
    }
    std::cout << gen::bin(sum);
}


double calc::ln(double x)
{
    if (x < 0) throw(OutOfDomain());
    double y = x - 1;
    double exp;
    double nx;
    if (y > 0) {
        exp = gen::exput(x, -1) * (- 1);
        return exp * ln2 + ln(x);
    }
    double sum = 0;
    double n = 0;
    double now;
    double sign = 1;
    double ny = 1;
    do {
        n++;
        ny *= y;
        now = (sign / n) * ny;
        sum += now;
        sign = -sign;
    } while (abs(now) >= 0.0000001);
    return sum;
}

double calc::log(double a, double x)
{
    return 0.0;
}

double calc::exp(double x)
{
    return 0.0;
}

double calc::pow(double x, double a)
{
    return 0.0;
}

double calc::root(double a, double x)
{
    return 0.0;
}

double calc::sqrt(double x)
{
    return 0.0;
}

double calc::arctg(double x)
{
    return 0.0;
}

double calc::arcctg(double x)
{
    return 0.0;
}

double calc::arcsin(double x)
{
    return 0.0;
}

double calc::arccos(double x)
{
    return 0.0;
}

double calc::sin(double x)
{
    return 0.0;
}

double calc::cos(double x)
{
    return 0.0;
}

double calc::tg(double x)
{
    return 0.0;
}

double calc::ctg(double x)
{
    return 0.0;
}

void calc::test()
{
    using namespace calc;
	//Тесты писать сюда
	//Обратить внимание на макросы test1to1err и test2to1err в testmacros.h
    //ln
    test1to1err(ln, ARR(4, 0.5, e), ARR(1.38629, -0.69314, 1), 0.00001);

}
