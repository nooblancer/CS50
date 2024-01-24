#include <stdio.h>

int main(void)
{
	float n1, n2, w1, w2, a1, a2;
	
	printf("Enter Weight of Items Sold: ");
	scanf("%f %f", &w1, &w2);
	
	printf("Enter Number of Items Sold: ");
	scanf("%f %f", &n1, &n2);
	
	a1 = w1/n1;
	a2 = w2/n2;
	
	printf("Average Value of Sales: %.2f and %.2f", a1, a2);
}
