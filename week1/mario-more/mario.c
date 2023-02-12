#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Take input then make sure it fits parameters using while loop
    int height;
    do
    {
        height = get_int("Height of your pyramid: ");
    }
    while (height < 1 || height > 8);
    //The row number is definded here, because the initial value of height must not change as it will be used later on
    //It is used later on to determine the number of hashes and spaces
    int row_number = height;
    //Main loop, prints spaces, then hashes, then new line
    while (row_number > 0)
    {
        int spaces = row_number - 1;
        //First loop, used to determine number of spaces
        while (spaces > 0)
        {
            printf(" ");
            spaces--;
        }
        //This is why row_number was declared above, because height will be used here, and we need it to have the same value
        //in each iteration of the loop, because as row_number decreases, hashes number will increase therefore they cannot be connected with on another
        int hashes = height;
        //This loop prints hashes, it is determined by the original height
        while (hashes >= row_number)
        {
            printf("#");
            hashes--;
        }
        //We now need to print the 2 spaces between each set of hashes, these are constant so they will repeat with every iteration of the main loop
        printf("  ");
        //After both the first set of hashes and spaces are printed, we need a new loop similar to the original hashes one
        //First we need to reset the number of rows to the original row we're at
        hashes = height;
        while (hashes >= row_number)
        {
            printf("#");
            hashes--;
        }
        printf("\n");
        row_number--;
    }
}