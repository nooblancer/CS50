#include <stdio.h>

int main() {
    int num1, num2, num3, max;

    printf("Enter three integers: ");
    scanf("%i %i %i", &num1, &num2, &num3);

    (num1 > num2)?((num1 > num3)?(max = num1):(max = num3)):((num2 > num3)?(max = num2):(max = num3));


    printf("The maximum of the three integers is %i.\n", max);
    return 0;
}


