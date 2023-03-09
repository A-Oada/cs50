#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    // A loop that compares the name to each element in the array candidates
    for (int i = 0; i < MAX; i++)
    {
        if (candidates[i].name != NULL && strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    /*
    **  Loop to find the largest number of all the votes
    ** Once  the winning vote is determined,  Print each voter who has the winning vote
    ** The number of iterations of the loop depend on the number of candidates which is the same as the number
    */
    int win_vote = 0, win_size = 0, cand_size = (sizeof(candidates) / sizeof(candidate));
    for (int i = 0; i < cand_size; i++)
    {
        if (win_vote < candidates[i].votes)
        {
            win_vote = candidates[i].votes;
        }
    }
    for (int i = 0; i < cand_size; i++)
    {
        if  (candidates[i].votes == win_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}