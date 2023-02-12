#include <cs50.h>
#include <stdio.h>

/*
The power function, I opted to make one myself instead of using math library
This one accepts only positive powers, as negative ones are not needed.
*/
long power(long base, long exp);

int main(void)
{
    //Input the card no.
    long number, divisor_power = 1, sum1 = 0, sum2 = 0, type = 0;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1);
    //A loop that counts the number of digits will determine which sum loop to use to calculate the type
    long counter = 0, temp_to_count = number;
    do
    {
        temp_to_count = temp_to_count / 10;
        counter++;
    }
    while (temp_to_count > 0);

    //At this loop we keep on dividing to shrink the card no. and each two "shrinkages" we calculate digit1
    //Digit1 is the every other digit starting from the second-to-last digit
    //There is an if-loop that takes care of the value of digit 1 if twice digit1 is more than 9
    //(i.e: if "digit1*2" is 2 digits)
    //At the end of the iteration of the loop it adds the value of digit1 to the sum1 which has initial value of 0
    //sum1 is the main
    do
    {
        long digit1 = number / power(10, divisor_power) % 10 * 2;
        if (digit1 > 9)
        {
            digit1 = digit1 - 9;
        }
        //The counter is used to determine the type as below
        //Type is determined by the first 2 digits
        //Therefore by "Shrinking" the number to the last 2 digits we can determine the type of card
        //If the number of digits is odd, then we can use the sum1 loop, and if not then we use the sum2 loop
        if (counter % 2 == ! 0)
        {
            type = number / power(10, divisor_power);
        }
        sum1 = sum1 + digit1;
        divisor_power = divisor_power + 2;
    }
    while (number > power(10, divisor_power));
    //Now the program will start working on the second part of the checksum
    //Same idea as sum1, however the first iteration of divisor_power will have a value of 0
    //The numbers that will be calculated are digit2 which is every other number starting from the last number
    //Then sum2 which will be the sum of all the digits not added considered in the first half of the check sum
    divisor_power = 0;
    do
    {
        long digit2 = number / power(10, divisor_power) % 10;
        sum2 = sum2 + digit2;
        //The counter is used to determine the type as below
        //Type is determined by the first 2 digits
        //Therefore by "Shrinking" the number to the last 2 digits we can determine the type of card
        //If the number of digits is odd, then we can use the sum1 loop, and if not then we use the sum2 loop
        if (counter % 2 == 0)
        {
            type = number / power(10, divisor_power);
        }
        divisor_power = divisor_power + 2;
    }
    while (number > power(10, divisor_power));
    long checksum = (sum1 + sum2) % 10;
    //Now that the checksum is calculated, the program will determine whether the card is mathematically valid, and if it is; what is it's type
    if (checksum == 0)
    {
        //This is the second use of the digit counter, it is used alongside the "type" variable to determine the type of card
        //This is usefull because a card may mathematically add up to the correct sum however if it does not meet the issuer's criteria then it's still invalid
        if (counter == 15 && (type == 34 || type == 37))
        {
            printf("AMEX\n");
        }
        else if (counter == 16 && (type == 51 || type == 52 || type == 53 || type == 54 || type == 54 || type == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((counter == 13 || counter == 16) && (type >= 40 && type <= 49))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}

long power(long base, long exp)
{
    long answer = base;
    if (exp == 0)
    {
        answer = 1;
    }
    else
    {
        while (exp > 1)
        {
            answer = answer * base;
            exp--;
        }
    }
    return answer;
}