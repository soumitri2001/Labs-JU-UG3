/**
 * Name: Soumitri Chattopadhyay
 * Roll: 001911001083
 * Year: UG-3 (5th Semester)
 * Subject: Compiler Lab Assignment 2
 *--------------------------------------------------------------------------------------------------------------------
 *  Question 3: Check whether an input string is accepted or rejected by a given DFA (DFA simulation).
 *--------------------------------------------------------------------------------------------------------------------
 * Compilation Sequence :   gcc 3.c
 *--------------------------------------------------------------------------------------------------------------------
 * Execution Sequence :     ./a.out input_DFA_83.txt       
 *--------------------------------------------------------------------------------------------------------------------
 * Input File : input_DFA_83.txt 
 *
 *  <N> --> number of states in DFA [states are assumed from 0...N-1]
 *  <M> --> number of symbols in DFA [symbols are assumed from 0...M-1]
 *  <F> --> number of final states in DFA
 *  <[S1...SF]> --> final states defined by the user [S1...SF]
 *  <u1 i1 v1>
 *  <u2 i2 v2>
 *  .
 *  .
 *  .
 *  <uK iK vK>
 *  .
 *  .
 *  .
 *  where,
 *  uK = source state
 *  iK = flow symbol 
 *  vK = final state
 *--------------------------------------------------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* defining standard constants */
#define DFA_STATE_LIM 256 // maximum number of DFA states
#define SYMBOL_LIM 256    // maximum number of input symbols
#define INITIAL_STATE 0   // '0' is taken to be the starting state or initial state

int states, symbols;
int num_final_states;

int trans_mat[DFA_STATE_LIM][SYMBOL_LIM]; // matrix in order to store the transitions from one state to other due to a input symbol
bool final_states[DFA_STATE_LIM];         // to mark the final states as 'true' among all the DFA states, as per the input

void loadDFA(int argc, char **argv)
{
    FILE *fs;

    int k;
    int src_state, curr_symbol, next_state;

    fs = fopen(argv[1], "r");
    if (!fs)
    {
        printf("Error in opening file\n");
        exit(1);
    }

    fscanf(fs, "%d", &states);           // number of states
    fscanf(fs, "%d", &symbols);          // number of symbols
    fscanf(fs, "%d", &num_final_states); // number of final states

    for (int i = 0; i < num_final_states; i++)
    {
        fscanf(fs, "%d", &k);
        final_states[k] = true;
    }

    memset(trans_mat, -1, DFA_STATE_LIM * SYMBOL_LIM * sizeof(int));

    while (!feof(fs))
    {
        fscanf(fs, "%d %d %d", &src_state, &curr_symbol, &next_state);
        trans_mat[src_state][curr_symbol] = next_state;
    }

    // checking if the constructed DFA is well defined or not
    for (int i = 0; i < states; i++)
    {
        for (int j = 0; j < symbols; j++)
        {
            if (trans_mat[i][j] < 0 || trans_mat[i][j] >= states)
            {
                printf("\nDFA not defined properly.\n");
                exit(1);
            }
        }
    }
    fclose(fs);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Invalid arguments entered -- arguments should be [EXEC_FILE] [INPUT_FILE]\n");
        exit(1);
    }

    // load the DFA pasrc_stateed by user
    loadDFA(argc, argv);

    // read the string to be tested
    char str[256];
    printf("Enter the string to be checked for DFA:\n");
    scanf("%s", str);

    // print the DFA parameters provided
    printf("\n------------------------\n");
    printf("DFA input provided:\n");
    printf("Total number of states is: %d\n", states);
    printf("Total number of symbols is: %d\n", symbols);
    printf("------------------------\n");
    printf("Permissible symbols are: ");
    for (int i = 0; i < symbols; i++)
    {
        printf("%d ", i);
    }

    printf("\nInitial State of DFA is: %d\n", INITIAL_STATE);

    printf("Final State(s) of DFA: ");
    for (int i = 0; i < DFA_STATE_LIM; i++)
    {
        if (final_states[i] == true)
        {
            printf("%d ", i);
        }
    }
    printf("\n------------------------\n");

    int curr_state = INITIAL_STATE;
    int sym;
    int len = strlen(str);

    printf("State transitions are as follows:\n");
    printf("%d --> ", curr_state);
    for (int i = 0; str[i] != '\0'; i++)
    {
        sym = str[i] - '0';

        if (sym < 0 || sym >= symbols)
        {
            printf("\n\ninput string REJECTED -- unknown symbol [%d] occured\n", sym);
            printf("------------------------\n");
            return 1;
        }

        curr_state = trans_mat[curr_state][sym];
        if (curr_state == -1)
        {
            printf("\n\nInput string REJECTED -- transition is not permissible\n");
            return 1;
        }
        if (i < len - 1)
        {
            printf("%d --> ", curr_state);
        }
        else
        {
            printf("%d\n", curr_state);
        }
    }
    if (final_states[curr_state] == true)
    {
        printf("\nFinal state REACHED -- input string ACCEPTED by the provided DFA\n");
        printf("------------------------\n");
        return 1;
    }
    else
    {
        printf("\nFinal state NOT reached -- input string REJECTED by the provided DFA\n");
        printf("------------------------\n");
        return 1;
    }
    printf("------------------------\n");
    return 0;
}
