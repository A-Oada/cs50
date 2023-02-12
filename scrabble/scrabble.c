#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

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
    int counting_loop = 0, score_count = 0, letter_loc = 0, upping_loop = 0;
    // Convert word to uppercase to match with uppercase alphabet
    while (word[upping_loop] != '\0')
    {
        word[upping_loop] = toupper(word[upping_loop]);
        upping_loop++;
    }
    //The alphabet, each letter will be matched with a location in POINTS array
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (word[counting_loop] != '\0')
    {
        // Find the location of the letter in the alphabet
        do
        {
            letter_loc++;
        }
        while (word[letter_loc] != alphabet[letter_loc]);
        score_count = POINTS[letter_loc] + score_count;
        // Reset the location back to zero for next loop iteration
        letter_loc = 0;
    }
    return score_count;
}
