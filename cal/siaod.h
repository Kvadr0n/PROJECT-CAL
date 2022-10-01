#ifndef siaodguard
#define siaodguard
#include "calc.h"

struct tnode
{
	double value;
	tnode* next[2];
};

struct exptree
{
	double operator[](double x);
};

namespace siaod
{
	extern exptree f;

	bool verify(std::string func);

	void test();
}

#endif