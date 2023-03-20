#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel in width and each pixel in height
    // If the pixel is white (i.e: lacks all colors)
    // Turn this pixel to another color
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00
                && image[i][j].rgbtBlue == 0x00)
            {
                image[i][j].rgbtBlue = 0xff;
            }
        }
    }

}