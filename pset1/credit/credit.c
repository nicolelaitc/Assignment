#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{
    long c = get_long("Number:"); //get the credit card number
    int d = floor(c / 1000000000000);  //for VISA 13-digit
    int e = floor(c / 10000000000000); //for AMEX 15-digit
    int f = floor(c / 100000000000000); //for master 16-digit
    int g = floor(c / 1000000000000000); //for VISA 16-digit
    
    long a = c;
    long b = c;
    int i = 0;
    int j = 0;
    
    while (a > 1)
    {
        i = i + a % 10; 
        a = (a - a % 10 - 10 * (a / 10 % 10)) / 100; 
    } 
     
    while (b > 10)
    {
        j = j + (2 * (b / 10 % 10) % 10) + ((2 * (b / 10 % 10) / 10) % 10) ;     //need to think how to get the product digit for number more than 10
        b = (b - b % 10 - 10 * (b / 10 % 10)) / 100;  
        
    }

    
    
    if ((i + j) % 10 == 0)
    {
        if (e == 34 || e == 37)
        {
            printf("AMEX\n");
        }
    
        else if (!(f < 50) && !(f > 55))
        {
            printf("MASTERCARD\n");
        }
    
        else if (d == 4)
        {
            printf("VISA\n");
        }
    
        else if (g == 4)
        {
            printf("VISA\n");
        }
        else 
        {
            printf("INVALID\n");
        }
    }
   
    else 
    {
        printf("INVALID\n");
    }
}



//count if the number have 16 digits, otherwise invalid
//calculate if the nuber is valid
//determine if it is VISA, Master or AMEX, can use floor(c/10^15)
//print the result