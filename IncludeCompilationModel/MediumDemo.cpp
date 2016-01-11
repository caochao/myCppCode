// 调用函数模板medium, 在保存int类型对象的vector中查找中间值

#include "Medium.hpp"
#include <iostream>
using namespace std;

int main()
{
	int ia1[] = { 1, 2, 3, 4, 5, 6, 7 };
	int ia2[] = { 1, 2, 3, 4 };
	int ia3[] = { 1, 2, 2, 3, 4, 5, 6 };
	vector<int> ivec1( ia1, ia1 + 7 );
	vector<int> ivec2( ia2, ia2 + 4 );
	vector<int> ivec3( ia3, ia3 + 7 );
	int m;

	// ivec1
	if ( medium( ivec1, m ) )
	{
		cout << "ivec1 medium:" << m << endl;
	}
	else
	{
		cout << "no median" << endl; 
	}

	// ivec2
	if ( medium( ivec2, m ) )
	{
		cout << "ivec2 medium:" << m << endl;
	}
	else
	{
		cout << "no median" << endl; 
	}

	// ivec3
	if ( medium( ivec3, m ) )
	{
		cout << "ivec3 medium:" << m << endl;
	}
	else
	{
		cout << "no median" << endl; 
	}
}