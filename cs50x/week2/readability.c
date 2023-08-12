#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sents(string text);

int main(void)
{
    string text = get_string("Text: ");

    count_letters(text);
    // to check no. of letters    printf("%i letters\n", count_letters(text));

    count_words(text);
    // to check no. of words    printf("%i words\n", count_words(text));

    count_sents(text);
    // to check no. of sentences    printf("%i sentences\n", count_sents(text));

    // L is the average number of letters per 100 words in the text
    float L = (count_letters(text) * 100.0 / count_words(text));
    // to check L    printf("L: %f\n", L);

    // S is the average number of sentences per 100 words in the text
    float S = (count_sents(text) * 100.0 / count_words(text));
    // to check S    printf("S: %f\n", S);

    double index = 0.0588 * L - 0.296 * S - 15.8;
    // to check index    printf("Index: %f\n", index);
    int X = round(index);

    // required results
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", X);
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    return (words + 1);
}

int count_sents(string text)
{
    int sents = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if ((text[i] == '.') && (text[i + 1] == '.'))
        {
        }
        else if ((text[i]) == '!' || (text[i]) == '?' || (text[i]) == '.')
        {
            sents++;
        }
    }
    return sents;
}
