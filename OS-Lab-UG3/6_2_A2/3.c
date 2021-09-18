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
 * Assignment No. : 2  |  Question: 3
 * ------------------------------------------------------------------------------------------------------------------
 * Assignment Details:  Demonstrate the usage of Linux system calls of EXEC FAMILY:
 *                           - execl (char * pathname , const char *arg1…….const char *argn , (char *)0)
 *                           - execv(char *pathname , char *const arg[])
 *                           - execlp(char *filename , const char *arg1…….const char *argn , (char *)0)
 *                           - execvp(char *filename , char *const arg[])
 *                      Use these calls for executing various Linux commands like whoami, ls , pwd.
 * ------------------------------------------------------------------------------------------------------------------
 * Compilation sequence: gcc 3.c -o 3.out -Werror
 * ------------------------------------------------------------------------------------------------------------------
 * Execution sequence:  ./3.out
 * ------------------------------------------------------------------------------------------------------------------
 */

/**
 * Program Description:
 * 
 *-------------------------------------------------------------------------------------------------------------------
 */

/**
OUTPUT :
    sagnik@LAPTOP-I58N2SVI:~/OSLab/ass2$ gcc 3.c -o 3.out -Werror
    sagnik@LAPTOP-I58N2SVI:~/OSLab/ass2$ ./3.out
    1 -> to run execl system call
    2 -> to run execv system call
    3 -> to run execlp system call
    3 -> to run execvp system call
    Enter your choice : 4
    /home/sagnik/OSLab/ass2
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
        int err, choice;
        const char *path1 = "/usr/bin/ls", *arg1 = "ls", *arg2 = "-a";
        const char *path2 = "/usr/bin/pwd";
        char *const args2[] = {"pwd", NULL};
        char *const args1[] = {"ls", "-a", NULL};

        printf("1 -> to run execl system call\n");
        printf("2 -> to run execv system call\n");
        printf("3 -> to run execlp system call\n");
        printf("4 -> to run execvp system call\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            err = execl(path1, arg1, arg2, NULL);
            break;

        case 2:
            err = execv(path2, args2);
            break;

        case 3:
            err = execlp("ls", arg1, arg2, NULL);
            break;

        case 4:
            err = execvp("pwd", args2);
            break;

        //a file that doesn't exist so return value is -1;
        default:
            err = execvp("pw", args2);
        }

        printf("Error wrong file or path provided as argument : %d\n", err);
    }
    else
    {
        wait(NULL);
    }

    return 0;
}