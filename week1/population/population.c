#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start, end, n = 0;
    //Input start value
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    //Input end value
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    //Calculate years
    int temp = start;
    while (temp < end)
    {
        temp = temp + temp / 3 - temp / 4;
        n++;
    }

    //Print final result
    printf("Years: %i\n", n);
}
