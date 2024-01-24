#include <stdio.h>

int main(void)
{
	int i, x, y, t;
	
	printf("ENTER THE TWO DIGIT NUMBER:");
	scanf("%i", &i);
	
	if(i>99 || i<10)
	{
		printf("ONLY TWO DIGIT NUMBERS");
		return 1;
	}
	
	x = i%10;
	y = (i%100)/10;
	
	t = x;
	x = y;
	y = t;
	
	printf("REVERSED NUMBER: %i%i", y,x);
	return 0;
}
