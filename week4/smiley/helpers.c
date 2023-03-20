#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtRED == 0x00 && image[i][j].rgbtGREEN == 0x00
                && image[i][j].rgbtBLUE == 0x00)
                {
                    image[i][j].rgbtBLUE == 0xff;
                }
        }
    }

}
