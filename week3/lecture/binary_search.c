//This code finds an element in a sorted array using binary search
//Binary Search means it splits the set in two and checks if the target is in the middle
//If it's not, it checks which side target and then discards the other side
//Then splits the side that has the target in two and repeat the previous process untill the target is in the middle
#include <cs50.h>
#include <stdio.h>

int main (void)
{
    //Array 'sub_a' is the sub array that will be used to store the the new data set
    int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}, loc, int sub_a{15};
    int target = get_string("Target: ");
    for (int i = 0; a[i] != '\0'; i++)
    {
        if (a[7] == target)
        {
            loc = (15+1) / 2;
            printf("Target Location: %i\n",loc);
            return 0;
        }
        else if (target < [7])
        {

        }
    }
}