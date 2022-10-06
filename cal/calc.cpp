#include "calc.h"

bool calc::negAllow = false;

uint64_t calc::a = 0b0011111111100110001011100100001011111111001111110000101011010001;
double calc::ln2 = *(double*)&a;
uint64_t calc::b = 0b0100000000000101101111110000101010001011000101000101011101101010;
double calc::e = *(double*)&b;
uint64_t calc::c = 0b0100000000001001001000011111110001100000101100111000001100010001;
double calc::pi = *(double*)&c;

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
    return ln(x) / ln(a);
}

double calc::exp(double x)
{
    double absx = gen::abs(x);
    if (absx < 0.000000001) return 1;
    if (absx < 1) {
        double fact = 1;
        double nfact = 0;
        double nx = 1;
        double now;
        double sum = 1;
        do {
            nfact++;
            fact *= nfact;
            nx *= absx;
            now = nx / fact;
            sum += now;
        } while (now >= 0.0000000000001);
        if(x > 0) return sum;
        return 1 / sum;
    }
    if (x > 0) return gen::ipow(e, gen::floor(absx)) * exp(gen::mant(absx));
    return 1 / gen::ipow(e, gen::floor(absx)) * exp(gen::mant(absx));
}

void calc::exp1()
{
        double fact = 1;
        double nfact = 0;
        double now;
        double sum = 1;
        do {
            nfact++;
            fact *= nfact;
            now = 1 / fact;
            sum += now;
        } while (now >= 0.0000000000001);
        std::cout << gen::bin(sum);

}

double calc::pow(double x, double a)
{
    bool negAllow = true;
    if (!negAllow) {
        if (x < 0 && gen::abs(gen::mant(a)) > 0.0000000001) throw OutOfDomain();
    }else {
        if (x < 0 && gen::abs(gen::mant(a)) > 0.0000000001) return -exp(a * ln(gen::abs(x)));
    }
    if (gen::mant(a) < 0.00000001) return gen::ipow(x, a);
    return exp(a * ln(gen::abs(x)));
}

double calc::root(double a, double x)
{
    return pow(x, 1 / a);
}

double calc::sqrt(double x)
{
    return root(2, x);
}

double calc::arctg(double x)
{
    if (gen::abs(x) <= 1) {
        double nn = 1;
        double nx = gen::abs(x);
        double now;
        double sum = nx;
        double sign = -1;
        do {
            nn += 2;
            nx = nx * x * x;
            now = nx * sign / nn;
            sum += now;
            sign = -sign;
        } while (gen::abs(now) >= 0.000001);
        if (x < 0) return -sum;
        return sum;
    }
    if(x > 0) return 2 * arctg(x/(1 + sqrt(1 + x * x)));
    return - 2 * arctg(x / (1 + sqrt(1 + x * x)));
}

void calc::arctg1()
{
    double nn = 1;
    double now;
    double sum = 1;
    double sign = -1;
    do {
        nn += 2;
        now = sign / nn;
        sum += now;
        sign = -sign;
    } while (gen::abs(now) >= 0.000001);
    std::cout << gen::bin(4 * sum);
}

double calc::arcctg(double x)
{
    return pi / 2 - arctg(x);
}

double calc::arcsin(double x)
{
    return 2 * arctg(x / (1 + sqrt(1 - x * x)));
}

double calc::arccos(double x)
{
    return pi / 2 - arcsin(x);;
}

double calc::sin(double x)
{
    if (x < 0) return -sin(-x);
    if (x >= 2 * pi) return sin(x - 2 * pi * gen::floor(x / (2 * pi)));
    if (x >= pi) return -sin(x - pi);
    if (x >= pi / 2) return cos(x - pi / 2);
    double fact = 1;
    double nfact = 1;
    double now;
    double sign = -1;
    double sum = x;
    double nx = x;
    do {
        nfact+=2;
        nx = nx * x * x;
        fact *= nfact - 1;
        fact *= nfact;
        now = sign * nx / fact;
        sum += now;
        sign = -sign;
    } while (gen::abs(now) >= 0.0000000000001);
    return sum;
}

double calc::cos(double x)
{
    if (x < 0) return cos(-x);
    if (x >= 2 * pi) return cos(x - 2 * pi * gen::floor(x / (2 * pi)));
    if (x >= pi) return -cos(x - pi);
    if (x >= pi / 2) return sin(x - pi / 2);
    double fact = 1;
    double nfact = 0;
    double now;
    double sign = -1;
    double sum = 1;
    double nx = 1;
    do {
        nfact += 2;
        nx = nx * x * x;
        fact *= nfact - 1;
        fact *= nfact;
        now = sign * nx / fact;
        sum += now;
        sign = -sign;
    } while (gen::abs(now) >= 0.0000000000001);
    return sum;
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
    test1to1err(exp, ARR(4, 0.5, e), ARR(54.59815, 1.648721, 15.154262), 0.0001);
    test2to1err(pow, ARR(0.5, -0.5, 10), ARR(0.5, 0.5, 2.31), ARR(0.70710, -0.70710, 204.173794), 0.001);
    test1to1err(sin, ARR(pi/6, pi/4, pi+pi/6, 10), ARR(0.5, 0.7071067, -0.5, -0.54402111088), 0.0001)
    test1to1err(cos, ARR(pi / 6, pi / 4, pi + pi / 6, 10), ARR(0.866025, 0.707106, -0.866025, -0.83907152), 0.0001)
}
