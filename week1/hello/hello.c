#include <stdio.h>
#include <cs50.h>

// This prints the name of someone, adding the comment to get the styles50 thing right
int main(void)
{
    string name = get_string("What's your name? ");
    printf("Hello, %s\n", name);

}