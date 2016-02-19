// 注意Cls1和Cls2的依赖关系

class Cls2;

class Cls1
{
public:
	int func1( Cls2 &c2 );		//func1使用了Cls2, 所以Cls2必须先不完全定义
};

class Cls2
{
friend int Cls1::func1( Cls2 &c2 );		// 声明Cls1的成员函数为友元. Cls1::func1必须先声明
public:
	Cls2(int pi): i(pi) {}
private:
	int i;
};

int Cls1::func1( Cls2 &c2 )		// func1只能在Cls2定义后定义, 因为要访问Cls2的成员
{
	return c2.i;
}

#include <iostream>
using std::cout;

class Cls3
{
	friend class Cls4;
	friend void friendFunc();
public:
	Cls3( int pi ): i(pi) {}
private:
	int i;
};
void friendFunc()
{
	Cls3 c3(-2);
	std::cout << "friendFunc:" << c3.i;
}


int main()
{
	Cls1 c1;
	Cls2 c2(-1);
	std::cout << c1.func1( c2 );
	friendFunc();
	return 0;
}