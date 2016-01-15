#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

// 标记是否要输出结果到文件
char file_output = FALSE;

// 函数原型
char **do_args( char ** );
unsigned short getsum( FILE * );
void printsum( unsigned short, char * );

// 如果命令行参数给出文件名, 则求文件检验和. 否则求stdin检验和
// 如果命令行参数提供-f选项, 则将结果写入文件. 否则写入stdout
// CheckSumDemo E:/code/cplus/test.cpp
int main( int argc, char **argv )
{
	FILE *f;
	unsigned short sum;

	argv = do_args( argv );
	if ( *argv == NULL )
	{
		if ( file_output )
		{
			fprintf( stderr, "-f illegal with standard input\n" );
			exit( EXIT_FAILURE );
		}
		sum = getsum( stdin );
		printsum( sum, NULL );
		return EXIT_SUCCESS;
	}

	// 处理命令行中每一个文件
	for ( ; *argv != NULL; argv++ )
	{
		f = fopen( *argv, "r" );
		if ( f == NULL )
		{
			perror( *argv );
			exit( EXIT_FAILURE );
		}
		else
		{
			sum = getsum( f );
			fclose( f );
			printsum( sum, *argv );
		}
	}
	return EXIT_SUCCESS;
}

// CheckSumDemo -f t1.txt t2.txt
// CheckSumDemo t1.txt
// CheckSumDemo
// 解析命令行options
char **do_args( char **av )
{
	// 跳过程序名, 逐一查看命令行参数
	while ( *++av != NULL && **av == '-' )
	{
		// 逐字符查看以"-"开头的参数字符串
		while ( *++*av != '\0' )
		{
			// 寻找option
			switch ( **av )
			{
				case 'f':
					file_output = TRUE;
					break;
				default:
					fprintf( stderr, "illegal option:%c\n", **av );
					break;
			}
		}
	}
	return av;
}

// 获取文件checksum
unsigned short getsum( FILE *f )
{
	unsigned short sum = 0;
	int ch;
	while ( ( ch = getc( f ) ) != EOF )
	{
		sum += ch;
	}
	return sum;
}

void printsum( unsigned short sum, char *in_name )
{
	char *out_name;
	FILE *f;

	if ( !in_name )
	{
		printf( "sum:%u\n", sum );
		return;
	}

	// out_name要比in_name多5个字符长度, ".cks"+NUL
	out_name = ( char* )malloc( sizeof( char ) * strlen( in_name ) + 5 );
	if ( out_name == NULL )
	{
		fprintf( stderr, "malloc:out of memory\n" );
		exit( EXIT_FAILURE );
	}

	strcpy( out_name, in_name );
	strcat( out_name, ".cks" );

	f = fopen( out_name, "w" );
	if ( f == NULL )
	{
		perror( out_name );
		exit( EXIT_FAILURE );
	}
	else
	{
		fprintf( f, "sum:%u\n", sum );
		fclose( f );
	}
	free( out_name );
}