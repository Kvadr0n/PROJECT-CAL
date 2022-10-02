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

short gen::order(double x)
{
	return 0;
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
	using namespace gen;
	//АНДРЕЙ - ТЕСТ БИНАРНЫХ СТРОК
	/*
	test1to1str
	(bin, ARR(0, 1, 1.25, -2), ARR
		(
			"0b0000000000000000000000000000000000000000000000000000000000000000",
			"0b0011111111110000000000000000000000000000000000000000000000000000",
			"0b0011111111110100000000000000000000000000000000000000000000000000",
			"0b1100000000000000000000000000000000000000000000000000000000000000",
		)
	);
	*/
	//АНДРЕЙ - ТЕСТЫ БИНАРНЫХ ОПЕРАЦИЙ НАД ДАБЛАМИ
	test1to1(order, ARR(1, 1.5, 2, 0), ARR(0, 0, 1, -1023));
	test2to1(exput, ARR(2, 32, 0), ARR(5, 1, 1024), ARR(4, -4, 2047));
	{
		unsigned long long a1 = 0b0111111111110000000000000000000000000000000000000000000000000000;
		unsigned long long a2 = 0b0000000000000000000000000000000000000000000000000000000000000001;
		unsigned long long a3 = 0b0111111111110000000000000000000000000000000000000000000000000000;
		unsigned long long a4 = 0b1111111111110000000000000000000000000000000000000000000000000000;
		unsigned long long a5 = 0b1111111111111000000000000000000000000000000000000000000000000000;
		double& b1 = (double&)a1;
		double& b2 = (double&)a2;
		double& b3 = (double&)a3;
		double& b4 = (double&)a4;
		double& b5 = (double&)a5;
		test2to1(x2, ARR(2, 32, 0, b1, b2, b3, b4, b5), ARR(4, -4, 1024, 2, 54, -1, -1, -1), ARR(32, 2, 0, 4, b2, b3, b4, b5));
	}
}
