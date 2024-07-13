// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
int C = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int h = hash(word);

    node *temp = table[h];
    while (temp != NULL)
    {
        if (strcasecmp(temp->word, word) == 0)
            return true;
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
        return false;

    char str[LENGTH + 1];
    while (fscanf(dict, "%s", str) != EOF)
    {
        node *temp = (node *) malloc(sizeof(node));
        if (temp == NULL)
            return false;

        strcpy(temp->word, str);

        int h = hash(str);

        if (table[h] == NULL)
            temp->next = NULL;
        else
            temp->next = table[h];
        table[h] = temp;

        C++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return C;
}

void freenode(node *n)
{
    if (n->next != NULL)
        freenode(n->next);
    free(n);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
            freenode(table[i]);
    }
    return true;
}
