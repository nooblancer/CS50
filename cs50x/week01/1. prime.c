//Objective of this practice problem was to write the code that generates prime numbers betwween two limits, which are inputed by the user. 

#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min + 1; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

//main function
bool prime(int i)
{
    //TODO
    //Checks if number if prime or not
    for (int x = 2; x < i; x++)
    {
        if (i % x == 0)
        {
            return false;
        }
    }
    return true;
}
