#include "siaod.h"

exptree siaod::f;

template<class T>
stack<T>::~stack()
{
	snode<T>* old;
	while (head)
	{
		old = head;
		head = head->prev;
		delete old;
	}
}

template<class T>
stack<T>& operator<<(stack<T>& S, T data)
{
	S.head = new snode<T>({ data, S.head });
	return(S);
}

template<class T>
stack<T>& operator>>(stack<T>& S, T& data)
{
	data = S.head->value;
	snode<T>* old = S.head;
	S.head = S.head->prev;
	delete old;
	return(S);
}

tnode::tnode(double value_, tnode* next0, tnode* next1)
{
	value = value_;
	next[0] = next0;
	next[1] = next1;
}

tnode::tnode(unsigned long long bin)
{
	next[0] = nullptr;
	next[1] = nullptr;
	double& a = (double&)bin;
	value = a;
}

exptree::exptree() {};

exptree::exptree(std::string func)
{
	stack<unsigned char> orders;
	stack<tnode*> nodes;
	unsigned char start = 0;
	unsigned char len;
	char cur;
	char* word;
	unsigned long long hash;
	char k = 0;
	double num = 0;
	double digval = 1;
	unsigned char dot;
	for (unsigned char i = 0; ; ++i)
	{
		cur = func[i];
		if (
			(cur == ' ') || (cur == 0) || (cur == '+') ||
			(cur == '-') || (cur == '*') || (cur == '/') ||
			(cur == '^') || (cur == '(') || (cur == ')') ||
			(cur == '|') || (cur == ',')
			)
		{
			len = i - start;
			if (len < 8)
			{
				word = new char[8];
				for (unsigned char j = 0; j < len; ++j)
					word[j] = func[j + start];
				for (unsigned char j = len; j < 8; ++j)
					word[j] = 0;
			}
			else
			{
				word = new char[len + 1];
				for (unsigned char j = 0; j < len; ++j)
					word[j] = func[j + start];
				word[len] = 0;
			}
			start = i + 1;
			hash = word[0] | (word[1] << 8) | (word[2] << 16) | (word[3] << 24) |
				((unsigned long long)word[4] << 32) | ((unsigned long long)word[5] << 40) |
				((unsigned long long)word[6] << 48) | ((unsigned long long)word[7] << 56);
			switch (hash)
			{
			case 0: // пустота
			{
				delete[] word;
				break;
			}
			case 101: // e
			{
				delete[] word;
				nodes << new tnode(0xfff0000000000001);
				break;
			}
			case 26992: // pi
			{
				delete[] word;
				nodes << new tnode(0xfff0000000000002);
				break;
			}
			case 120: // x
			{
				delete[] word;
				nodes << new tnode(0xfff0000000000003);
				break;
			}
			case 1953460082: // root
			{
				delete[] word;
				nodes << new tnode(0xfff0000000000004);
				break;
			}
			case 6778732: // log
			{
				delete[] word;
				nodes << new tnode(0xfff0000000000005);
				break;
			}
			case 28268: // ln
			{
				delete[] word;
				nodes << new tnode(0xfff0000000000006);
				break;
			}
			case 7235955: // sin
			{
				delete[] word;
				nodes << new tnode(0xfff0000000000007);
				break;
			}
			case 7565155: // cos
			{
				delete[] word;
				nodes << new tnode(0xfff0000000000008);
				break;
			}
			case 26484: // tg
			{
				delete[] word;
				nodes << new tnode(0xfff0000000000009);
				break;
			}
			case 6780003: // ctg
			{
				delete[] word;
				nodes << new tnode(0xfff000000000000a);
				break;
			}
			case 121399186518625: // arcsin
			{
				delete[] word;
				nodes << new tnode(0xfff000000000000b);
				break;
			}
			case 126922246025825: // arccos
			{
				delete[] word;
				nodes << new tnode(0xfff000000000000c);
				break;
			}
			case 444334305889: // arctg
			{
				delete[] word;
				nodes << new tnode(0xfff000000000000d);
				break;
			}
			case 113749581328993: // arcctg
			{
				delete[] word;
				nodes << new tnode(0xfff000000000000e);
				break;
			}
			default: // число?
			{
				for (k = 0; (k < len) && (word[k] != '.'); ++k);
				if (k == len)
				{
					--k;
					for (k; k >= 0; --k)
					{
						num += digval * (word[k] - 48);
						digval *= 10;
					}
				}
				else
				{
					dot = k;
					--k;
					for (k; k >= 0; --k)
					{
						num += digval * (word[k] - 48);
						digval *= 10;
					};
					digval = 1.0 / 10.0;
					k = dot + 1;
					for (k; word[k] != 0; ++k)
					{
						num += digval * (word[k] - 48);
						digval /= 10;
					}
				}
				std::cout << num << '\n';
				num = 0;
				digval = 1;
				delete[] word;
				nodes << new tnode(num, nullptr, nullptr);
				break;
			}
			}
			switch (cur)
			{
			case ' ':
			{
				break;
			}
			case '+':
			{
				if (orders.head)
					if (orders.head->value >= 1)
					{
						unsigned char garbage;
						orders >> garbage;
						tnode* trio[3];
						nodes >> trio[2] >> trio[1] >> trio[0];
						trio[1]->next[0] = trio[0];
						trio[1]->next[1] = trio[2];
						nodes << trio[1];
					}
				nodes << new tnode(0xfff0000000000010);
				orders << (unsigned char)1;
				break;
			}
			case '*':
			{
				if (orders.head)
					if (orders.head->value >= 2)
					{
						unsigned char garbage;
						orders >> garbage;
						tnode* trio[3];
						nodes >> trio[2] >> trio[1] >> trio[0];
						trio[1]->next[0] = trio[0];
						trio[1]->next[1] = trio[2];
						nodes << trio[1];
					}
				nodes << new tnode(0xfff0000000000011);
				orders << (unsigned char)2;
				break;
			}
			case '/':
			{
				if (orders.head)
					if (orders.head->value >= 2)
					{
						unsigned char garbage;
						orders >> garbage;
						tnode* trio[3];
						nodes >> trio[2] >> trio[1] >> trio[0];
						trio[1]->next[0] = trio[0];
						trio[1]->next[1] = trio[2];
						nodes << trio[1];
					}
				nodes << new tnode(0xfff0000000000012);
				orders << (unsigned char)2;
				break;
			}
			case '^':
			{
				if (orders.head)
					if (orders.head->value >= 4)
					{
						unsigned char garbage;
						orders >> garbage;
						tnode* trio[3];
						nodes >> trio[2] >> trio[1] >> trio[0];
						trio[1]->next[0] = trio[0];
						trio[1]->next[1] = trio[2];
						nodes << trio[1];
					}
				nodes << new tnode(0xfff0000000000013);
				orders << (unsigned char)4;
				break;
			}
			case '-':
			{
				if (orders.head)
					if (orders.head->value >= 1)
					{
						unsigned char garbage;
						orders >> garbage;
						tnode* trio[3];
						nodes >> trio[2] >> trio[1] >> trio[0];
						trio[1]->next[0] = trio[0];
						trio[1]->next[1] = trio[2];
						nodes << trio[1];
					}
				if (!nodes.head)
				{
					nodes << new tnode(0);
					nodes << new tnode(0xfff0000000000014);
				}
				else
					if ((unsigned long long&)nodes.head->value->value == 0xfff0000000000015)
					{
						nodes << new tnode(0);
						nodes << new tnode(0xfff0000000000014);
					}
					else
						nodes << new tnode(0xfff0000000000014);
				orders << (unsigned char)1;
				break;
			}
			case '(':
			{
				nodes << new tnode(0xfff0000000000015);
				orders << (unsigned char)10;
				break;
			}
			case ')':
			{
				unsigned char garbage;
				tnode* trio[3];
				while (orders.head->value != 10)
				{
					orders >> garbage;
					nodes >> trio[2] >> trio[1] >> trio[0];
					trio[1]->next[0] = trio[0];
					trio[1]->next[1] = trio[2];
					nodes << trio[1];
				}
				orders >> garbage;
				tnode* res;
				tnode* garbaj;
				nodes >> res >> garbaj;
				if (nodes.head)
					if (((unsigned long long&)nodes.head->value->value >= 0xfff0000000000006) ||
						((unsigned long long&)nodes.head->value->value <= 0xfff000000000000e))
						nodes.head->value->next[0] = res;
					else
						nodes << res;
				break;
			}
			case '[':
			{
				nodes << new tnode(0xfff0000000000018);
				nodes << new tnode(0xfff0000000000019);
				orders << (unsigned char)10;
				break;
			}
			case ']':
			{
				unsigned char garbage;
				tnode* trio[3];
				while (orders.head->value != 10)
				{
					orders >> garbage;
					nodes >> trio[2] >> trio[1] >> trio[0];
					trio[1]->next[0] = trio[0];
					trio[1]->next[1] = trio[2];
					nodes << trio[1];
				}
				orders >> garbage;
				tnode* res;
				tnode* garbaj;
				nodes >> res >> garbaj;
				if (nodes.head)
					if (((unsigned long long&)nodes.head->value->value >= 0xfff0000000000006) ||
						((unsigned long long&)nodes.head->value->value <= 0xfff000000000000e))
						nodes.head->value->next[0] = res;
					else
						nodes << res;
				break;
			}
			}
		}
		if (!cur)
		{
			break;
		}
	}
}

