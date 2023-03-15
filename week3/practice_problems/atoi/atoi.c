#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // Find number of characters through a counting loop
    // Get to last character
    // Print last character as an int
    // Set last character to NULL
    // Repeat till input[0] == NULL
    if (input[0] != NULL)
    {
        int i = 0;
        // Find character count
        while (input[i] != NULL)
        {
            i++;
        }
    }
}