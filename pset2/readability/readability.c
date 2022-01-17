#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(void)
{
    string text = get_string("text: ");

    int L = 0;

    for (int i = 0, m = strlen(text); i < m; i++) //counter +1 if it detects letters
    {
        if (isalpha(text[i]))
        {
            L = L + 1;
        }
    }

    printf("%i\n", L);

    int S = 0;

    for (int j = 0, n = strlen(text); j < n; j++) 
    {
        if ((text[j]) == 33 || (text[j]) == 46 || (text[j]) == 63)

        {
            S = S + 1;
        }
    }

    printf("%i\n", S);
    int W = 1;
    for (int k = 0, p = strlen(text); k < p; k++)
    {
        if (isspace(text[k]))

        {
            W = W + 1;
        }
    }

    printf("%i\n", W);

    int grade = round(0.0588 * L * 100 / W - 0.296 * S * 100 / W - 15.8);

    if (grade < 1)  //print the result
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}




