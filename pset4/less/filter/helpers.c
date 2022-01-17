#include "helpers.h"
#include <math.h>

//TODO

// Convert image to grayscale

int check_range(int n);


void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // i < the total amount of bytes in the bmp
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + 
                                  image[i][j].rgbtBlue) / 3.0);

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // i < the total amount of bytes in the bmp
    {
        for (int j = 0; j < width; j++)
        {
            int newRed;
            int newGreen;
            int newBlue;

            newRed = round(.393 * image[i][j].rgbtRed  + .769 * image[i][j].rgbtGreen  + .189 * image[i][j].rgbtBlue);
            newGreen = round(.349 * image[i][j].rgbtRed  + .686 * image[i][j].rgbtGreen  + .168 * image[i][j].rgbtBlue);
            newBlue = round(.272 * image[i][j].rgbtRed  + .534 * image[i][j].rgbtGreen  + .131 * image[i][j].rgbtBlue);

            newRed = check_range(newRed);
            newGreen = check_range(newGreen);
            newBlue = check_range(newBlue);

            image[i][j].rgbtRed = newRed;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtBlue = newBlue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor(0.5 * width); j++)
        {
            int k = width - 1 - j;
            buffer = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float avgRed[height][width];
    float avgGreen[height][width];
    float avgBlue[height][width];
    float avgCount[height][width];
    
    RGBTRIPLE buffer[height][width];  
    
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            buffer[x][y] = image[x][y];
            avgRed[x][y] = avgGreen[x][y] = avgBlue[x][y] = avgCount[x][y] = 0;
        }
    }
    

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < height; k++)
            {
                for (int l = 0; l < width; l++)
                {
                    if (i - 1 <= k && k <= i + 1 && j - 1 <= l && l <= j + 1)
                    {
                        
                        
                        avgCount[i][j]++; 
                        avgRed[i][j] += buffer[k][l].rgbtRed; 
                        avgGreen[i][j] += buffer[k][l].rgbtGreen;
                        avgBlue[i][j] += buffer[k][l].rgbtBlue; 
                         
                        image[i][j].rgbtRed = round(avgRed[i][j] / avgCount[i][j]); 
                        image[i][j].rgbtGreen = round(avgGreen[i][j] / avgCount[i][j]);
                        image[i][j].rgbtBlue = round(avgBlue[i][j] / avgCount[i][j]); 
                    }
                    
            
                    
                
                }
            }
        }
    }
    return;
}

int check_range(int n)
{
    if (n > 255)
    {
        n = 255;
    }
       

    return n;
}
