#include <stdio.h>
#include <cs50.h>

bool valid_triangle(float side1, float side2, float side3);

int main(void)
{
    float s1 = get_float("Please enter side 1: \n");
    float s2 = get_float("Please enter side 2: \n");
    float s3 = get_float("Please enter side 3: \n");
    if (valid_triangle(s1, s2, s3) == true)
    {
        printf("True\n");
        return 0;
    }
    else
    {
        printf("false\n");
        return 0;
    }
}

bool valid_triangle(float side1, float side2, float side3)
{
    if (side1 <= 0 || side2 <= 0 || side3 <= 0)
    {
        return false;
    }
    if (side1 + side2 <= side1 || side1 + side3 <= side2 || side2 + side3 <= side1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
