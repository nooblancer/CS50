#include <stdio.h>

int main() {
    int num1, num2, temp;

    printf("Enter two integers: ");
    scanf("%i %i", &num1, &num2);

    printf("Before swapping: num1 = %i, num2 = %i\n", num1, num2);

    temp = num1;
    num1 = num2;
    num2 = temp;

    printf("After swapping: num1 = %i, num2 = %i\n", num1, num2);

    return 0;
}


