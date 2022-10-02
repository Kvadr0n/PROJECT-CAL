#include "gen.h"

short gen::exput(double& x, short a)
{
	return 0;
}

double gen::x2(double x, short a)
{
	return 0.0;
}

double gen::sgn(double x)
{
	return 0.0;
}

double gen::abs(double x)
{
	return 0.0;
}

double gen::floor(double x)
{
	return 0.0;
}

double gen::mant(double x)
{
	return 0.0;
}

double gen::ceil(double x)
{
	return 0.0;
}

double gen::round(double x)
{
	return 0.0;
}

double gen::ipow(double x, short a)
{
	return 0.0;
}

std::string bin(double x)
{

	return;
}

void gen::test()
{
	using namespace gen;
	//АНДРЕЙ - ТЕСТ БИНАРНЫХ СТРОК
	test1to1str(bin, ARR(0, 1, 1.25, -2), ARR
		(
			"0b0000000000000000000000000000000000000000000000000000000000000000",
			"0b0011111111110000000000000000000000000000000000000000000000000000",
			"0b0011111111110100000000000000000000000000000000000000000000000000",
			"0b1100000000000000000000000000000000000000000000000000000000000000",
		)
	);
}
