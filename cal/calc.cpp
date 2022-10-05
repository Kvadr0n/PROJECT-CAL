#include "calc.h"

bool calc::negAllow = false;

uint64_t calc::a = 0b0011111111100110001011100100001011111111001111110000101011010001;
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
        } while (now >= std::numeric_limits<double>::epsilon());
        if(x > 0) return sum;
        return 1 / sum;
    }
    if (x > 0) return gen::ipow(e, gen::floor(absx)) * exp(gen::mant(absx));
    return 1 / gen::ipow(e, gen::floor(absx)) * exp(gen::mant(absx));
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
    test1to1err(exp, ARR(4, 0.5, e), ARR(54.59815, 1.648721, 15.154262), 0.0001);
    test2to1err(pow, ARR(0.5, -0.5, 10), ARR(0.5, 0.5, 2.31), ARR(0.70710, -0.70710, 204.173794), 0.001);
}
