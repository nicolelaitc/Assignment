#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float x; 
    do
    {
        x = get_float("Change owed: ");
    }
    while (x < 0);
    
    int y = round(x * 100);
    int i = 0;
    
    while (y >= 25)
    { 
        y = y - 25; 
        i = i + 1;
    }
    
    while (y >= 10)
    { 
        y = y - 10;
        i = i + 1;
        
    }
    
    while (y >= 5)
    { 
        y = y - 5; 
        i = i + 1;
        
    }
    
    while (y >= 1)
    { 
        y = y - 1;
        i = i + 1;
    }
    
    printf("%i\n", i);
    
}