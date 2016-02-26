// this指针与const成员函数
#include <iostream>
using std::cout;
using std::endl;

class Test
{
public:
	void non_const_func() {}			// 非常量成员函数,this指针是一个指向非const对象的const指针
	void const_func() const {}			// 常量成员函数,this指针是一个指向const对象的const指针

	void overload_func() const { cout << "const version" << endl; }		// 此种用法的const可用于重载
	void overload_func() {  cout << "non const version" << endl; }
};

int main()
{
	Test t;
	const Test t2;
	t.non_const_func();		// 非常量对象可以调用常量和非常量成员函数
	t.const_func();			
	//t2.non_const_func();	// 常量对象不可以调用非常量成员函数

	t.overload_func();		// 非常量对象优先调用非常量版本
	t2.overload_func();		// 常量对象只能调用常量版本

	return 0;
}