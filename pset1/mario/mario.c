#include <stdio.h>
#include <cs50.h>

int main(void)
{ 
    // Get n = 1-8 
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    
    // Print out that many hashtag
    int i = 1;
    
    while (i <= n) //create another line of hashtag if i < n
    {   
        for (int k = n - i; k > 0; k--) //making the left-hand side of the pyramid right-aligned 
        
        {
            printf(" "); 
        }
        
        for (int j = 0; j < i; j++) //print #

        { 
            printf("#");
        }
        
        printf("  "); //the space in between
        
        for (int j = 0; j < i; j++)

        { 
            printf("#");
        }
        
        printf("\n"); //be careful where to put this line; will affect where to start a new line
        i++;
        
    }
}
