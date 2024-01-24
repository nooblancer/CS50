#include <stdio.h>
int main(void)
{
	int i;

    printf("Enter integer: ");
    scanf("%i", &i);
    
    (i%2==0)?printf("Even\n"):printf("Odd\n");
    return 0;
}

