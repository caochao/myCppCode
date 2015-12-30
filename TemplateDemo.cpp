#include <stdlib.h>
#include <stdio.h>

template < typename T1, typename T2, typename T3 >
inline T1 foo( T2 t2, T3 t3 )
{
	T1 t1;
	return t1; 
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

	scanf( "press any key to quit..." );
	return 0;
}