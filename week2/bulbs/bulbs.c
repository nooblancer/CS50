#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    // getting the message
    string message = get_string("Input the message: ");

    int bit[8];

    for (int i = 0; i < strlen(message); i++)
    {
        int x = message[i];

        for (int j = 0; j < 8; j++)
        {
            if (x % 2 == 1)
            {
                bit[7 - j] = 1;
            }
            else
            {
                bit[7 - j] = 0;
            }
            x = x / 2;
            // check stored value            printf("%i", bit[7 - j]);
        }

        for (int k = 0; k < 8; k++)
        {
            // check actual value            printf("%i", bit[k]);
            print_bulb(bit[k]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}