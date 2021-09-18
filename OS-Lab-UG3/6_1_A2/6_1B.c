/*
 * Group No :6 (Batch-A2)
 * Group Members : 1) Sk Asif      -- Roll No. 64
 *                 2) Sagnik Haldar -- Roll No. 74
 *                 3) Soumitri Chattopadhyay -- Roll No. 83
 *
 * Dept : Information Technology
 * Year : 3rd Year 1st Semester
 * Subject: Operating Systems Lab
 *
 *---------------------------------------------------------------------------------------------
 * Assignment Details: Program to get and set environment variables using
 *                     system calls
 *---------------------------------------------------------------------------------------------
 * Compilation sequence: gcc 6_1B.c -o 6_1B.out -Werror
 *---------------------------------------------------------------------------------------------
 * Execution sequence:  ./6_1B.out
 *---------------------------------------------------------------------------------------------
 * Program Description :-
 *
 *   This program demonstrates how to get and set environment variables using
 *   system calls like getenv() and setenv().
 *
 *   The C library function char *getenv(const char *name) searches for the
 *   environment string pointed to by name and returns the value associated
 *   with the string.
 *
 *   The setenv() function adds the variable name to the environment with the
 *   value value, if name does not already exist. If name does exist in the
 *   environment, then its value is changed to value if overwrite is nonzero;
 *   if overwrite is zero, then the value of name is not changed (and setenv()
 *   returns a success status).
 *---------------------------------------------------------------------------------------------
 * Output:
 *  Printing the current environment variables.
    $USER: asif
    $HOME: /home/asif
    $HOST: (null)
    $ARCH: (null)
    $DISPLAY: :0
    $PRINTER: (null)
    $PATH: /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

    Creating new environment variable named NEWENV.
    $NEWENV: TEAM_6

    Passing overwrite=0 to check whether the environment-variable is overwritten or not.
    $NEWENV: TEAM_6

    Passing overwrite=1 and the overwrite of the environment variable should be successful.
    $NEWENV: ZERO
 
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

    /*
    *  USER (your login name)
    *  HOME (the path name of your home directory)
    *  HOST (the name of the computer you are using)
    *  ARCH (the architecture of the computers processor)
    *  DISPLAY (the name of the computer screen to display X windows)
    *  PRINTER (the default printer to send print jobs)
    *  PATH (the directories the shell should search to find a command)
    */

    const char *params[7] = {"USER", "HOME", "HOST", "ARCH", "DISPLAY", "PRINTER", "PATH"};

    int i;
    printf("Printing the current environment variables.\n");

    for (i = 0; i < 7; i++)
    {
        printf("$%s: %s\n", params[i], getenv(params[i]));
    }
    printf("\n");

    const char *customEnv = "NEWENV";
    const char *customEnv_val = "TEAM_6";

    // If name does not exist then a new environment variable is created and it is initilaised with the given value.
    printf("Creating new environment variable named NEWENV.\n");
    setenv(customEnv, customEnv_val, 0);
    printf("$NEWENV: %s\n", getenv(customEnv));
    printf("\n");

    //If environment variable exists, then for overwrite=0, the value of the environment-variable is not over-written.
    printf("Passing overwrite=0 to check whether the environment-variable is overwritten or not.\n ");
    setenv(customEnv, "ZERO", 0);
    printf("$NEWENV: %s\n", getenv(customEnv));
    printf("\n");

    //If environment variable exists, then for overwrite!=0, the value of the environment-variable is  overwritten.
    printf("Passing overwrite=1 and the overwrite of the environment variable should be successful.\n");
    setenv(customEnv, "ZERO", 1);
    printf("$NEWENV: %s\n", getenv(customEnv));
    printf("\n");

    return 0;
}