double exptree::operator[](double x)
{
	return 0.0;
}

bool siaod::verify(std::string func)
{
	unsigned char start = 0;
	unsigned char len;
	char cur;
	char* word;
	unsigned long long hash;
	char circle = 0;
	char square = 0;
	char localCircle = 0;
	bool nonEmpty = false;
	bool prevOperator = false;
	bool prevOperand = false;
	bool prevBracket = true;
	bool nonEmptyOperand = false;
	bool wasDot = false;
	for (unsigned char i = 0; ; ++i)
	{
		cur = func[i];
		if (
			(cur == ' ') || (cur ==  0 ) || (cur == '+') ||
			(cur == '-') || (cur == '*') || (cur == '/') ||
			(cur == '^') || (cur == '(') || (cur == ')') ||
			(cur == '|') || (cur == ',')
		   )
		{
			len = i - start;
			if (len < 8)
			{
				word = new char[8];
				for (unsigned char j = 0; j < len; ++j)
					word[j] = func[j + start];
				for (unsigned char j = len; j < 8; ++j)
					word[j] = 0;
			}
			else
			{
				word = new char[len];
				for (unsigned char j = 0; j < len; ++j)
					word[j] = func[j + start];
			}
			start = i + 1;
			hash = word[0] | (word[1] << 8) | (word[2] << 16) | (word[3] << 24) | 
				((unsigned long long)word[4] << 32) | ((unsigned long long)word[5] << 40) | 
				((unsigned long long)word[6] << 48) | ((unsigned long long)word[7] << 56);
			switch (hash)
			{
				case 0: // пустота
				{
					delete[] word;
					break;
				}
				case 101: // e
				case 26992: // pi
				case 120: // x
				{
					delete[] word;
					nonEmpty = true;
					if (prevOperand)
						return(false);
					prevOperator = false;
					prevOperand = true;
					if (prevBracket)
						nonEmptyOperand = true;
					prevBracket = false;
					break;
				}
				case 1953460082: // root
				case 6778732: // log
				{
					delete[] word;
					nonEmpty = true;
					if (prevOperand || (cur != '('))
						return(false);
					prevOperator = false;
					prevOperand = true;
					prevBracket = false;
					start = i + 1;
					for (i; (func[i] != ',') && (func[i] != 0); ++i);
					if (func[i] == 0)
						return(false);
					if (siaod::verify(func.substr(start, i - start)))
					{
						start = i + 1;
						++i;
						for (i; (localCircle != -1) && (func[i] != 0); ++i)
						{
							if (func[i] == '(')
								++localCircle;
							if (func[i] == ')')
								--localCircle;
						}
						localCircle = 0;
						cur = func[i];
						if (!siaod::verify(func.substr(start, i - start - 1)))
							return(false);
					}
					else
						return(false);
					start = i + 1;
					break;
				}
				case 28268: // ln
				case 7235955: // sin
				case 7565155: // cos
				case 26484: // tg
				case 6780003: // ctg
				case 121399186518625: // arcsin
				case 126922246025825: // arccos
				case 444334305889: // arctg
				case 113749581328993: // arcctg
				{
					delete[] word;
					nonEmpty = true;
					nonEmptyOperand = true;
					if (prevOperand || (cur != '('))
						return(false);
					prevOperator = false;
					prevOperand = true;
					prevBracket = false;
					start = i + 1;
					++i;
					for (i; (localCircle != -1) && (func[i] != 0); ++i)
					{
						if (func[i] == '(')
							++localCircle;
						if (func[i] == ')')
							--localCircle;
					}
					localCircle = 0;
					cur = func[i];
					if (!siaod::verify(func.substr(start, i - start - 1)))
						return(false);
					start = i + 1;
					break;
				}
				default: // число?
				{
					nonEmpty = true;
					if ((prevOperand) || (word[0] == '.') || (word[len - 1] == '.'))
					{
						delete[] word;
						return(false);
					}
					for (unsigned char k = 0; k < len; ++k)
					{
						if (((word[k] < '0') && (word[k] != '.')) || (word[k] > '9'))
						{
							delete[] word;
							return(false);
						}
						if (word[k] == '.')
							if (wasDot)
							{
								delete[] word;
								return(false);
							}
							else
								wasDot = true;
					}
					delete[] word;
					prevOperator = false;
					prevOperand = true;
					if (prevBracket)
						nonEmptyOperand = true;
					prevBracket = false;
					wasDot = false;
					break;
				}
			}
			switch (cur)
			{
				case ' ':
				{
					break;
				}
				case '+':
				case '*':
				case '/':
				case '^':
				{
					if (!prevOperand)
						return(false);
					prevOperator = true;
					prevOperand = false;
					prevBracket = false;
					break;
				}
				case '-':
				{
					if (prevOperator)
						return(false);
					prevOperator = true;
					prevOperand = false;
					prevBracket = false;
					break;
				}
				case '(':
				{
					if (prevOperand)
						return(false);
					prevOperator = false;
					prevOperand = false;
					prevBracket = true;
					++circle;
					break;
				}
				case ')':
				{
					if ((prevOperator) || (!nonEmptyOperand))
						return(false);
					prevOperator = false;
					prevOperand = true;
					prevBracket = false;
					nonEmptyOperand = true;
					--circle;
					break;
				}
				case '[':
				{
					if (prevOperand)
						return(false);
					prevOperator = false;
					prevOperand = false;
					prevBracket = true;
					++square;
					break;
				}
				case ']':
				{
					if ((prevOperator) || (!nonEmptyOperand))
						return(false);
					prevOperator = false;
					prevOperand = true;
					prevBracket = false;
					nonEmptyOperand = true;
					--square;
					break;
				}
			}
		}
		if (!cur)
		{
			break;
		}
	}
	if ((square) || (circle) || !nonEmpty)
		return(false);
	return(true);
}

