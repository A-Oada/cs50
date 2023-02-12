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

    if (score1 > score2)
    {
        printf("Player 1 Wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie\n");
    }
}

int compute_score(string word)
{
    int score = 0;
    int ScoreCounter = 0;
    char checking_stuff = word[ScoreCounter];
    char LowerLetters[] = "abcdefghijklmnopqrstuvwxyz";
    char UpperLetters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //The next 2 loops will calculate the score, first one is to define the letter we're checking for
    //second one nested inside it will check for this letter inside the whole word
    for (int defLetter = 0; defLetter <= 26; defLetter++)
    {
        for (int checkLetter = 0; checkLetter <= strlen(word); checkLetter++)
        {
            if (word[checkLetter] == LowerLetters[defLetter] || word[checkLetter] == UpperLetters[defLetter])
            {
                score = score + POINTS[defLetter];
            }
        }
    }
    return score;
}
