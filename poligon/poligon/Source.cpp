#include <iostream>

class A
{
public:
	virtual void printName()
	{
		std::cout << "a";
	}
};

class B :public A
{
public:
	virtual void printName()
	{
		std::cout << "b";
	}
};

void main()
{
	A a = A();
	B b = B();
	A c = B();
	A *d = new B();
	a.printName();
	b.printName();
	c.printName();
	d->printName();
	system("pause");
}