void siaod::test()
{
	using namespace siaod;
	//АНДРЕЙ - Тесты стека в белую
	//Ожидаемый результат: 6543
	//Результат достигнут
	{
		stack<int> A;
		A << 1 << 2 << 3 << 4 << 5 << 6;
		int B[4]; //лишние числа в стеке для проверки утечек профилированием кучи
		A >> B[0] >> B[1] >> B[2] >> B[3];
		std::cout << B[0] << B[1] << B[2] << B[3] << '\n';
	}
	//АНДРЕЙ - Тест верификации выражения-строки
	test1strto1
			(verify, 
				ARR
				(
					"", "   ",
					"x + e + pi",
					"123", "-123", "123.5", "12a3", "12.3.4", ".123", "123.",
					"sin(x)", "sin(1)", "sin(x + 1)", "sin((x))", "sin()", "sin(x", "sinx",
					"log(2, 3)", "log(2,3.2)", "log( 2, log(2, 3))", "log((2),(5))", "log2,3", "log(2 5)", "log(2)",
					"log(2, 4) + sin(x)", "log(2,4)+sin(x)", "-log(2,4)^sin(x)", "(-log(2,4)^sin(x))", "(sin(x)^(-log(2,4)))", "(sin(x)^(-log(2,4)))"
				), 
				ARR
				(
					false, false,
					true,
					true, true, true, false, false, false, false,
					true, true, true, true, false, false, false,
					true, true, true, true, false, false, false,
					true, true, true, true, true, true
				)
			);
	//f = std::string("12 + (12.53 + 3)");
}