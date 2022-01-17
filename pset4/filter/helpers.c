#include "helpers.h"
#include <math.h>

float edge_calculation(int height, int width, float buffer[height][width], int i, int j); 


// Convert image to grayscale
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float bufferRed[height][width]; 
    float bufferGreen[height][width]; 
    float bufferBlue[height][width]; 
    
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            bufferRed[x][y] = image[x][y].rgbtRed; 
            bufferGreen[x][y] = image[x][y].rgbtGreen; 
            bufferBlue[x][y] = image[x][y].rgbtBlue; 
            
        }
    }
    
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtRed = edge_calculation(height, width, bufferRed, a, b); 
            image[a][b].rgbtBlue = edge_calculation(height, width, bufferBlue, a, b); 
            image[a][b].rgbtGreen = edge_calculation(height, width, bufferGreen, a, b); 
            
        }
    }

}

float edge_calculation(int height, int width, float buffer[height][width], int i, int j)
{
    float Gx = 0, Gy = 0, result = 0; 
    
    if (i - 1 >= 0)
    {
        Gy = Gy - (2 * buffer[i - 1][j]); 
        if (j - 1 >= 0)
        {
            Gx = Gx - buffer[i - 1][j - 1]; 
            Gy = Gy - buffer[i - 1][j - 1]; 
        }
        
        if (j + 1 < width)
        {
            Gx = Gx + buffer[i - 1][j + 1]; 
            Gy = Gy - buffer[i - 1][j + 1]; 
            
        }
    }
    
    if (i + 1 < height)
    {
        Gy = Gy + (2 * buffer[i + 1][j]);  
        if (j - 1 >= 0)
        {
            Gx = Gx - buffer[i + 1][j - 1]; 
            Gy = Gy + buffer[i + 1][j - 1]; 
        }
        
        if (j + 1 < width)
        {
            Gx = Gx + buffer[i + 1][j + 1]; 
            Gy = Gy + buffer[i + 1][j + 1]; 
        }
        
    }
    
    if (j - 1 >= 0)
    {
        Gx = Gx - 2 * buffer[i][j - 1]; 
    }
    
    if (j + 1 < width)
    {
        Gx = Gx + 2 * buffer[i][j + 1]; 
    }
    
    result = round(sqrt(Gx * Gx + Gy * Gy)); 
    
    if (result > 255)
    {
        return 255; 
    }
    
    else 
    {
        return result; 
    }
    
}


