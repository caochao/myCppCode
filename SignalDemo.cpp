#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//void ( *signal( int, void (*handler)(int)))(int);

void raiseSignal( int sig )
{
	int t = raise( sig );
	printf( "raiseSignal:sig=%d, result=%d\n", sig, t );
}

void ON_SIGABRT( int sig )
{
	printf( "ON_SIGABRT:receive sig:%d\n", sig );
}

void ON_SIGFPE( int sig )
{
	printf( "ON_SIGFPE:receive sig:%d\n", sig );
}

void ON_SIILL( int sig )
{
	printf( "ON_SIILL:receive sig:%d\n", sig );
}

void ON_SSEGV( int sig )
{
	printf( "ON_SSEGV:receive sig:%d\n", sig );
}

void ON_SINT( int sig )
{
	printf( "ON_SINT:receive sig:%d\n", sig );
}

void ON_STERM( int sig )
{
	printf( "ON_STERM:receive sig:%d\n", sig );
}

void registerSignalHandler()
{
	signal( SIGABRT, ON_SIGABRT );
	signal( SIGFPE, ON_SIGFPE );
	signal( SIGILL, ON_SIILL );
	signal( SIGSEGV, ON_SSEGV );
	signal( SIGINT, ON_SINT );
	signal( SIGTERM, ON_STERM );
}

void test1()
{
	void (*p)();
	p();
}

void test2()
{
	int a = 10/0;
}

void test3()
{
	int a[4] = { 0, 0, 0, 0 };
	int *p = a;
	*--p = 0;
}

void test4()
{
	int a[5];
	int *p = a + 5;
	*p = 0;
}

void test5()
{
	abort();
}

void test6()
{
	exit( EXIT_SUCCESS );
}

int main(int argc, char const *argv[])
{
	registerSignalHandler();

	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	test6();

	scanf( "press any key to quit" );
	return 0;
}