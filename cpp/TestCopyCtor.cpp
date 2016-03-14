#include <string>
#include <iostream>
using namespace std;

// 自定义复制构造函数
// 如果类没有指针成员, 或复制构造/赋值时不需要做特殊的工作, 则合成的复制构造/赋值操作一样可以工作得很好
class Foo
{
public:
	Foo(): ival(0), sval( "empty" ) { cout << "Foo()" << endl; }
	Foo( int i ): ival(i), sval( "empty" ) { cout << "Foo( int i )" << endl; }
	Foo( const Foo& );
	Foo& operator=( const Foo& );
private:
	int ival;
	string sval;
};

// 自定义的复制构造函数做的工作与合成的复制构造函数做的工作一模一样
Foo::Foo( const Foo& rhs ): ival( rhs.ival ), sval( rhs.sval )
{
	cout << "Foo( const Foo& rhs )" << endl;
}

// 自定义的赋值操作符做的工作与合成的赋值操作符做的工作一模一样
Foo& Foo::operator=( const Foo& rhs )
{
	ival = rhs.ival;
	sval = rhs.sval;
	cout << "Foo& operator=( const Foo& rhs )" << endl;
	return *this;
}

int main()
{
	Foo f;				// 调用默认构造函数

	Foo f2(f);			// 调用复制构造函数
	Foo f5 = Foo(1);	// 先创建临时对象, 再复制初始化
	Foo f6 = 1;			// 先调用单形参构造函数创建临时对象, 接着调用复制初始化

	//Foo f7 = f;			// 这种写法表示初始化, 复制初始化. 所以调用复制构造函数
	//f7 = 1;				// 先调用单形参构造函数创建临时对象, 再调用赋值操作符
	//f7 = Foo(1);		// 先创建临时对象, 再调用赋值操作符函数
	return 0;
}