#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2) //check if the key only 1-line
    {
        printf("Your key should only consists of one line.\n");
        return 1;
    }
    
    char *key = argv[1];
    
    if (strlen(key) != 26)//check if the key is 26 character long
    {
        printf("Your key should consist of 26 alphabets.\n");
        return 1;
    }
    
    
    for (int i = 0; i < 26; i++) //check if it contains any non-alphatical character
    {
        if (!isalpha(key[i]))
        {
            printf("Your key should consist of alphabet only.\n");
            return 1;
        }
    }
    
    for (int d = 0; d < 26; d++)
    {
        for (int e = 0; e < 26; e++)
        {
            if (key[d] == key[e] && d != e)
            {
                printf("Your key should not have any duplicate character.\n");
                return 1;
            }
        }
    }
    
     
    string text = get_string("plaintext: ");
    
    char upperkey[26]; 
    char lowerkey[26];
    
    for (int j = 0; j < 26; j++) //create the string for upper letter
    {
        upperkey[j] = toupper(key[j]);
    }
    
    for (int k = 0; k < 26; k++) //create the string for lower letter 
    {
        lowerkey[k] = tolower(key[k]);
    }
    

    printf("ciphertext: ");
    
    for (int l = 0, p = strlen(text); l < p; l++)//use if-loop to solve each letter is upper or lowercase
    {
        if (islower(text[l]))
        {
            int x = text[l] - 97;
            printf("%c", lowerkey[x]);
        }
        else if (isupper(text[l]))
        {
            int y = text[l] - 65;
            printf("%c", upperkey[y]);
        }
        else 
        {
            printf("%c", text[l]);
        }
    }
    
    printf("\n");
}

