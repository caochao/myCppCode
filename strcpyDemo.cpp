#include <stdio.h>
#include <string.h>

void testStrCpy()
{
	const char *src = "hello";
	char dst[1] = {};
	strcpy( dst, src );		// src比dst长, 会覆盖dst后面的内存空间
	printf("%s\n", dst);
}

int main()
{
	testStrCpy();
	return 0;
}