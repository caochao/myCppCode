#include <iostream>
#include "TQueue.hpp"

using namespace std;

void testIntQueue()
{
	TQueue<int> q;
	q.push( 1 );
	q.push( -1 );
	q.push( 0 );
	q.push( 2 );
	q.pop();
	cout << q << endl;
}

void testFloatQueue()
{
	TQueue<float> q;
	q.push( 0.2 );
	q.push( 3.4 );
	q.push( 0.01 );
	q.push( 10.7 );
	cout << q << endl;
}

void testConstructor()
{
	short a[4] = { 4, 1, 2, 3 };
	double b[3] = { 0.02, 0.01, 11.4 };

	TQueue<int> q( a, a + 4 );
	cout << q << endl;

	q.assign( b, b + 3 );
	cout << q << endl;
}

int main( int argc, char **argv )
{
	testIntQueue();
	testFloatQueue();
	testConstructor();

	return 0;
}