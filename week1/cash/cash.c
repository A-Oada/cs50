#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();
    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;
    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

//This function will get the change owed, it makes sure that the change is between 1 and 99 cents inclusive
int get_cents(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);
    return cents;
}

//This will get the quarters, first we need to make sure that custmer is owed at least 1 quarter hence the if condition
//Then we make sure that cents are reduced to a number divisible by 25, hence the while loop
int calculate_quarters(int cents)
{
    int quarters = 0;
    if (cents >= 25)
    {
        while (cents % 25 == ! 0)
        {
            cents--;
        }
        quarters = cents / 25;
    }
    return quarters;
}

//Similarly to above function, first we check if there are any dimes owed, then reduce it so it's divisible by 10
int calculate_dimes(int cents)
{
    int dimes = 0;
    if (cents >= 10)
    {
        while (cents % 10 == ! 0)
        {
            cents--;
        }
        dimes = cents / 10;
    }
    return dimes;
}

//Same as dimes and quarters, this time we use 5 instead of 10 and 25, respectively
int calculate_nickels(int cents)
{
    int nickels = 0;
    if (cents >= 5)
    {
        while (cents % 5 == ! 0)
        {
            cents--;
        }
        nickels = cents / 5;
    }
    return nickels;
}

//At this point the remaining owed change are all pennies, so we only need to initialize and return the number of pennies
int calculate_pennies(int cents)
{
    int pennies = cents;
    return pennies;
}
