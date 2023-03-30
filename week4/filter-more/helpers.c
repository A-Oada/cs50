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
    // Creat a copy of image to prevent the updated values from affecting other pixels
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    int avgred, avggreen, avgblue, k;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avgred = 0, avggreen = 0, avgblue = 0, k = 0;
            // For each of the surrounding pixels
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    // If the pixel is within the borders of the image
                    if ((!(x < 0) && !(x >= height)) && (!(y < 0) && !(y >= width)))
                    {
                        // Add up the values of this pixel to avg
                        avgred = avgred + image[x][y].rgbtRed;
                        avggreen = avggreen + image[x][y].rgbtGreen;
                        avgblue = avgblue + image[x][y].rgbtBlue;
                        k++;
                    }
                }
            }

            // Caclulate average values of RGB in pixel
            avgred = round(((float)avgred / k));
            avggreen = round(((float)avggreen / k));
            avgblue = round(((float)avgblue / k));

            // Assign new values to the pixel
            copy[i][j].rgbtRed = avgred;
            copy[i][j].rgbtGreen = avggreen;
            copy[i][j].rgbtBlue = avgblue;
        }
    }

    // Assign copy to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy of original image to prevent each pixel from affecting the kernels
    RGBTRIPLE copy[height][width], Gx, Gy;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Make the edges of the image black
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || j == 0)
            {
                copy[i][j].rgbtRed = 0;
                copy[i][j].rgbtGreen = 0;
                copy[i][j].rgbtBlue = 0;
            }
        }
    }

    int Gxred, Gxgreen, Gxblue, k, l;
    // For each pixel within the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate Gx values for each color from surrounding pixels
            Gxred = 0; Gxgreen = 0; Gxblue = 0, k = -1, l = - 2;
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; j++)
                {
                    // If the surrounding pixel is within the image and not in middle column of surrounding pixels
                    if ((!(x < 0) && !(x >= height)) && (!(y < 0) && !(y >= width) && (y != j)))
                    {
                        // Rows 1 and 3 in an image are multiplied by -1 and 1 for Column 1 and 3 respectively
                        if (x != i)
                        {
                            Gxred = Gxred + image[x][y].rgbtRed * k;
                            Gxgreen = Gxgreen + image[x][y].rgbtGreen * k;
                            Gxblue = Gxblue + image[x][y].rgbtBlue * k;
                            k *= -1;
                        }
                        // Row 2 is multiplied by -2 and 2 for columns 1 and 3 respectively
                        else
                        {
                            Gxred = Gxred + image[x][y].rgbtRed * l;
                            Gxgreen = Gxgreen + image[x][y].rgbtRed * l;
                            Gxblue = Gxblue + image[x][y].rgbtBlue * l;
                            l *= -2;
                        }
                    }
                }
            }

            // Square value of Gx for each colour
            Gxred = Gxred * Gxred;
            Gxgreen = Gxgreen * Gxgreen;
            Gxblue = Gxblue * Gxblue;
        }
    }
    return;
}
