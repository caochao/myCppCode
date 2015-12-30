#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// #define max( a, b ) ( ( a ) > ( b ) ? ( a ) : ( b ) )
// #define min( a, b ) ( ( a ) > ( b ) ? ( b ) : ( a ) )


template<class Type>
inline Type min( Type t1, Type t2 )
{
	t1 < t2 ? t1 : t2;
}

template<typename Type>
inline Type max( Type t1, Type t2 )
{
	t1 > t2 ? t1 : t2;
}

// 截取srcStr从start位置开始, 长度为len的子串
char* substr( const char* srcStr, int start, int len )
{
	if ( srcStr == NULL ) 
	{
		printf( "invalid arg:srcStr = NULL\n" );
		return NULL;
	}
	int srcLen = strlen( srcStr );

	if ( start < 0 || start >= srcLen )
	{
		printf( "invalid arg:start =%d, should be in range[ 0, strlen( srcStr ) )\n", start );
		return NULL;
	}

	if ( len < 0 )
	{
		printf( "invalid arg:len =%d, must larger than 0\n", len );
		return NULL;
	}

	int destLen = min( srcLen - start, len );
	char* destStr = (char*)malloc( sizeof( char ) * ( destLen + 1 ) );
	strncpy( destStr, srcStr + start , destLen );
	destStr[ destLen ] = '\0';	// make sure str ends with '\0'
	return destStr;
}

// 截取srcStr位于[start, end)区间的子串
char* substring( const char* srcStr, int start, int end )
{
	if ( srcStr == NULL )
	{
		printf( "invalid arg:srcStr = NULL\n" );
		return NULL;
	}
	int srcLen = strlen( srcStr );

	if ( start < 0 || end < 0 || start > srcLen || start > end )
	{
		printf( "invalid args\n", start );
		return NULL;
	}

	int destLen = min( srcLen - start, end - start );
	char* destStr = (char*)malloc( sizeof( char ) * ( destLen + 1 ) );
	strncpy( destStr, srcStr + start, destLen );
	destStr[ destLen ] = '\0';
	return destStr;
}

int main()
{
	char* str = "cao,hi";

	// test substr
	char* s = substr( str, 1, -3 );
	if ( s != NULL )
	{
		printf("%s, %d\n", s, strlen( s ) );
		free( s );
	}

	// test substring
	char* s2 = substring( str, 1, 0 );
	if ( s2 != NULL )
	{
		printf("%s, %d\n", s2, strlen( s2 ) );
		free( s2 );	
	}

	scanf( "press any key to quit..." );
	return 0;
}