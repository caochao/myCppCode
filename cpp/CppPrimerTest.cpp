#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cctype>
#include <cstdlib>

using namespace std;

int test_vector()
{
	vector<string> svec;
	string str;

	cout << "enter text(ctrl+z to end):" << endl;
	while ( cin >> str )
	{
		svec.push_back( str );
	}

	if ( svec.size() == 0 )
	{
		cout << "no string?!" << endl;
		return EXIT_FAILURE;
	}

	cout << "transformed elements from the vector:" << endl;

	for ( vector<string>::size_type ix = 0; ix != svec.size(); ix++ )
	{
		for ( string::size_type index = 0; index != svec[ix].size(); index++ )
		{
			if ( islower( svec[ix][index] ) )
			{
				svec[ix][index] = toupper( svec[ix][index] );
			}
		}
		cout << svec[ix] << endl;
		if ( ( ix + 1 ) % 8 == 0 )
		{
			cout << endl;
		}
	}
	return EXIT_SUCCESS;
}

void test_bitset()
{
	bitset<8> b(32);
	cout << b << "=" << b.to_ulong() << endl;
}

void test_constcast( char *str )
{

}

void test_static()
{
	static int i = 0;
	i++;
	cout << "static local object i = " << i << endl;
}

// 指向const对象的指针既能指向const对象, 也能指向非const对象.不能通过指向const对象的指针来修改其指向的值
// 不能将指向non const对象的指针指向const对象.
// const指针定义时必须初始化, 其值不能更改
//string str;
//int i;
int main( int argc, char const *argv[] )
{
	for ( int i = 0; i != 10; ++i )
	{
		test_static();
	}
	// string str;
	// int i;
	// cout << str << i << endl;

	// test_vector();
	// test_bitset();

	// const char *cstr = "牛b";
	// //test_constcast( cstr );
	// test_constcast( const_cast<char*>( cstr ) );

	int *pi = new int(1024);
	cout << *pi << endl;
	delete pi;

	string *ps = new string;
	cout << "addr=" << ps << ", value=" << *ps << endl;
	delete ps;

	string s = string();
	cout << "addr=" << &s << ", value=" << s << endl;

	// const &既可引用const对象, 也可引用非const对象
	// 非const &只可引用非const对象
	int i = 1;
	const int ci = 2;

	const int &ri = 0;
	const int &rii = i;
	//int &rci = ci;

	// 指向const对象的指针既可指向const对象, 也可指向非const对象
	// 但指向非const对象的指针不可指向const对象
	const int *ppi = &i;
	const int *ppci = &ci;
	//int *pppi = &ci;


	return EXIT_SUCCESS;
}