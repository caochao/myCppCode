#include <stdio.h>
#include <stdlib.h>

// 数字字符串转为int整数
// 123abc ok
// abc123 error
int my_atoi( const char *str )
{
	if ( str == NULL ) return 0;

	while ( *str == ' ' || *str == '\t' || *str == '+' )
	{
		str++;
	}

	int num = 0;
	int minus = 1;

	if ( *str == '-' )
	{
		minus = -1;
		str++;
	}

	// 第1个非符号位非数字, 判定为非法输入
	if ( *str < '0' || *str > '9' )
	{
		return 0;
	}

	// 跳过形如123abc的后半部分
	while ( *str != '\0' && *str >= '0' && *str <= '9' )
	{
		num = num * 10 + ( *str - '0' );
		str++;
	}
	num *= minus;

	// 是否溢出int范围
    if( num > 0x7fffffff || num < ( signed int )0x80000000 )  
    {
    	return 0;
    }
    return num;
}

int main(int argc, char const **argv )
{
	char input[10];
	printf("input str:");
	scanf( "%s", &input );
	printf( "input=%s, ret=%d\n", input, my_atoi( input ) );

	return 0;
}