#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT( FORMAT, VALUE ) \
		printf("the value of " #VALUE " is " FORMAT "\n", VALUE);

#ifndef DEBUG
//#if !defined(DEBUG)
#define DEBUG 1
#endif


// 将10进制数字转换为指定的进制字符串
void int2binary( int value, int radix )
{
	int div = value / radix;
	if ( div != 0 )
	{
		int2binary( div, radix );
	}
	int remainder = value % radix;
	remainder = remainder > 10 ? ( ( remainder - 10 ) + 'a' ) : ( remainder + '0' );
	printf( "%c", remainder );//注意值是char类型
}

// JosephCycleDemo.exe -o -c test
// JosephCycleDemo -o -c test
// argc为4, argv是有4个char*元素的数组
void parseArgs( int argc, char** argv )
{
    // for( char** p = argv; p < argv + argc; p++ )
    // {
    //     printf("%s\n", *p);
    // }

    while ( *++argv != NULL )
    {
        printf("%s\n", *argv);
    }
}

int main( int argc, char** argv )
{
    //parseArgs( argc, argv );

    //int2binary( 11, 16 );
    //int2binary( 11, 2 );
    int2binary( 11, 10 );
    PRINT("%s","caochao")

    scanf( "press any key to quit..." );
    return 0;
}