#include <stdlib.h>
#include <stdio.h>

// 有序数组去重, 返回丢弃区起始位置索引
template < typename Type, int size >
Type* sortedArrayUnique( const Type (&array)[size], Type* begin, Type* end )
{
	// 传入的数组为空或长度为1, 直接返回
	if ( array == NULL || size == 1 )
	{
		return NULL;
	}
	Type* pi = begin;
	Type* pj = begin + 1;
	while ( pj < end )
	{
		if ( *pi != *pj )
		{
			pi++;
			*pi = *pj;
		}
		pj++;
	}
	return pi + 1;
}

// 打印数组
template < typename Type, int size >
void printArray( const Type(&array)[size], Type* begin, Type* end, char* fmt )
{
	for ( ; begin < end; begin++ )
	{
		printf( fmt, *begin );
	}
}

template < typename Type, int size >
Type min( Type (&r_array)[size] )
{
	Type min_val = r_array[0];
	for ( int i = 0; i < size; i++ )
	{
		if ( r_array[i] < min_val )
		{
			min_val = r_array[i];
		}
	}
	return min_val;
}

typedef int (&RAI)[5];
int func( int (*method)(RAI), RAI arg )
{
	return method(arg);
}

typedef float (&RAF)[6];
float func( float (*method)(RAF), RAF arg )
{
	return method(arg);
}

int main()
{
	// int
	int ia[5] = { 4, 3, 5, 0, -1 };
	int min1 = min( ia );
	printf("%d\n", min1 );

	// float
	float fa[6] = { 4.0, 5.3, 5.7, 0.2, 11.5, 9.0 };
	float min2 = min( fa );
	printf("%f\n", min2 );

	// char
	char ca[4] = { 'c', 'Z', 'f', 'd' };
	char min3 = min( ca );
	printf("%c\n", min3 );

	// int
	int min4 = func( &min, ia );
	printf("%d\n", min4 );

	// float
	float min5 = func( &min, fa );
	printf("%f\n", min5 );

	// sorted array uniqify-int
	int sorted_ia[9] = { 1, 1, 1, 2, 2, 3, 4, 4, 5 };
	int* iborder = sortedArrayUnique( sorted_ia, sorted_ia, sorted_ia + 9 );
	printArray( sorted_ia, sorted_ia, iborder, "%d->" );

	scanf( "press any key to quit..." );
	return 0;
}