#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool encryptor(int l, char in[l], char key[25]);

int main(int argc, string argv[])
{
    // ensuring input is correct.
    // key is provided
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // key is of correct length
    else if (strlen(argv[1]) != 26)
    {
        printf("Key Must Contain 26-Charachters\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (isalpha(argv[1][i]) == false)
        {
            printf("Key Must Only Contain Alphabets\n");
            return 1;
        }
    }
    for (int f = 0; f < 26; f++)
    {
        char character = argv[1][f];
        for (int s = f + 1; s < 26; s++)
        {
            if (character == argv[1][s])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // storing key database as array
    char key[25] = "";
    for (int i = 0; i < 26; i++)
    {
        key[i] = argv[1][i];
    }
    // to check Key     printf("Key: %s\n", key);

    // recieving plain-text as input from user
    string input = get_string("plaintext: ");
    int l = strlen(input);

    // storing input as array 'plain'
    char plain[l];
    for (int i = 0; i < l; i++)
    {
        plain[i] = input[i];
    }

    // encrypting cipher-text for output using function to display
    bool a = encryptor(l, plain, key);

    // final call
    if (a)
    {
        return 0;
    }
}

bool encryptor(int l, char in[l], char key[25])
{
    // defining empty cipher as array to print later
    char cipher[l - 1];
    // printf("ciphertext: ");

    // main function loop, that creates cipher
    for (int i = 0; i < l; i++)
    {
        int index = 0;
        // ensuring lower input = lower output
        if (isalpha(in[i]))
        {
            if (islower(in[i]))
            {
                index = (in[i] - 'a');
                cipher[i] = tolower(key[index]);
            }
            // ensuring upper input = upper output
            else if (isupper(in[i]))
            {
                index = (in[i] - 'A');
                cipher[i] = toupper(key[index]);
            }
        }
        // ensuring non-alphabets remain un-encrypted
        else
        {
            cipher[i] = in[i];
        }
        // printf("%s\n", cipher);
    }
    // final display output
    printf("ciphertext: %s\n", cipher);
    // call for code
    return true;
}