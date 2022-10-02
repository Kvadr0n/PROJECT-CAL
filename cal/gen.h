#ifndef genguard
#define genguard
#include "testmacros.h"

struct OutOfDomain : public std::exception
{
	const char* what()
	{
		return("OutOfDomain");
	}
};

namespace gen
{
	void test();

	short exput(double& x, short a);
	double x2(double x, short a);
	double sgn(double x);
	double abs(double x);
	double floor(double x);
	double mant(double x);
	double ceil(double x);
	double round(double x);
	short order(double x);
	double ipow(double x, short a);
	std::string bin(double x);
}

#endif