#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    float letters_f = letters, words_f = words, sentences_f = sentences;
    float L = letters_f / (words_f / 100);
    float S = sentences_f / (words_f / 100);
    float index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}

//This function calculates the number of letters by calculating the number of characters that are not letters
//And the deducting this number from the strlen of the input text
int count_letters(string text)
{
    //Declaring the alphabet to determine what is a letter and what is not
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int notLetters = 0, position = 0;
    while (text[position] != '\0')
    {
        //P is the position of the letter in the alphabet
        //The nested loop keeps the checks whether the current chat of the text belongs to the alphabet
        int p = 0, letterCount = 0;
        while (alphabet[p] <= 'z')
        {
            if (alphabet[p] == text[position])
            {
                letterCount++;
            }
            p++;
        }
        //If after the nested loop the number of letters is zero; it means that there are no characters belonging to the alphabet
        //Therefore the value of the variable "notLetters" increases by one each time the condition above is met
        if (letterCount == 0)
        {
            notLetters++;
        }
        position++;
    }
    int letters = strlen(text) - notLetters;
    return letters;
}

//This loop counts words by counting the number of spaces, there is a (+1) at the end to account to the first word which would not be counted elsewise
//The "1" is only added to word_number if the user entered at least one character otherwise text is blank
int count_words(string text)
{
    string words = text;
    int i = 0, word_number = 0;
    while (words[i] != '\0')
    {
        if (words[i] == ' ')
        {
            word_number++;
        }
        i++;
    }
    if (words[0] != '\0')
    {
        word_number = word_number + 1;
    }
    return word_number;
}

//This function will count sentences, it will use the same technique as count_words
//However we won't need the (+1) here, because the first few words are not a sentence if they do not end with a '.' or '!' or '?'
int count_sentences(string text)
{
    string sentences = text;
    int sentence_number = 0, i = 0;
    while (sentences[i] != '\0')
    {
        if (sentences[i] == '.' || sentences[i] == '!' || sentences[i] == '?')
        {
            sentence_number++;
        }
        i++;
    }
    return sentence_number;
}