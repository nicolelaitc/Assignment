// Implements a dictionary's functionality
//reference: https://benhoyt.com/writings/hash-table-in-c/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table (need to change it by myself)
const unsigned int N = 4527; //strlen + first alphabet

// Hash table
node *table[N];

//counting size
int word_in_dict; 

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //hash word to obtain a hash value
    char hash[strlen(word)];  
    strcpy(hash, word); 
    
    char check[45]; 
   
    int first_alphabet = tolower(hash[0]) - 97; 
   
    int hash_value = (strlen(hash) * 100 + first_alphabet); 
    //access the linked list 
    for (node *tmp = table[hash_value]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true; 
            break; 
        }
    }
    //traverse linked list, looking for the word (strcasecmp)
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //input(character) -> output(number)
    //can use hash function found online
    
    char hash[strlen(word)];  
    strcpy(hash, word); 
   
    int first_alphabet = tolower(hash[0]) - 97; 
   
    return (strlen(hash) * 100 + first_alphabet); 
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    word_in_dict = 0; 
    
    //open the dictionary file
    FILE *dict = fopen(dictionary, "r"); 
   
    //remember to check NULL -> return 1
    if (dict == NULL)
    {
        return false; 
    }
    
    //create buffer to deal with the read text
    char vocab[45];  
    
    while (fscanf(dict, "%s", vocab) && feof(dict) == 0)//read string from file one at a time
    {
        //create a new node for each word
        node *n = malloc(sizeof(node));

        //rmb to check if no memory
        if (n == NULL)
        {
            return false; 
            word_in_dict = 0; 
        }
        //use strcpy to copy string 
        strcpy(n->word, vocab); 
        //hash word to obtain the hash value    
        int hash_value = hash(n->word); 
    
        //insert node into that location
        n->next = table[hash_value]; 
        table[hash_value] = n; 
        word_in_dict++; 
        //return false if not enough memory

    }
    
    fclose(dict); 
    
    return true; 

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_in_dict; 
    
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int a = 0; a < N; a++)
    {
        while (table[a] != NULL)
        {
            node *tmp = table[a]->next;
            free(table[a]);
            table[a] = tmp;
        }
    
    }
    //ensure to free a used thing, but not losing the link 
    return true; 
}
