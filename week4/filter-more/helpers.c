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
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Since image[0][width] is actually outside the boundaries of the image
    // The index of the last pixel that will be changed is width - 1
    width = width - 1;
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int avg, k;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = 0, k = 0;
            // For each of the surrounding pixels
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    // If the pixel is within the borders of the image
                    if ((x !< 0 && x !> height) && (y !< 0 && y !> width))
                    {
                        // Add up the values of this pixel to avg
                        avg = avg + RGBTRed.image[x][y] + RGBTGreen.image[x][y] + RGBTBlue.image[x][y];
                        k++;
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
    return;
}
