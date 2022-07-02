#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float k;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            k = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = round(k);
            image[i][j].rgbtGreen = round(k);
            image[i][j].rgbtRed = round(k);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int k1 = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            k1 = k1 < 255 ? k1 : 255;

            int k2 = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            k2 = k2 < 255 ? k2 : 255;

            int k3 = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));
            k3 = k3 < 255 ? k3 : 255;

            image[i][j].rgbtRed = k1;
            image[i][j].rgbtGreen = k2;
            image[i][j].rgbtBlue = k3;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i == 0) && (j == 0))
            {
                image[i][j].rgbtRed = round((image_copy[i+1][j].rgbtRed + image_copy[i][j+1].rgbtRed + image_copy[i+1][j+1].rgbtRed + image_copy[i][j].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((image_copy[i+1][j].rgbtGreen + image_copy[i][j+1].rgbtGreen + image_copy[i+1][j+1].rgbtGreen + image_copy[i][j].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((image_copy[i+1][j].rgbtBlue + image_copy[i][j+1].rgbtBlue + image_copy[i+1][j+1].rgbtBlue + image_copy[i][j].rgbtBlue) / 4.0);
            }
            else if ((i == 0) && (j == (width - 1)))
            {
                image[i][j].rgbtRed = round((image_copy[i][j-1].rgbtRed + image_copy[i+1][j].rgbtRed + image_copy[i+1][j-1].rgbtRed + image_copy[i][j].rgbtRed)/4.0);
                image[i][j].rgbtGreen = round((image_copy[i][j-1].rgbtGreen + image_copy[i+1][j].rgbtGreen + image_copy[i+1][j-1].rgbtGreen + image_copy[i][j].rgbtGreen)/4.0);
                image[i][j].rgbtBlue = round((image_copy[i][j-1].rgbtBlue + image_copy[i+1][j].rgbtBlue + image_copy[i+1][j-1].rgbtBlue + image_copy[i][j].rgbtBlue)/4.0);
            }
            else if ((i == (height - 1)) && (j == 0))
            {
                image[i][j].rgbtRed = round((image_copy[i-1][j].rgbtRed + image_copy[i][j+1].rgbtRed + image_copy[i-1][j+1].rgbtRed + image_copy[i][j].rgbtRed)/4.0);
                image[i][j].rgbtGreen = round((image_copy[i-1][j].rgbtGreen + image_copy[i][j+1].rgbtGreen + image_copy[i-1][j+1].rgbtGreen + image_copy[i][j].rgbtGreen)/4.0);
                image[i][j].rgbtBlue = round((image_copy[i-1][j].rgbtBlue + image_copy[i][j+1].rgbtBlue + image_copy[i-1][j+1].rgbtBlue + image_copy[i][j].rgbtBlue)/4.0);
            }

            else if ((i == (height - 1)) && (j == (width - 1)))
            {
                image[i][j].rgbtRed = round((image_copy[i][j-1].rgbtRed + image_copy[i-1][j].rgbtRed + image_copy[i-1][j-1].rgbtRed + image_copy[i][j].rgbtRed)/4.0);
                image[i][j].rgbtGreen = round((image_copy[i][j-1].rgbtGreen + image_copy[i-1][j].rgbtGreen + image_copy[i-1][j-1].rgbtGreen + image_copy[i][j].rgbtGreen)/4.0);
                image[i][j].rgbtBlue = round((image_copy[i][j-1].rgbtBlue + image_copy[i-1][j].rgbtBlue + image_copy[i-1][j-1].rgbtBlue + image_copy[i][j].rgbtBlue)/4.0);
            }

            else if (j == 0)
            {
                image[i][j].rgbtRed = round((image_copy[i-1][j].rgbtRed + image_copy[i+1][j].rgbtRed + image_copy[i-1][j+1].rgbtRed + image_copy[i+1][j+1].rgbtRed + image_copy[i][j+1].rgbtRed + image_copy[i][j].rgbtRed)/6.0);
                image[i][j].rgbtGreen = round((image_copy[i-1][j].rgbtGreen + image_copy[i+1][j].rgbtGreen + image_copy[i-1][j+1].rgbtGreen + image_copy[i+1][j+1].rgbtGreen + image_copy[i][j+1].rgbtGreen + image_copy[i][j].rgbtGreen)/6.0);
                image[i][j].rgbtBlue = round((image_copy[i-1][j].rgbtBlue + image_copy[i+1][j].rgbtBlue + image_copy[i-1][j+1].rgbtBlue + image_copy[i+1][j+1].rgbtBlue + image_copy[i][j+1].rgbtBlue + image_copy[i][j].rgbtBlue)/6.0);
            }

            else if (j == (width - 1))
            {
                image[i][j].rgbtRed = round((image_copy[i-1][j].rgbtRed + image_copy[i+1][j].rgbtRed + image_copy[i-1][j-1].rgbtRed + image_copy[i+1][j-1].rgbtRed + image_copy[i][j-1].rgbtRed + image_copy[i][j].rgbtRed)/6.0);
                image[i][j].rgbtGreen = round((image_copy[i-1][j].rgbtGreen + image_copy[i+1][j].rgbtGreen + image_copy[i-1][j-1].rgbtGreen + image_copy[i+1][j-1].rgbtGreen + image_copy[i][j-1].rgbtGreen + image_copy[i][j].rgbtGreen)/6.0);
                image[i][j].rgbtBlue = round((image_copy[i-1][j].rgbtBlue + image_copy[i+1][j].rgbtBlue + image_copy[i-1][j-1].rgbtBlue + image_copy[i+1][j-1].rgbtBlue + image_copy[i][j-1].rgbtBlue + image_copy[i][j].rgbtBlue)/6.0);
            }

            else if (i == 0)
            {
                image[i][j].rgbtRed = round((image_copy[i][j-1].rgbtRed + image_copy[i][j+1].rgbtRed + image_copy[i+1][j-1].rgbtRed + image_copy[i+1][j+1].rgbtRed + image_copy[i+1][j].rgbtRed + image_copy[i][j].rgbtRed)/6.0);
                image[i][j].rgbtGreen = round((image_copy[i][j-1].rgbtGreen + image_copy[i][j+1].rgbtGreen + image_copy[i+1][j-1].rgbtGreen + image_copy[i+1][j+1].rgbtGreen + image_copy[i+1][j].rgbtGreen + image_copy[i][j].rgbtGreen)/6.0);
                image[i][j].rgbtBlue = round((image_copy[i][j-1].rgbtBlue + image_copy[i][j+1].rgbtBlue + image_copy[i+1][j-1].rgbtBlue + image_copy[i+1][j+1].rgbtBlue + image_copy[i+1][j].rgbtBlue + image_copy[i][j].rgbtBlue)/6.0);
            }

            else if (i == (height - 1))
            {
                image[i][j].rgbtRed = round((image_copy[i][j-1].rgbtRed + image_copy[i][j+1].rgbtRed + image_copy[i-1][j-1].rgbtRed + image_copy[i-1][j+1].rgbtRed + image_copy[i-1][j].rgbtRed + image_copy[i][j].rgbtRed)/6.0);
                image[i][j].rgbtGreen = round((image_copy[i][j-1].rgbtGreen + image_copy[i][j+1].rgbtGreen + image_copy[i-1][j-1].rgbtGreen + image_copy[i-1][j+1].rgbtGreen + image_copy[i-1][j].rgbtGreen + image_copy[i][j].rgbtGreen)/6.0);
                image[i][j].rgbtBlue = round((image_copy[i][j-1].rgbtBlue + image_copy[i][j+1].rgbtBlue + image_copy[i-1][j-1].rgbtBlue + image_copy[i-1][j+1].rgbtBlue + image_copy[i-1][j].rgbtBlue + image_copy[i][j].rgbtBlue)/6.0);
            }

            else
            {
                image[i][j].rgbtRed = round((image_copy[i-1][j].rgbtRed + image_copy[i+1][j].rgbtRed + image_copy[i][j+1].rgbtRed + image_copy[i][j-1].rgbtRed + image_copy[i-1][j+1].rgbtRed + image_copy[i-1][j-1].rgbtRed + image_copy[i+1][j+1].rgbtRed + image_copy[i+1][j-1].rgbtRed + image_copy[i][j].rgbtRed)/9.0);
                image[i][j].rgbtGreen = round((image_copy[i-1][j].rgbtGreen + image_copy[i+1][j].rgbtGreen + image_copy[i][j+1].rgbtGreen + image_copy[i][j-1].rgbtGreen + image_copy[i-1][j+1].rgbtGreen + image_copy[i-1][j-1].rgbtGreen + image_copy[i+1][j+1].rgbtGreen + image_copy[i+1][j-1].rgbtGreen + image_copy[i][j].rgbtGreen)/9.0);
                image[i][j].rgbtBlue = round((image_copy[i-1][j].rgbtBlue + image_copy[i+1][j].rgbtBlue + image_copy[i][j+1].rgbtBlue + image_copy[i][j-1].rgbtBlue + image_copy[i-1][j+1].rgbtBlue + image_copy[i-1][j-1].rgbtBlue + image_copy[i+1][j+1].rgbtBlue + image_copy[i+1][j-1].rgbtBlue + image_copy[i][j].rgbtBlue)/9.0);
            }
        }
    }
    return;
}