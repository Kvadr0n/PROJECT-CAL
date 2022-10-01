#include "num.h"

/*
double sqr(double a)
{
	return(a * a);
}

double sum(double a, double b)
{
	return(a + b);
}

std::string func(double a)
{
	if (a == 1)
		return("sus");
	if (a == 2.5)
		return("amogus");
	return("no");
}

bool veri(std::string a)
{
	if (a == "sus")
		return(true);
	else
		return(false);
}
*/

void parsetest()
{
	//Саму функцию parse тестировать в серую здесь
	
	/* Примеры некоторых других тестов (раскомментить это и функции выше)
	test1to1(sqr, ARR(1, 2, 3), ARR(1, 6, 9));
	test2to1(sum, ARR(2, 4, 6), ARR(5, 9, 3), ARR(7, 10, 9));
	test2to1err(sum, ARR(2, 4, 6), ARR(5, 9, 3), ARR(7, 10, 9), 2.9);
	test1to1str(func, ARR(1, 2.5, 2), ARR("sus", "amogus", "nein"));
	test1strto1(veri, ARR("sus", "sos", "sis"), ARR(true, false, true));
	*/
}

void parse(std::string com)
{

}


int main()
{
	gen::test();
	calc::test();
	siaod::test();
	num::test();
	parsetest();
	parsetest();
	system("pause");
	return(0);
}
//