#include <stdio.h>

int main(void)
{
	int i, x, y, sum;
	
	printf("ENTER THE THREE DIGIT NUMBER:");
	scanf("%i", &i);
	
	x = i%10;
	y = (i%1000)/100;
	
	sum = x + y;
	
	printf("SUM: %i", sum);
}
