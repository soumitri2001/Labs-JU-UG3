/**
 * Group No.: 6 (Batch-A2)
 * Group Members : 1) Sk Asif      -- Roll No. 64
 *                 2) Sagnik Haldar -- Roll No. 74
 *                 3) Soumitri Chattopadhyay -- Roll No. 83
 * 
 * Dept : Information Technology
 * Year : 3rd Year 1st Semester
 * Subject: Operating Systems Lab
 * ------------------------------------------------------------------------------------------------------------------
 * Assignment No. : 2  |  Question: 1
 * ------------------------------------------------------------------------------------------------------------------
 * Assignment Details:  Write a program to display process information using process related system calls
 *                      like getpid, getppid.
 *                           1 : Create a child process
 *                           2 : Print process id of the child and its parents process id.
 *                           3 : Print process id of the parent and its parents process id
 * ------------------------------------------------------------------------------------------------------------------
 * Compilation sequence: gcc 1.c -o 1.out -Werror
 * ------------------------------------------------------------------------------------------------------------------
 * Execution sequence:  ./1.out
 * ------------------------------------------------------------------------------------------------------------------
 */

/**
 * Program Description:
 * 
 *-------------------------------------------------------------------------------------------------------------------
 */

/**
OUTPUT : 
        Child Processing
        I am child and my process id is 489
        I am child and my parents process id is 488
        Parent Processing
        I am parent and my process id is 488
        I am parent and my parent process id is 431
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    //use fork to create a child process
    int cid = fork();

    //if the return value of fork is -1 then child process wasn't created
    if (cid == -1)
    {
        printf("Child process could not be created.\n");
    }

    //if the return value of fork is 0 means we are in child process
    if (cid == 0)
    {
        printf("Child Processing\n");
        printf("I am child and my process id is %d\n", getpid());
        printf("I am child and my parents process id is %d\n", getppid());
    }
    //return value of fork is the id of the child process and thus now we are in parent process
    else
    {
        wait(NULL);
        printf("Parent Processing\n");
        printf("I am parent and my process id is %d\n", getpid());
        printf("I am parent and my parent process id is %d\n", getppid());
    }

    return 0;
}