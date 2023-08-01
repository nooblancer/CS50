#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // ensuring the key is correct
    // a) only 1 input
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // b) only integer input
    bool a = only_digits(argv[1]);
    if (a == false)
    {
        printf("Key must only contain Digits\n");
        return 1;
    }

    // storing the key
    int key;
    key = atoi(argv[1]);

    // check stored key    printf("Key: %i\n", key);

    // getting plain-text
    string plain = get_string("plaintext: ");

    // encrypting plain-text
    printf("ciphertext: ");

    // working loop
    for (int i = 0; i < strlen(plain); i++)
    {
        char cipher = (rotate(plain[i], key));
        // printing cipher-text
        printf("%c", cipher);
    }
    printf("\n");
    // code ends
}

// func 1
bool only_digits(string s)
{
    bool r = true;
    // working loop
    for (int i = 0; i < strlen(s); i++)
    {
        if (isdigit(s[i]) == false)
        {
            r = false;
            break;
        }
    }
    return r;
}

// func 2
char rotate(char c, int n)
{
    char x;
    // encrypt if alphabetic charachter
    // and rounding by 26 if needed.
    if (isupper(c))
    {
        x = (((c - 'A' + n) % 26) + 'A');
    }
    else if (islower(c))
    {
        x = (((c - 'a' + n) % 26) + 'a');
    }
    // ignore if any other charachter
    // and print as it is
    else
    {
        x = c;
    }
    return x;
}