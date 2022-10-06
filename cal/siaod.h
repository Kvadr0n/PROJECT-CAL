#ifndef siaodguard
#define siaodguard
#include "calc.h"

template <class T>
struct snode
{
	T value;
	snode* prev;
};

template <class T>
struct stack
{
	~stack<T>();

	snode<T>* head = nullptr;
};

template <class T>
stack<T>& operator<<(stack<T>& S, T data);
template <class T>
stack<T>& operator>>(stack<T>& S, T& data);

struct tnode
{
	tnode(double value_, tnode* next0, tnode* next1);
	tnode(unsigned long long bin);

	double value;
	tnode* next[2];
};

struct exptree
{
	exptree();
	exptree(std::string func);
	double operator[](double x);

	tnode* head;
};

namespace siaod
{
	extern exptree f;

	bool verify(std::string func);
	double parseNum(std::string num);

	void test();
}

#endif