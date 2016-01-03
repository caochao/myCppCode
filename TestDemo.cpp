#include <stdlib.h>
#include <stdio.h>

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

int main()
{
	int a[6] = { 1, 1, 1, 1, 1, 1 };
	int ret = mostFre( a, 0, 6 );
	printf("the mostFre elem is:%d\n", ret);

	scanf( "press any key to quit..." );
	return 0;
}