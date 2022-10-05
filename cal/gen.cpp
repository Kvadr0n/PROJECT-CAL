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

double gen::sgn(double x){
	if (x > 0) return 1;
	if (x == 0) return 0;
	return -1;
}

double gen::abs(double x){
	return x * sgn(x);
}

double gen::floor(double x){
	int temp = order(x);
	if (temp > 51) return x;
	if (temp < 0) return x < 0 ? -1 : 0;
	uint64_t o = *(uint64_t*)(&x);
	uint64_t mask = temp > 0 ? 0b0000000000001000000000000000000000000000000000000000000000000000 : 0b0000000000000000000000000000000000000000000000000000000000000000;
	for (int i = 0; i < temp - 1; ++i) {
		mask |= mask >> 1;
	}
	uint64_t t = (o & mask);
	mask = 0b1111111111110000000000000000000000000000000000000000000000000000 & o;
	uint64_t now = (t | mask);
	if (x <= 0) return  *(double*)&now - 1;
	return *(double*)&now;
}

double gen::mant(double x){
	int now = x - floor(x);
	if(x >= 0) return x - floor(x);
	return x - floor(x) - 1;
}

double gen::ceil(double x){
	if (floor(x) == x) return x;
	return floor(x) + 1;
}

double gen::round(double x){
	return floor(x + 0.5);
}

short gen::order(double x)
{
	return(((((unsigned short*)(&x))[3] >> 4) & 0b0000011111111111) - 1023);
}

double gen::ipow(double x, short a)
{
	uint64_t res = 1;
	while (a)
		if (a & 1) {
			res *= x;
			--a;
		}
		else {
			x *= x;
			a >>= 1;
		}
	return res;
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
	{
			//РОМАН тесты:
		//sgn
		test1to1(sgn, ARR(0, 1, -1, -550.12, 12345.6), ARR(0, 1, -1, -1, 1));
		//abs
		test1to1(abs, ARR(0, 1, -1, -550.12, 12345.6), ARR(0, 1, 1, 550.12, 12345.6));
		//floor
		test1to1(floor, ARR(0, 1, -31.1111, 800000.22948, 0.12345, -0.123, 1.5), ARR(0, 1, -32, 800000, 0, -1, 1));
		//mant
		union { unsigned long long a0 = 0xC037C00000000000; double d0; };//-23.75
		union { unsigned long long a1 = 0x41286A02C0000000; double d1; };//800001.375
		union { unsigned long long a2 = 0xBFE8000000000000; double d2; };//-0.75
		union { unsigned long long a3 = 0x3FD8000000000000; double d3; };//0.375
		
		test1to1(mant, ARR(0, 1, d0, d1, 0.12345), ARR(0, 0, d2, d3, 0.12345));
		//ceil
		test1to1(ceil, ARR(0, 1, -31.1111, 800000.22948, 0.12345), ARR(0, 1, -31, 800001, 1));
		//round
		test1to1(round, ARR(0, 1, -31.1111, 800000.5, 0.8881111), ARR(0, 1, -31, 800001, 1));
		//ipow
		test2to1(ipow, ARR(0, 1, 10, 7, 5), ARR(50, 50, 7, 10, -6), ARR(0, 1, 10000000, 282475249, 0.000064));
	}
}