#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y)
{
	int sum = x + y;
	int temp;

	!(x&INT_MIN) && !(y&INT_MIN)&&__builtin_add_overflow(x,y,&temp) && (sum=INT_MAX);
	(x&INT_MIN) && (y&INT_MIN) && __builtin_add_overflow(x, y, &temp) && (sum = INT_MIN);

	return sum;
}