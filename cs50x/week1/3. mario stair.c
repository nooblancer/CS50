//Objective: Make a staircase like in mario (game) with height being inputted by user. 

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Take height input
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    //Wall Master Loop
    for (int i = 1; i <= height; i++)
    {
        //Loop 1
        for (int a = height; a > i; a--)
        {
            printf(" ");
        }
        //Loop 2
        for (int b = 1; b <= i; b++)
        {
            printf("#");
        }
        //indent for next layer
        printf("\n");
    }
}
