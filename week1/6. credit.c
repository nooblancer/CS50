//Objective: Checking validity of a credit card using Luhn's Algorithm, and the company based on their number patterns.

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //Getting Card No.
    long cc = get_long("Number: ");

    if (cc < 1000000000000)
    {
        printf("INVALID\n");
        exit(EXIT_SUCCESS);
    }

    //Checksum using Luhn’s Algorithm
    //Sorting Digits 1
    //every other digit, starting with the number's first from last digit
    long n1 = cc;
    int sum1 = 0;

    while (n1 > 0)
    {
        //add those digits together
        sum1 = (sum1 + (n1 % 10));
        //reducing the number
        n1 = (n1 / 100);
    }

    //Sorting Digits 2
    //every other digit, starting with the number’s second-to-last digit
    long n2 = cc / 10;
    int sum2 = 0;

    while (n2 > 0)
    {
        //Multiply digit by 2, and then add those products’ digits together
        sum2 = (sum2 + (((n2 % 10) * 2) % 10) + ((((n2 % 10) * 2) / 10) % 10));
        //reducing the number
        n2 = (n2 / 100);
    }

    //Checking Card Validity using Checksum algo
    int sum = (sum1 + sum2);

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        exit(EXIT_SUCCESS);
    }

    //Checking Company
    while (cc > 99)
    {
        cc = (cc / 10);
    }
    if (cc >= 51 && cc <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if (cc == 34 || cc == 37)
    {
        printf("AMEX\n");
    }
    else if (cc >= 40 && cc <= 49)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}