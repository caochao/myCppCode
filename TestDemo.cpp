#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>

// 在有序数组中, 找出出现次数最频繁的元素
// 如果有多个值出现的次数相同,则返回先出现的值
int mostFre( const int (&array)[6], int start, int end )
{
	int occu = 0, maxOccu = 0;
	int currElem = 0, preElem = array[0], maxOccuElem = array[0];

	while ( start != end )
	{
		currElem = array[start];
		if ( currElem != preElem )
		{
			printf("currElem=%d, preElem=%d, occu=%d, maxOccu=%d\n", currElem, preElem, occu, maxOccu );
			if ( occu > maxOccu )
			{
				maxOccu = occu;
				maxOccuElem = preElem;
				printf("maxOccu=%d, maxOccuElem=%d\n", maxOccu, maxOccuElem);
			}
			preElem = currElem;
			occu = 0;
		}
		occu++;
		start++;
	}

	// 考虑最后几个元素值相同的情况
	if ( occu > maxOccu )
	{
		maxOccu = occu;
		maxOccuElem = preElem;
		printf("end:::::::maxOccu=%d, maxOccuElem=%d\n", maxOccu, maxOccuElem);
	}

	return maxOccuElem;
}

template < typename Type, int size >
void printArray( const Type(&array)[size], Type* begin, Type* end, char* fmt )
{
	for ( ; begin < end; begin++ )
	{
		printf( fmt, *begin );
	}
}

void initRandomSeed()
{
	srand( ( unsigned int )( time( ( time_t )NULL ) ) );
}	

void shuffle( int *deck, int n_cards )
{
	int r;
	for ( int i = n_cards - 1; i > 0; i-- )
	{
		r = rand() % ( i + 1 );
		if ( r == i ) continue;
		deck[i] ^= deck[r];
		deck[r] ^= deck[i];
		deck[i] ^= deck[r];
		printf("r=%d, i=%d, deck[r]=%d, deck[i]=%d\n", r, i, deck[r], deck[i] );
	}
}

void testShuffle()
{
	const int num = 11;
	int a[num] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	shuffle( a, num );
	printArray( a, a, a + num, "%d-" );
}

void testTime()
{
	const time_t t = time(NULL);
	struct tm *t2 = localtime( &t );

	const int TIME_STR_SIZE = 100;
	char timeStr[TIME_STR_SIZE];
	size_t timeSize = strftime( timeStr, TIME_STR_SIZE, "今天是%Y-%m-%d, 星期%w, 现在时间是%H:%M:%S", t2 );

	printf( "timeSize=%d, timeStr=%s\n", timeSize, timeStr );
}

void testLocale()
{
	char *oldLocale = setlocale( LC_ALL, NULL );
	printf("oldLocale=%s\n", oldLocale);
}

void recPrintNum( int num )
{
	int quotient = num / 10;
	int remainder = num % 10;

	if ( quotient > 0 )
	{
		recPrintNum( quotient );
	}
	putchar( '0' + remainder );
}

// 迭代方法计算fibonacci数列第n个值
// 			n == 1: 1
//fibo_n = 	n == 2: 1
// 			n > 2: fibo_n( n - 1 ) + fibo_n( n - 2 )
long fibo_n( int n )
{
	long f = 1, g = 1;
	while ( n > 2 )
	{
		g = g + f;
		f = g - f;
		n--;
	}
	return g;
}

int main()
{
	int a[6] = { 1, 1, 1, 1, 1, 1 };
	int ret = mostFre( a, 0, 6 );
	printf("the mostFre elem is:%d\n", ret);

	testTime();
	testLocale();
	initRandomSeed();
	testShuffle();

	printf("\nbinary2ascii:");
	recPrintNum( 4399 );

	printf("\nfibo:");
	printf("%d\n", fibo_n( 10 ) );

	scanf( "press any key to quit..." );
	return 0;
}