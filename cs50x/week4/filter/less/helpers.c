#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j].rgbtRed + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][j].rgbtGreen;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // Initialise values
            float r = 0;
            float g = 0;
            float b = 0;

            r = round(0.393 * temp[i][j].rgbtRed + 0.769 * temp[i][j].rgbtGreen + 0.189 * temp[i][j].rgbtBlue);
            g = round(0.349 * temp[i][j].rgbtRed + 0.686 * temp[i][j].rgbtGreen + 0.168 * temp[i][j].rgbtBlue);
            b = round(0.272 * temp[i][j].rgbtRed + 0.534 * temp[i][j].rgbtGreen + 0.131 * temp[i][j].rgbtBlue);

            if (r > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = r;
            }
            if (g > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = g;
            }
            if (b > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = b;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // Initialise values
            float r = 0;
            float g = 0;
            float b = 0;
            int t = 0;

            // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    r += temp[i + k][j + l].rgbtRed;
                    g += temp[i + k][j + l].rgbtGreen;
                    b += temp[i + k][j + l].rgbtBlue;
                    t++;
                }
            }
            // Get average and blur image
            image[i][j].rgbtRed = round(r / t);
            image[i][j].rgbtGreen = round(g / t);
            image[i][j].rgbtBlue = round(b / t);
        }
    }
    return;
}
