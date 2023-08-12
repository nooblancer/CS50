#include "helpers.h"
#include <math.h>
#include <stdio.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    // Initialise Sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {

            // Initialise ints
            float x_r = 0;
            float x_g = 0;
            float x_b = 0;
            float y_r = 0;
            float y_g = 0;
            float y_b = 0;

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
                    x_r += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    x_g += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    x_b += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    y_r += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    y_g += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    y_b += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }
            // Calculate Sobel operator
            int red = round(sqrt((x_r * x_r) + (y_r * y_r)));
            int green = round(sqrt((x_g * x_g) + (y_g * y_g)));
            int blue = round(sqrt((x_b * x_b) + (y_b * y_b)));
            // Cap at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            // Assign new values to pixels
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}