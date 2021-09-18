/**
 * Group No. : 6 (Batch-A2)
 * Group Members : 1) Sk Asif      -- Roll No. 64
 *                 2) Sagnik Haldar -- Roll No. 74
 *                 3) Soumitri Chattopadhyay -- Roll No. 83
 * 
 * Dept : Information Technology
 * Year : 3rd Year 1st Semester
 * Subject: Operating Systems Lab
 * ------------------------------------------------------------------------------------------------------------------
 * Assignment No. : 2  |  Question: 2(b)
 * ------------------------------------------------------------------------------------------------------------------
 * Assignment Details:  Write a program to demonstrate usage of linux system calls on Process Management:
 *                      Fork (), (Orphan and Zombie process) Exec(),Wait() and Sleep().
 *                       (b) Zombie process
 *                               1. Create a child process
 *                               2. Parent process is suspended for some time so that the Child process
 *                               terminates to
 *                               demonstrate the Zombie process
 * ------------------------------------------------------------------------------------------------------------------
 * Compilation sequence: gcc 2b.c -o 2b.out -Werror
 * ------------------------------------------------------------------------------------------------------------------
 * Execution sequence:  ./2b.out
 * ------------------------------------------------------------------------------------------------------------------
 */

/**
 * Program Description:
 * 
 *-------------------------------------------------------------------------------------------------------------------
 */

/**
OUTPUT : 
        sagnik@LAPTOP-I58N2SVI:~$ ps -aux
        USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
        root         1  0.0  0.0    892   580 ?        Sl   Aug25   0:00 /init
        root       429  0.0  0.0    892    80 ?        Ss   00:17   0:00 /init
        root       430  0.0  0.0    892    80 ?        S    00:17   0:00 /init
        sagnik     431  0.0  0.0  10272  5408 pts/1    Ss   00:17   0:00 -bash
        root       513  0.0  0.0    892    80 ?        Ss   00:23   0:00 /init
        root       514  0.0  0.0    892    80 ?        R    00:23   0:00 /init
        sagnik     515  0.0  0.0  10164  5128 pts/0    Ss   00:23   0:00 -bash
        root       533  0.0  0.0    892    80 ?        Ss   00:25   0:00 /init
        root       534  0.0  0.0    892    80 ?        S    00:25   0:00 /init
        sagnik     535  0.0  0.0   2608   596 pts/2    Ss+  00:25   0:00 sh -c "$VSCODE_WSL_EXT_LOCATION/scripts/wslServer.sh" 3
        sagnik     536  0.0  0.0   2608  1788 pts/2    S+   00:25   0:00 sh /mnt/c/Users/hp/.vscode/extensions/ms-vscode-remote.
        sagnik     542  0.0  0.0   2608   536 pts/2    S+   00:25   0:00 sh /home/sagnik/.vscode-server/bin/3866c3553be8b268c8a7
        sagnik     544  3.8  0.9 921552 58540 pts/2    Sl+  00:25   0:04 /home/sagnik/.vscode-server/bin/3866c3553be8b268c8a7f8c
        sagnik     555  0.4  0.5 612940 35764 pts/2    Sl+  00:25   0:00 /home/sagnik/.vscode-server/bin/3866c3553be8b268c8a7f8c
        sagnik     583  5.5  1.5 833864 95764 pts/2    Sl+  00:25   0:06 /home/sagnik/.vscode-server/bin/3866c3553be8b268c8a7f8c
        sagnik     589  0.7  0.6 875732 40236 pts/2    Sl+  00:25   0:00 /home/sagnik/.vscode-server/bin/3866c3553be8b268c8a7f8c
        sagnik     619  0.0  0.0   2356   584 pts/1    S+   00:27   0:00 ./2b.out
        sagnik     620  0.0  0.0      0     0 pts/1    Z+   00:27   0:00 [2b.out] <defunct>
        sagnik     621  0.0  0.0  10856  3368 pts/0    R+   00:27   0:00 ps -aux


        sagnik@LAPTOP-I58N2SVI:~/OSLab/ass2$ ./2b.out
        Parent process ID 619
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int cid = fork();

    //for the 10 second duration the child process remains as the zombie process after it finishes executing
    if (cid != 0)
    {
        sleep(10);
        printf("Parent process ID %d\n", getpid());
    }

    return 0;
}