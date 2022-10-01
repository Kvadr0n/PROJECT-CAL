#ifndef numguard
#define numguard
#include "siaod.h"

struct SolutionFail : public std::exception
{
	const char* what()
	{
		return("SolutionFail");
	}
};

namespace num
{
	double derive(double x);
	double derive(double x, unsigned char n);
	double solve(double a, double b);
	double integrate(double a, double b);

	void test();
}

#endif