#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
//The alphabet, each letter will be matched with a location in POINTS array
char alphabet[] = {A, B, C, D, E, F, G, H, I, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z}

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
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int i = 0, score_count = 0, letter_loc = 0;
    toupper(word)
    while (word[i] != '\0')
    {
        // Find the location of the letter in the alphabet
        while (word[i] )
    }
}
