#include "helpers.h"
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            int gx [3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
            int gy [3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
            int k1x, k2x, k3x = 0;
            int k1y, k2y, k3y = 0;
            float r1,r2,r3;

            for (int row = i-1; row < (i+2); row++)
            {
                for (int col = j-1; col < (j+2); col++)
                {
                    if ((row != -1) && (row != height) && (col != -1) && (col != width))
                    {
                        k1x = k1x + (image_copy[row][col].rgbtRed * gx[row-i+1][col-j+1]);
                        k1y = k1y + (image_copy[row][col].rgbtRed * gy[row-i+1][col-j+1]);

                        k2x = k2x + (image_copy[row][col].rgbtGreen * gx[row-i+1][col-j+1]);
                        k2y = k2y + (image_copy[row][col].rgbtGreen * gy[row-i+1][col-j+1]);

                        k3x = k3x + (image_copy[row][col].rgbtBlue * gx[row-i+1][col-j+1]);
                        k3y = k3y + (image_copy[row][col].rgbtBlue * gy[row-i+1][col-j+1]);
                    }
                }
            }
            r1 = round(pow((pow(k1x,2) + pow(k1y,2)), 0.5));
            r2 = round(pow((pow(k2x,2) + pow(k2y,2)), 0.5));
            r3 = round(pow((pow(k3x,2) + pow(k3y,2)), 0.5));

            image[i][j].rgbtRed = r1 < 255 ? r1 : 255;
            image[i][j].rgbtGreen = r2 < 255 ? r2 : 255;
            image[i][j].rgbtBlue = r3 < 255 ? r3 : 255;
        }
    }
    return;
}
