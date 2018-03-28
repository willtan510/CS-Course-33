#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y)
{
	int sum = x + y;
	
	int posCheck = !(x&INT_MIN) && !(y&INT_MIN) && (sum & INT_MIN);	//if x and y are both positive, and sum ends up negative, posCheck is 1
	int negCheck = (x&INT_MIN) && (y&INT_MIN) && !(sum &INT_MIN);	//if x and y are both negative, and the sum ends up positive, negCheck is 1

	posCheck && (sum = INT_MAX);
	negCheck && (sum = INT_MIN);

	return sum;
}
