#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 行长度必须>=2, 因为要预留一个字节放NUL字符
// 如果值小于实际行长度, 不会影响程序结果, 因为fgets会从下个字节继续读
#define MAX_LINE_LENGTH 1024

// 字符串方式逐行复制
void copyLines( FILE* input, FILE* output )
{
	char buffer[MAX_LINE_LENGTH];

	// 读取到EOF(-1)时, fgets返回NULL, 否则返回buffer地址
	while ( fgets( buffer, MAX_LINE_LENGTH, input ) != NULL )
	{
		fputs( buffer, output );
	}
}

// 以二进制方式复制
void copyBins( FILE* input, FILE* output )
{
	const int BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];
	int count;

	// 读取到文件尾时, fread返回0
	while ( ( count = fread( buffer, sizeof( char ), BUFFER_SIZE, input ) ) != 0 )
	{
		fwrite( buffer, sizeof( char ), count, output );
	}
}

// 复制srcFile到destFile, srcFile必须存在, destFile动态创建
void copyFiles( char* srcFile, char* destFile )
{
	// 打开文件流
	FILE* input = fopen( srcFile, "r" );
	if ( input == NULL )
	{
		perror( srcFile );
		exit( EXIT_FAILURE );
	}

	FILE* output = fopen( destFile, "w" );
	if ( output == NULL )
	{
		perror( destFile );
		exit( EXIT_FAILURE );
	}

	// 逐行复制
	copyLines( input, output );

	// 二进制复制
	//copyBins( input, output );

	// 关闭文件流
	int ifc = fclose( input );
	if ( ifc != 0 )
	{
		perror( "ifc fclose" );
		exit( EXIT_FAILURE );
	}

	int dfc = fclose( output );
	if ( dfc != 0 )
	{
		perror( "dfc fclose" );
		exit( EXIT_FAILURE );
	}
}

// 注意. 操作系统换行符的差异导致在文本流中不能根据实际写入字符数的计算结果定位到文本流的一个位置
// 但ftell()返回的偏移量处理了这种差异, 所以在文本流中只能使用ftell配合fseek使用
void append2TxtStream( char* fileName, char* txt )
{
	// 以写入文本方式打开
	FILE* txtStream = fopen( fileName, "a" );
	if ( txtStream == NULL )
	{
		perror( fileName );
		exit( EXIT_FAILURE );
	}

	// 定位并写入
	long end = ftell( txtStream );
	fseek( txtStream, end, SEEK_SET );
	fputs( txt, txtStream );

	// 关闭文件流
	int fc = fclose( txtStream );
	if ( fc != 0 )
	{
		perror( "fclose" );
		exit( EXIT_FAILURE );
	}
}

void testTmpName()
{
	char buffer[L_tmpnam];
	tmpnam( buffer );
	printf("buffer=%s\n", buffer);

	char* ptr = tmpnam( NULL );
	printf("ptr=%s\n", ptr);
}

int read_int()
{
	int ch, value = 0;
	while ( ( ch = getchar() ) != EOF && isdigit( ch ) )
	{
		//value *= 10;
		//value += ch - '0';
		value = value * 10 + ch - '0';
	}

	ungetc( ch, stdin );	// 观察加不加这句, 下一个getchar()调用返回值的区别
	printf("nextchar=%c\n", getchar());
	return value;
}

int main()
{
	printf( "FOPEN_MAX=%-6d\n", FOPEN_MAX );
	printf( "FILENAME_MAX=%d\n", FILENAME_MAX );
	printf("BUFSIZ=%d\n", BUFSIZ);

	copyFiles( "E:\\code\\cplus\\test.cpp", "E:\\code\\cplus\\test2.cpp" );

	append2TxtStream( "E:\\code\\cplus\\test2.cpp", "//test append2TxtStream" );

	testTmpName();

	//printf("read_int=%d\n", read_int());

	scanf( "press any key to quit..." );
	return 0;
}