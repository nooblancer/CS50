#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void nextPermutation(int *nums, int numsSize);

int main(int argc, char *argv[])
{
    // taking array input
    int s = argc - 1;
    int arr[s];
    for (int i = 0; i < s; i++)
    {
        arr[i] = atoi(argv[i + 1]);
    }

    nextPermutation(arr, s);

    return 0;
}

void nextPermutation(int *nums, int numsSize)
{
    int value = 0;
    for (int i = 0; i < numsSize; i++)
    {
        value = value + (nums[i]*pow(10, numsSize - i - 1));
    }
}
