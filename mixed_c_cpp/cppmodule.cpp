extern "C"					//extern "C"指示编译器按c语言方式编译cmodule.h.
{							//c不支持函数重载, 编译后的函数原型为add, c++为add_int_int
	#include "cmodule.h"
}

#include "cppmodule.hpp"

int sub( int a, int b )
{
	return a - b;
}

int main(int argc, char const *argv[])
{
	int ret = add( 1, 2 );
	return 0;
}


