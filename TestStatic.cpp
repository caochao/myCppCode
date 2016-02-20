#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// static成员属于类全体对象所共有, 与类关联而不是与对象关联
// static成员函数不用访问非static成员
// static不能用来定义常量成员函数.因为常量成员函数目的是防止修改调用函数的对象, 然而static成员不与类对象关联, 并没有this指针
// static只能用于声明数据成员, 不能用于定义数据成员
// static成员只能在类里声明, 且必须在类外定义时并初始化
class Cls
{
public:
	Cls( int pi ): i(pi) {}
	//static void func1() const;		// error. staic不能用来定义常量成员函数
	static void func1();				// 只能在类内用static对成员声明
	static int si;
	static const int init_si = 1;		// 整形const static成员可以在类里用整形常量初始化
	static Cls sc;						// static数据成员可以声明为自身类对象
	//Cls c2;							// 非static数据成员被限定声明为其自身类对象的指针或引用
private:
	int i;
};

static int Cls::si = 1;		// 必须在类外定义并初始化static成员
const int Cls::init_si;		// 即使const static数据成员已在类内声明初始化, 仍必须在类外定义, 但不必指定初始化值

void Cls::func1() // static只能用于类定义体内部的成员声明, 不能用于类定义体外部的成员定义 
{
	//i++;		// error. static成员函数不能访问类的非static成员
}

int main(int argc, char const *argv[])
{
	Cls c(0);
	Cls &rc = c;
	Cls *pc = &c;

	c.func1();	// 如果不在类外定义func1则调用会报错

	// 以下几种方式都可以访问static成员
	cout << Cls::si << endl;
	cout << c.si << endl;
	cout << pc->si << endl;
	cout << rc.si << endl;
	return 0;
}