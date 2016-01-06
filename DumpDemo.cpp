#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>

#define BUFFER_SIZE 65			// 63个字符+NUL结尾符+\n换行符
#define BIN_SIZE 16				// 16个字符

// dump一个文本, 表示stream的16进制内容
void dump( FILE *input, FILE *output )
{
	long offset;
	int len;
	char buffer[ BUFFER_SIZE ];			// 一行文本
	unsigned char data[ BIN_SIZE ];		// 存放16个字节的2进制数据

	// 以空白字符填充buffer
	memset( buffer, ' ', BUFFER_SIZE - 1 );
	buffer[ 45 ] = '*';
	buffer[ 62 ] = '*';
	buffer[ BUFFER_SIZE - 2 ] = '\n';
	buffer[ BUFFER_SIZE - 1 ] = '\0';

	offset = 0;

	// 一次读取16个char, len表示实际读取的字符数
	// 注意fread可从流中读取结构体数据, 所以实际读取的字节数=sizeof(type)*count
	while ( ( len = fread( data, sizeof( char ), BIN_SIZE, input ) ) > 0 )
	{
		int i;
		char *hex_ptr, *char_ptr;

		// 构造每一行, 用offset控制偏移
		sprintf( buffer, "%06X  ", offset );
		hex_ptr = buffer + 8;
		char_ptr = buffer + 46;
		memset( hex_ptr, ' ', 35 );
		memset( char_ptr, ' ', 16 );

		// 按格式转化data和其对应的内容
		for ( i = 0; i < len; i++ )
		{
			// 每1字节数据表示为2位宽度的16进制字符串
			sprintf( hex_ptr, "%02X", data[i] );
			hex_ptr += 2;
			*hex_ptr = ' ';

			// 4个字节一组
			if ( i % 4 == 3 )
			{
				hex_ptr++;
			}

			// 如果字符不可打印就打印一个句点
			if ( isprint( data[i] ) || data[i] == ' ' )
			{
				*char_ptr++ = data[i];
			}
			else
			{
				*char_ptr++ = '.';
			}
		}

		// 将行写入输出流, 并更新offset
		fputs( buffer, output );

		offset += len;
	}
}

// dump文件, 如果没有指定文件则dump stdin
// DumpDemo E:\\code\\cplus\\test.cpp E:\\code\\cplus\\ret
int main( int argc, char **argv )
{
	// argv第一个参数是当前文件名
	if ( argc <= 1 )
	{
		dump( stdin, stdout );
		return EXIT_SUCCESS;
	}

	// 要dump的文件
	FILE *input = fopen( argv[1], "rb" );
	if ( input == NULL )
	{
		perror( argv[1] );
		exit( EXIT_FAILURE );
	}

	// dump结果文件
	FILE *output = fopen( argv[2], "w" );
	if ( output == NULL )
	{
		perror( argv[2] );
		exit( EXIT_FAILURE );
	}

	// 让子弹飞
	dump( input, output );

	// 关闭文件流
	int ifc = fclose( input );
	if ( ifc != 0 )
	{
		perror( "ifc fclose" );
		exit( EXIT_FAILURE );
	}

	int ofc = fclose( output );
	if ( ofc != 0 )
	{
		perror( "ofc fclose" );
		exit( EXIT_FAILURE );
	}

	return EXIT_SUCCESS;
}