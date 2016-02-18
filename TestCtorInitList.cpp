// 测试构造函数初始化列表

// 一个没有默认构造函数的类
class Cls1
{
public:
	Cls1( int arg ): _arg(arg) {}
private:
	int _arg;
};

// 构造函数分2阶段执行:
// 1, 初始化阶段, 此阶段调用构造函数初始化列表. 如果没有显示提供初始化列表, 
// 则进行隐式初始化. 对于类类型, 调用其默认构造函数初始化. 对于内置类型, 不进行隐式初始化
// 2, 计算阶段, 由构造函数体中的所有语句组成
// 由上可知, 没有默认构造函数的类类型对象. const成员或引用成员需要在构造函数初始化列表中显示初始化
class Cls2
{
public:
	// Cls2(){}										// error. ri未初始化, ci未初始化, 初始化阶段构造c1时未提供初始化式
	Cls2( int i ): ri(i), ci(i), c1(i) {}			// ok
	// Cls2( int i ) { ri = i; ci = i; c1(i); }		// ri未绑定到对象, 不能赋值. ci是常量, 不能赋值
private:
	int &ri;
	const int ci;
	Cls1 c1;
};

// 定义成员的次序就是初始化成员的次序
class Cls3
{
public:
	Cls3( int i ): b(i), a(b) {}	// 初始化列表中的次序并非成员初始化次序. 这里先用未初始化的b初始化a, 再初始化b
public:
	int a;
	int b;
};

#include <iostream>
int main()
{
	Cls2 c2(1);
	Cls3 c3(1);
	std::cout<<c3.a<<c3.b;
	return 0;
}