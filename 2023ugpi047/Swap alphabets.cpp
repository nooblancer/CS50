#include <stdio.h>

int main(void)
{
	char ch;
	printf("ENTER THE INPUT:");
	scanf("%c", &ch);
	
	if(ch>=65 && ch<=91)
	{
		ch = ch + 32;
		printf("%c\n", ch);
	}
	
	else if(ch>=97 && ch<=123)
	{
		ch = ch -32;
		printf("%c\n", ch);
	}
	
	else
	{
		printf("INPUT IS NOT AN ALPHABET");
	}
}

