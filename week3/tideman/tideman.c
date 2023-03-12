#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i] != NULL && strcmp(name, candidates[i]) == 0)
        {
            ranks[i] = rank;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if (ranks[i] < ranks[j])
            {
                preferences[i][j]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // temp is the variable that determines the element in pairs to be modified
    // Because if i is used some elements will be skipped
    int temp = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        // Value of j is  determine as such because the number of pairs is a combination of pair_count and 2
        // So to avoid the same pair being checked  more than once, j will always be bigger than  i by 1
        int j = i + 1;
        do
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[temp].winner = i;
                pairs[temp].loser = j;
                pair_count++, temp++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[temp].winner = j;
                pairs[temp].loser = i;
                pair_count++, temp++;
            }
            j++;
        }
        while (j < candidate_count);
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Store the differences between winner and loser in each pair in an array
    // The second index denotes the number of the pair in pairs
    // For example, if strength[0][0] = 0, strength[0][1] = 5
    // This means that element[0] in strength is  pairs[2] and the gap between loser and winner is 5
    int strength[pair_count][2];
    for (int i = 0; i < pair_count; i++)
    {
        strength[i][0] = i;
        int j = i + 1;
        // Use pairs[i] to find loser and winner
        // Since each winner/loser corresponds to two elemens in preferences, subtract them to get strength
        // Use abs function to avoid negative strength value
        strength[i][1] = abs(preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]);
    }
    // Sort array, using strength[i][1] as reference
    // After sorting, strength[i][0] will be used to determine to determine which is the leading pair
    // Sorting is done using selection sort - not good enough to do merge sorting yet :(
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            int temp;
            if (strength[i][1] > strength[j][1])
            {
                temp = strength[i][1];
                strength[i][1] = strength[j][1];
                strength[j][1] = temp;
                temp = strength[i][0];
                strength[i][0] = strength[j][0];
                strength[j][0] = temp;
            }
        }
    }
    // Now use strength as a reference to sort pairs
    for (int i = 0; i < pair_count; i++)
    {
        pair temp = pairs[i];
        pairs[i] = pairs[strength[i][0]];
        pairs[strength[i][0]] = temp;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j <= pair_count; j++)
        {
            // For a cycle to appear a pattern of triangle of trues will appear in the array
            locked[pairs[i].winner][pairs[i].loser] = true;
            locked[pairs[i].loser][pairs[i].winner] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}