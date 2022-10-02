#ifndef testmacrosguard
#define testmacrosguard
#include <iostream>
#include <exception>

//Оборачивает массив для подачи в тестирующий макрос. Например:
//AR(1.0, 2.5, 3.25) = {1.0, 2.5, 3.25}
//AR("amogus2", "baza") = {"amogus2", "baza"}
#define ARR(...) {__VA_ARGS__}

//Тестирует функции double->double
#define test1to1(function, input1, expected) \
{ \
	double in1[] = input1; \
	double ex[] = expected; \
	int size = sizeof(in1)/sizeof(double); \
	double value; \
	std::cout << #function << " test:\n"; \
	for (int i = 0; i < size; ++i) \
	{ \
		value = function(in1[i]); \
		if (value == ex[i]) \
			std::cout << "    Test " << i + 1 << " passed.\n"; \
		else \
			std::cout << "    Test " << i + 1 << " FAILED.\n        EXPECTED: " << ex[i] << "\n        ACTUAL:   " << value << "\n"; \
	} \
	std::cout << '\n'; \
}
//Тестирует функции double+double->double
#define test2to1(function, input1, input2, expected) \
{ \
	double in1[] = input1; \
	double in2[] = input2; \
	double ex[] = expected; \
	int size = sizeof(in1)/sizeof(double); \
	double value; \
	std::cout << #function << " test:\n"; \
	for (int i = 0; i < size; ++i) \
	{ \
		value = function(in1[i], in2[i]); \
		if (value == ex[i]) \
			std::cout << "    Test " << i + 1 << " passed.\n"; \
		else \
			std::cout << "    Test " << i + 1 << " FAILED.\n        EXPECTED: " << ex[i] << "\n        ACTUAL:   " << value << "\n"; \
	} \
	std::cout << '\n'; \
}
//Тестирует функции double->string
#define test1to1str(function, input1, expected) \
{ \
	double in1[] = input1; \
	std::string ex[] = expected; \
	int size = sizeof(in1)/sizeof(double); \
	std::string value; \
	std::cout << #function << " test:\n"; \
	for (int i = 0; i < size; ++i) \
	{ \
		value = function(in1[i]); \
		if (value == ex[i]) \
			std::cout << "    Test " << i + 1 << " passed.\n"; \
		else \
			std::cout << "    Test " << i + 1 << " FAILED.\n        EXPECTED: " << ex[i] << "\n        ACTUAL:   " << value << "\n"; \
	} \
	std::cout << '\n'; \
}
//Тестирует функции double->double с указанной погрешностью
#define test1to1err(function, input1, expected, error) \
{ \
	double in1[] = input1; \
	double ex[] = expected; \
	int size = sizeof(in1)/sizeof(double); \
	double value; \
	std::cout << #function << " test:\n"; \
	for (int i = 0; i < size; ++i) \
	{ \
		value = function(in1[i]); \
		if ((ex[i] - error <= value) && (value <= ex[i] + error)) \
			std::cout << "    Test " << i + 1 << " passed.\n"; \
		else \
			std::cout << "    Test " << i + 1 << " FAILED.\n        EXPECTED: " << ex[i] << "\n        ACTUAL:   " << value << "\n"; \
	} \
	std::cout << '\n'; \
}
//Тестирует функции double+double->double с указанной погрешностью
#define test2to1err(function, input1, input2, expected, error) \
{ \
	double in1[] = input1; \
	double in2[] = input2; \
	double ex[] = expected; \
	int size = sizeof(in1)/sizeof(double); \
	double value; \
	std::cout << #function << " test:\n"; \
	for (int i = 0; i < size; ++i) \
	{ \
		value = function(in1[i], in2[i]); \
		if ((ex[i] - error <= value) && (value <= ex[i] + error)) \
			std::cout << "    Test " << i + 1 << " passed.\n"; \
		else \
			std::cout << "    Test " << i + 1 << " FAILED.\n        EXPECTED: " << ex[i] << "\n        ACTUAL:   " << value << "\n"; \
	} \
	std::cout << '\n'; \
}
//Тестирует функции string->double
#define test1strto1(function, input1, expected) \
{ \
	std::string in1[] = input1; \
	double ex[] = expected; \
	int size = sizeof(in1)/sizeof(std::string); \
	double value; \
	std::cout << #function << " test:\n"; \
	for (int i = 0; i < size; ++i) \
	{ \
		value = function(in1[i]); \
		if (value == ex[i]) \
			std::cout << "    Test " << i + 1 << " passed.\n"; \
		else \
			std::cout << "    Test " << i + 1 << " FAILED.\n        EXPECTED: " << ex[i] << "\n        ACTUAL:   " << value << "\n"; \
	} \
	std::cout << '\n'; \
}
//Тестирует функции double->double с указанной погрешностью, требующие задания функции в виде уравнения
#define test1to1errfunc(function, funcs, input1, expected, error) \
{ \
	std::string fs[] = funcs; \
	double in1[] = input1; \
	double ex[] = expected; \
	int size = sizeof(in1)/sizeof(double); \
	double value; \
	std::cout << #function << " test:\n"; \
	for (int i = 0; i < size; ++i) \
	{ \
		siaod::f = fs[i]; \
		value = function(in1[i]); \
		if ((ex[i] - error <= value) && (value <= ex[i] + error)) \
			std::cout << "    Test " << i + 1 << " passed.\n"; \
		else \
			std::cout << "    Test " << i + 1 << " FAILED.\n        EXPECTED: " << ex[i] << "\n        ACTUAL:   " << value << "\n"; \
	} \
	std::cout << '\n'; \
}
//Тестирует функции double+double->double с указанной погрешностью, требующие задания функции в виде уравнения
#define test2to1errfunc(function, funcs, input1, input2, expected, error) \
{ \
	std::string fs[] = funcs; \
	double in1[] = input1; \
	double in2[] = input2; \
	double ex[] = expected; \
	int size = sizeof(in1)/sizeof(double); \
	double value; \
	std::cout << #function << " test:\n"; \
	for (int i = 0; i < size; ++i) \
	{ \
		siaod::f = fs[i]; \
		value = function(in1[i], in2[i]); \
		if ((ex[i] - error <= value) && (value <= ex[i] + error)) \
			std::cout << "    Test " << i + 1 << " passed.\n"; \
		else \
			std::cout << "    Test " << i + 1 << " FAILED.\n        EXPECTED: " << ex[i] << "\n        ACTUAL:   " << value << "\n"; \
	} \
	std::cout << '\n'; \
}
//test
#endif
