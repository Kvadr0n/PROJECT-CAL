#ifndef calcguard
#define calcguard
#include "gen.h"

namespace calc
{
	extern bool negAllow;

	extern double ln2;
	extern double e;
	extern double pi;
	extern uint64_t a;
	extern uint64_t b;
	extern uint64_t c;

	double ln(double x);
	void ln_22();
	double log(double a, double x);
	double exp(double x);
	void exp1();
	double pow(double x, double a);
	double root(double a, double x);
	double sqrt(double x);
	double arctg(double x);
	void arctg1();
	double arcctg(double x);
	double arcsin(double x);
	double arccos(double x);
	double sin(double x);
	double cos(double x);
	double tg(double x);
	double ctg(double x);

	void test();
}

#endif