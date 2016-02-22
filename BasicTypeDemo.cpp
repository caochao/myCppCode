#include <stdio.h>

enum ValueEnum
{
	INT = 0,
	NUMBER,
	STRING
};

union ValueUnion
{
	int iValue;
	float fValue;
	char cValue;
};

struct ValueStruct
{
	int iValue;
	float fValue;
	char cValue;
};

void testValueEnum()
{
	printf("testValueEnum\n");
	ValueEnum ve = STRING;
	printf( "%d\n", ve );
}

void testValueUnion()
{
	printf("testValueUnion\n");
	ValueUnion vu;
	//vu.cValue = 'a';
	vu.fValue = 3.14;
	printf( "%d\n", vu.iValue );
	printf( "%f\n", vu.fValue );
	printf( "%c\n", vu.cValue );
}

void testValueStruct()
{
	printf("testValueStruct\n");
	ValueStruct vs;
	vs.iValue = 97;
	printf( "%d\n", vs.iValue );
	printf( "%f\n", vs.fValue );
	printf( "%c\n", vs.cValue );
}

int main(int argc, char const *argv[])
{
	testValueEnum();
	testValueUnion();
	testValueStruct();
	return 0;
}