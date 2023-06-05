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
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Number of words in dictionary
unsigned int word_count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to a number
    unsigned int h = hash(word);

    // Create traversal pointer
    node *trav = table[h];

    // Check each dictionary node for the word
    while(trav != NULL)
    {
        if (strcasecmp(word, trav->word) != 0)
        {
            trav = trav->next;
        }
            else
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Adds up all ASCII values of word, returning hash modded by size of hash table
    int sum = 0;
    for (int j = 0; word[j] != '\0'; j++)
    {
        sum += toupper(word[j]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file != NULL)
    {
        // Read strings from dictionary file one at a time
        char buffer[LENGTH + 1];
        while (fscanf(file, "%s", buffer) != EOF)
        {
            // Create new node for each word
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                free(n);
                return false;
            }
            // Copy dictionary word to node
            strcpy(n->word, buffer);
            // Set next pointer to NULL
            n->next = NULL;

            // Hash word to a hash value
            unsigned int h = hash(n->word);

            // Insert node into hash table at that location given by hash function
            n->next = table[h];
            table[h] = n;

            // Update dictionary word count
            word_count++;
        }
        fclose(file);
        return true;
    }
    fclose(file);
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count == 0)
        return 0;
    else
        return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through buckets in hash table
    for(int i = 0; i < N; i++)
    {
        // If a bucket is empty return to loop
        if (table[i] != NULL)
        {
            // Create traversal pointer to point to first node in linked list
            node *trav = table[i];
            // Create traversal pointer to also point to first node in linked list
            node *tmp = trav;

            // Free all nodes in linked list
            while(trav != NULL)
            {
                // Point traversal to the next node in the linked list
                trav = trav->next;
                // Free first node
                free(tmp);
                // Point tmp to the next node in the linked list
                tmp = trav;
            }

            // Check if there was an error during memory deallocation
            if (trav != NULL)
            {
                return false;
            }
        }
    }
    return true;
}
