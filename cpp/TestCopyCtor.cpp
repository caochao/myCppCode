#include <string>
#include <iostream>
using namespace std;

// 自定义复制构造函数
class Foo
{
public:
	Foo(): ival(0), sval( "empty" ) { cout << "Foo()" << endl; }
	Foo( int i ): ival(i), sval( "empty" ) { cout << "Foo( int i )" << endl; }
	Foo( const Foo& );		// 似乎这里的explicit
	Foo& operator=( const Foo& );
private:
	int ival;
	string sval;
};

Foo::Foo( const Foo& rhs ): ival( rhs.ival ), sval( rhs.sval )
{
	cout << "Foo( const Foo& rhs )" << endl;
}

Foo& Foo::operator=( const Foo& rhs )
{
	ival = rhs.ival;
	sval = rhs.sval;
	cout << "Foo& operator=( const Foo& rhs )" << endl;
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