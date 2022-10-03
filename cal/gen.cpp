#include "gen.h"

short gen::exput(double& x, short a)
{
	if ((a < -1024) || (a > 1024))
		throw(OutOfDomain());
	short old = order(x);

	a = ((x < 0) << 15) | ((a + 1023) << 4) | (((short*)(&x))[3] & 0xf);
	((short*)(&x))[3] = a;
	return(order(x) - old);
}

double gen::x2(double x, short a)
{
	unsigned long long& num = (unsigned long long&)x;
	if ((num == 0) ||
		(num == 0b0111111111110000000000000000000000000000000000000000000000000000) ||
		(num == 0b1111111111110000000000000000000000000000000000000000000000000000) ||
		(num == 0b1111111111111000000000000000000000000000000000000000000000000000) ||
		(a == 0))
		return(x);
	short old = order(x);
	unsigned long long sign = (x < 0) ? 0x8000000000000000 : 0;
	num &= 0x7fffffffffffffff;
	if (a < 0)
	{
		a = -a;
		if (old + 1023 <= a)
		{
			a -= old + 1023;
			num = sign | ((((num & 0b0000000000001111111111111111111111111111111111111111111111111111) >> 1) | 0b0000000000001000000000000000000000000000000000000000000000000000) >> a);
			return(x);
		}
		num = sign | num;
		exput(x, old - a);
		return(x);
	}
	if (old == -1023)
	{
		while ((num < 0b0000000000010000000000000000000000000000000000000000000000000000) && (a))
		{
			num <<= 1;
			--a;
		}
		num |= sign;
		if (!a)
			return(x);
		++old;
	}
	if (old + a >= 1024)
	{
		num = sign | 0b0111111111110000000000000000000000000000000000000000000000000000;
		return(x);
	}
	num = sign | num;
	exput(x, old + a);
	return(x);
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
	return(((((short*)(&x))[3] >> 4) & 0b0000011111111111) - 1023);
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
	test2to1(exput, ARR(2, 32, -1.5, 0), ARR(5, 1, 1, 1024), ARR(4, -4, 1, 2047));
	{
		unsigned long long a0 = 0b0000000001001000000000000000000000000000000000000000000000000000;
		unsigned long long a1 = 0b0111111111100000000000000000000000000000000000000000000000000000;
		unsigned long long a2 = 0b0000000000000000000000000000000000000000000000000000000000000011;
		unsigned long long a3 = 0b0111111111110000000000000000000000000000000000000000000000000000;
		unsigned long long a4 = 0b1111111111110000000000000000000000000000000000000000000000000000;
		unsigned long long a5 = 0b1111111111111000000000000000000000000000000000000000000000000000;
		double& b0 = (double&)a0;
		double& b1 = (double&)a1;
		double& b2 = (double&)a2;
		double& b3 = (double&)a3;
		double& b4 = (double&)a4;
		double& b5 = (double&)a5;
		test2to1(x2, ARR(2, 32, -2, -32, 0, -1.5, b1, b2, b3, b4, b5), ARR(4, -4, 4, -4, 1024, 1, 2, 54, -1, -1, -1), ARR(32, 2, -32, -2, 0, -3, b3, b0, b3, b4, b5));
		//провал теста 11 - нормально, так как NaN != NaN по определению
	}
}
