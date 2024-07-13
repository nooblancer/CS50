// Simulate genetic inheritance of blood type
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GEN = 7;
const int IL = 4;

person *head = NULL;

person *create_family(int gen);
void print_family(person *p, int gen);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    head = create_family(GEN);

    // Print family tree of blood types
    print_family(head, 0);

    // Free memory
    free_family(head);
    return 0;
}

// Create a new individual with `generations`
person *create_family(int gen)
{
    // TODO: Allocate memory for new person
    person *baby = (person *) malloc(sizeof(person));

    // If there are still generations left to create
    if (gen > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(gen - 1);
        person *parent1 = create_family(gen - 1);

        // TODO: Set parent pointers for current person
        baby->parents[0] = parent0;
        baby->parents[1] = parent1;

        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        baby->alleles[0] = parent0->alleles[rand() % 2];
        baby->alleles[1] = parent1->alleles[rand() % 2];
    }

    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL
        baby->parents[0] = NULL;
        baby->parents[1] = NULL;

        // TODO: Randomly assign alleles
        baby->alleles[0] = random_allele();
        baby->alleles[1] = random_allele();
    }

    // TODO: Return newly created person
    return baby;
}

// Free `head` and all ancestors of `head`.
void free_family(person *p)
{
    // TODO: Handle base case
    if (p == NULL)
        return;

    // TODO: Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int gen)
{

    // Handle base case
    if (p == NULL)
        return;

    // Print indentation
    for (int i = 0; i < gen * IL; i++)
    {
        printf(" ");
    }

    // Print person
    if (gen == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", gen, p->alleles[0], p->alleles[1]);
    }
    else if (gen == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", gen, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < gen - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", gen, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], gen + 1);
    print_family(p->parents[1], gen + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    switch (r)
    {
        case 1:
            return 'A';
        case 2:
            return 'B';
        default:
            return 'O';
    }
}
