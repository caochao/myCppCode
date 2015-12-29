#include <stdlib.h>
#include <stdio.h>


void* func()
{
	int a[6];
	return &a;
}

int main()
{
	int (*(*abc)())[6] = &func;
	scanf( "press any key to quit..." );
	return 0;
}