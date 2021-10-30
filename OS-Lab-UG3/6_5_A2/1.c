/**
#  * Group No.: 6 (Batch-A2)
#  * Group Members : 1) Sk Asif      -- Roll No. 64
#  *                 2) Sagnik Haldar -- Roll No. 74
#  *                 3) Soumitri Chattopadhyay -- Roll No. 83
#  * 
#  * Dept : Information Technology
#  * Year : 3rd Year 1st Semester
#  * Subject: Operating Systems Lab
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment No. : 5  |  Question
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details: Implement a program for producer consumer problem: A producer process produces information that is
						 consumed by a consumer process. The problem describes two processes, the producer and the
						 consumer, who share a common, fixed-size buffer. The producer&#39;s job is to generate data (A to Z) and
						 put it into the buffer and start again. At the same time the consumer is consuming the data (i.e.
						 removing it from the buffer) one piece at a time.
						 1. Create a semaphore.
						 2. Create a shared buffer
						 3. Initialize value of the semaphore to 1.
						 4. Create a child process.
						 5. Child process (Producer) writes to the buffer.
						 6. Producer performs an up operation on the semaphore for the consumer to consume.
						 7. Parent process (Consumer) performs a down operation on the semaphore and reads or
							consumes the data from the buffer (Print A …Z)
						 8. Consumer then performs an up operation.
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: gcc 1.c -o 1.out -lpthread
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence:  ./1.out
#  * ------------------------------------------------------------------------------------------------------------------
     Output :
	 ❯ ./1.out
			Child writes: a
			                         Parent reads: a
			Child writes: b
			                         Parent reads: b
			Child writes: c
			                         Parent reads: c
			Child writes: d
			                         Parent reads: d
			Child writes: e
			                         Parent reads: e
			Child writes: f
			                         Parent reads: f
			Child writes: g
			                         Parent reads: g
			Child writes: h
			                         Parent reads: h
			Child writes: i
			                         Parent reads: i
			Child writes: j
			                         Parent reads: j
			Child writes: k
			                         Parent reads: k
			Child writes: l
			                         Parent reads: l
			Child writes: m
			                         Parent reads: m
			Child writes: n
			                         Parent reads: n
			Child writes: o
			                         Parent reads: o
			Child writes: p
			                         Parent reads: p
			Child writes: q
			                         Parent reads: q
			Child writes: r
			                         Parent reads: r
			Child writes: s
			                         Parent reads: s
			Child writes: t
			                         Parent reads: t
			Child writes: u
			                         Parent reads: u
			Child writes: v
			                         Parent reads: v
			Child writes: w
			                         Parent reads: w
			Child writes: x
			                         Parent reads: x
			Child writes: y
			                         Parent reads: y
			Child writes: z
			                         Parent reads: z
            
# */

#include <semaphore.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>	/*  This file is necessary for using shared
			    memory constructs
			*/
void Producer(){

}
int main()
{
	int shmid;
	int status;
	int *a, *b;
	char *mutex1, *mutex2;
	int i;

	sem_t *sem1, *sem2;
    

	shmid = shmget(IPC_PRIVATE, sizeof(char), 0666|IPC_CREAT);
	sem1 = sem_open(mutex1, O_CREAT, 0666, 1);
	sem2 = sem_open(mutex2, O_CREAT, 0666, 0);

	if (fork() == 0) {

		
		a = (int *)shmat(shmid, 0, 0);
		// sem = sem_open(mutex, O_CREAT, 0666, 1);
		
		for (i = 0; i < 26; i++)
		{
			sem_wait(sem1);
			a[0] = 97 + i;
			printf("Child writes: %c\n", (char)(a[0]));
			sleep(1);
			sem_post(sem2);
				}
		

		shmdt(a);
	}
	else {
       b =  (int *)shmat(shmid, 0, 0);
	  
	   for (i = 0; i < 26; i++)
	   {
		   sem_wait(sem2);
		   printf("\t\t\t Parent reads: %c\n", (char)b[0]);
		   sleep(1);
		   sem_post(sem1);
		   }
		    

		   shmdt(b);
		   wait(&status);

		   shmctl(shmid, IPC_RMID, 0);
		   sem_close(sem1);
		   sem_close(sem2);
	}

	return 0;
}
