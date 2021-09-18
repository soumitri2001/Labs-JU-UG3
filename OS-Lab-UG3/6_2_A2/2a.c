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
 * Assignment No. : 2  |  Question: 2(a)
 * ------------------------------------------------------------------------------------------------------------------
 * Assignment Details:  Write a program to demonstrate usage of linux system calls on Process Management:
 *                      Fork (), (Orphan and Zombie process) Exec(),Wait() and Sleep().
 *                       (a) Orphan process
 *                               1. Create a child process
 *                               2. Child process is suspended for some time so that the parent process
 *                                  terminates
 *                               to demonstrate an orphan process
 *                               3. The init process becomes the parent of the orphan process
 * ------------------------------------------------------------------------------------------------------------------
 * Compilation sequence: gcc 2a.c -o 2a.out -Werror
 * ------------------------------------------------------------------------------------------------------------------
 * Execution sequence:  ./2a.out
 * ------------------------------------------------------------------------------------------------------------------
 */

/**
 * Program Description:
 * 
 *-------------------------------------------------------------------------------------------------------------------
 */

/**
OUTPUT : 
        Parent process ID 527
        Child processed : 528 childs parent process id : 527
        sagnik@LAPTOP-I58N2SVI:~/OSLab/ass2$ Orphan process parent is init process whose id is 430
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int cid = fork();

    if (cid == 0)
    {
        printf("Child processed : %d childs parent process id : %d\n", getpid(), getppid());
        sleep(3);
        printf("Orphan process parent is init process whose id is %d\n", getppid());
    }
    //here parent gets terminated before the child process finishes thus we are left with a orphan process
    else
    {
        printf("Parent process ID %d\n", getpid());
    }

    return 0;
}