#include <cs50.h>
#include <stdio.h>
#include <math.h>

int get_x(void)
{
    int x;
    do
    {
        x = get_int("start size:");
    }
    while (x < 9);
    return x;
//TODO: Prompt for start size (check lecture video for this code )
}

int get_y(int x)
{

    int y;
    do
    {
        y = get_int("end size:");
    }
    while (y < x);
    return y;    // TODO: Prompt for end size
}

int main(void)
{
    int x = get_x();
    int y = get_y(x);
    
    int i = 0;

    while (x < y)
    {
        x = x + floor(x / 3.0) - floor(x / 4.0);
        i = i + 1;
    }
     
    // TODO: Calculate number of years until we reach threshold
    
    printf("Years: %i\n", i);   // TODO: Print number of years
    
}