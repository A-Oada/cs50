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
bool cyclic(int start, int loser);
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
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
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
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
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
    // Sorting is done using selection sort - not good enough to do merge sorting yet :(
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            // Sorting is done by comparing i-th pair gap to the j-th gap, if the i-th gap is smaller, swap the pairs
            int strength1 = preferences[pairs[i].winner][pairs[i].loser];
            int strength2 = preferences[pairs[j].winner][pairs[j].loser];
            if (strength1 < strength2 && i < j)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs()
{
    /**
     *  This function will check for a loser via recursion
     *  In the recursive helper function cyclic, the function will retain the starting candidate,
     *  then go down the graph and see if the loser to start defeats anyone
     *  If the loser does win, it checks compares the loser to the loser with start
     *  It goes on to the bottom of the graph
     *  It iterates a number of times = candidate_count, since the longest possible path  for a cycle is candidate_count - 1
     */
    for (int i = 0; i < candidate_count; i++)
    {
        // cyclic is the function that will determine whether there is an edge
        if (!cyclic(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Helper function that determines whether there is a circle
bool cyclic(int start, int loser)
{
    if (start == loser)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // If the loser to the original winner has any losers
        if (locked[loser][i])
        {
            // check if the loser to the original loser is the same as start
            if (cyclic(start, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // winner will be determined by the amounts of "true" values in the locked array
    // The row that has the largest amount of true values is has the winners index
    int most = 0;
    for (int i = 0; i < candidate_count; i ++)
    {
        int temp_sum = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                temp_sum++;
            }
        }
        if (temp_sum > most)
        {
            most = temp_sum;
        }
    }
    // Check the number of true values in each row,
    // if these numbers are equal to  most, print the corresponding candidate
    for (int i = 0; i < candidate_count; i++)
    {
        int votes = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                votes++;
            }
        }
        if (votes >= most)
            {
                printf("%s\n", candidates[i]);
            }
    }
    return;
}