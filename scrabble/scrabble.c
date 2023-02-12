#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int alphaloc(char letter);
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    // Convert word to uppercase to match with uppercase alphabet
    int upping_loop = 0;
    while (word[upping_loop] != '\0')
    {
        word[upping_loop] = toupper(word[upping_loop]);
        upping_loop++;
    }
    // Calculating the score
    int score_count = 0;
    for (int i = 0, j = strlen(word); word[i] != '\n'; i++)
    {
        // For each letter, find it's location in the alphabet,
        int location = alphaloc(word[i]);
        // Add it's score to the count
        score_count = POINTS[location] + score_count;
    }
    return score_count;
}

// Find the location of the letter in the alphabet
int alphaloc(char letter)
{
    //The alphabet, each letter will be matched with a location in POINTS array
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int loc = 0;
    while (alphabet[i] != letter)
    {
        loc++;
    }
    return loc;
}