//Objective: Calculate the time taken for a population to reach from x to y in years. birth rate 33%, death rate 25%. 

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // TODO: Prompt for start size
    int s;
    do
    {
        s = get_int("Starting size of Llama Population: ");
    }
    while (s < 9);

    // TODO: Prompt for end size
    int e;
    do
    {
        e = get_int("Final size of Llama Population: ");
    }
    while (e < s);

    // TODO: Calculate number of years until we reach threshold
    int y = 0;
    while (s < e)
    {
        s = s + (s / 3) - (s / 4);
        y++;
    }

    // TODO: Print number of years
    printf("Years: %i \n", y);
}