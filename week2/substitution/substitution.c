#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool is_key_alpha(string key);
bool is_key_norepeat(string key);
bool is_key_valid(string key);
char rotate_letter(char input_c, string key, string alpha_type);
char rotate(char input_c, string key);
char change_key_case(char key, char input);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution <<key>>\n");
        return 1;
    }
    string key = argv[1];
    if (is_key_valid(key) != true)
    {
        printf("Key must be 26 non-repeated alphabetical charachters\n");
        return 1;
    }
    string input_text = get_string("Plaintext:  ");
    string cipher = input_text;
    for (int i = 0; i <= strlen(input_text); i++)
    {
        cipher[i] = rotate(input_text[i], key);
    }
    printf("ciphertext: %s\n", cipher);
}

//Function to determine if the key string consists of alphabetical charachers only
bool is_key_alpha(string key)
{
    for (int i = 0; i <= 25; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

//Function to determine whether each letter is repeated more than once by comparing each letter to all other letters in key except itself
bool is_key_norepeat(string key)
{
    //key[i] is the char that all the other keys will be compared to
    for (int i = 0; i <= 25; i++)
    {
        //key[j] is the char that we are comparing key[i] to
        for (int j = 0; j <= 25; j++)
        {
            //If we are comparing the same letter to itself then naturally they key[i] will be equal to key[j] we should ignore this iteration of the loop hence the continue statement
            //The continue statemant only takes effect for the 'j' loop but not the 'i' loop
            if (j == i)
            {
                continue;
            }
            //If the we are comparing any chars in different locations (i & j) then this means a char is repeated therefore the function returns false
            else if (key[i] == key[j])
            {
                return false;
            }
        }
    }
    return true;
}

//Function combining "is_key_nonrepeat" and is_key_alpha into one to make main easier to read
bool is_key_valid(string key)
{
    if (is_key_norepeat(key) != true || is_key_alpha(key) != true)
    {
        return false;
    }
    return true;
}

//Apply key to lower or upper case characters
char rotate_letter(char input_c, string key, string alpha_type)
{
    char cipher;
    for (int i = 0; i <= 25; i++)
    {
        //Determine the position of the letter in the text in the lower_alphabet
        //The ciphered letter is key [location in alphabet] as the key is basically the encryptor's own version of alphabet
        if (input_c == alpha_type[i])
        {
            key[i] = change_key_case(key[i], input_c);
            cipher = key[i];
        }
    }
    return cipher;
}

//Final rotation, merge rotate_letter with another condition that would not change non-alphabetical characters
char rotate(char input_c, string key)
{
    char cipher, upper_alpha[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", lower_alpha[26] = "abcdefghijklmnopqrstuvwxyz";
    //If the input letter is lower case
    if (islower(input_c))
    {
        for (int i = 0; i <= 25; i++)
        {
            key[i] = change_key_case(key[i], input_c);
        }
        cipher = rotate_letter(input_c, key, lower_alpha);
    }
    //If the input letter is upper case
    else if (isupper(input_c))
    {
        for (int i = 0; i <= 25; i++)
        {
            key[i] = change_key_case(key[i], input_c);
        }
        cipher = rotate_letter(input_c, key, upper_alpha);
    }
    //If the input character is not in the alphabet (i.e: commas, question marks, dots...)
    else
    {
        cipher = input_c;
    }
    return cipher;
}

//To be able to preserve the case of the input text, make sure all letters in key have the same case as the input text
char change_key_case(char key, char input)
{
    //If the input is uppercase, make sure the key is uppercase
    //At this stage the key is valid so no need to include all possibilities for the key, (i.e: only check if the value of the key in ASCII is more than Z)
    if (isupper(input) && key > 90)
    {
        key = key - 32;
    }
    //If the input is lowercase; make sure the key is lower as well
    else if (islower(input) && key < 97)
    {
        key = key + 32;
    }
    return key;
}