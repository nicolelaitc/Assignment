#include <cs50.h>
#include <stdio.h>
#include <string.h>

void Collatz (int n); 

int count = 0; 

int main (void)
{
    int n = get_int("Number: "); 
    Collatz(n); 
    printf("Step: %i\n", count); 
    
}

void Collatz (int n)
{
    
    if (n == 1)
        return 0; 
    
    else if (n % 2 == 0)
    {
        n = n / 2; 
        count++; 
        Collatz (n); 
    }
    
    else if (n % 2 == 1)
    {
        n  = 3*n + 1; 
        count++; 
        Collatz (n); 
    }
    
    else
    {
        return; 
    }
    
    
}