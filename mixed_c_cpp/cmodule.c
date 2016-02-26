#include "cmodule.h"

//extern int sub( int a, int b );		// 声明在此使用cppmodule.hpp中的extern "C" int sub( int a, int b );

// 定义cmodule.h中的全局add函数
int add( int a, int b )
{
	return a + b;
}

// int main(int argc, char const *argv[])
// {
// 	sub(2,1);	
// 	return 0;
// }