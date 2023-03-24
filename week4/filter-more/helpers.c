#include "helpers.h"
#include <math.h>

// Convert image to grayscale.
// For each pixel, turn it into grayscale.
// Grayscale is calculated by approximating the average of all
// colors in a pixel and rounding that number
// Values of r, g and b are cast into floats to accurately round the numbers
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float gray;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gray = round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtBlue)/3);
            image[i][j].rgbtRed = (int)gray;
            image[i][j].rgbtGreen = (int)gray;
            image[i][j].rgbtBlue = (int)gray;
        }
    }
    return;
}

// Reflect image horizontally
// To reflect the image; copy the value of the first pixel to the last, second to second-to-last... etc
// At the midpoint the image will have two identical halves, therefore store the original 1st half in an array
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE half[height][width/2];
    // Copy 1st half of image into an array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            half[i][j].rgbtRed = image[i][j].rgbtRed;
            half[i][j].rgbtGreen = image[i][j].rgbtGreen;
            half[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // Copy right half of image into left half
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            image[i][j].rgbtRed = image[i][width - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j].rgbtBlue;
        }
    }

    // Copy left half of image onto the right from the stored array
    // Image will be copied in og orientation and needs to be reversed
    for (int i = 0; i < height; i++)
    {
        int half_width = 0;
        for (int j = width/2; j < width; j++)
        {
            image[i][j].rgbtRed = half[i][half_width].rgbtRed;
            image[i][j].rgbtGreen = half[i][half_width].rgbtGreen;
            image[i][j].rgbtBlue = half[i][half_width].rgbtBlue;
            half_width++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
