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

std::string gen::bin(double x)
{
	char res[67];
	res[0] = '0';
	res[1] = 'b';
	res[66] = 0;
	unsigned long long& num = (unsigned long long&)x;
	for (char i = 2; i < 66; ++i)
	{
		res[i] = char(num >= 0x8000000000000000) + 48;
		num <<= 1;
	}
	return(res);
}

void gen::test()
{
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
