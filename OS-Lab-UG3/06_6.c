/**
 * Group No.: 6 (Batch-A2)
 * Group Members : 1) Sk Asif      -- Roll No. 64
 *                 2) Sagnik Haldar -- Roll No. 74
 *                 3) Soumitri Chattopadhyay -- Roll No. 83
 * ------------------------------------------------------------------------------------------------------------------
 * Assignment No. : 6
 * ------------------------------------------------------------------------------------------------------------------
 * Assignment Details: Objective of this program is to create a deadlock.
 * ------------------------------------------------------------------------------------------------------------------
 * Input Description: Total_1 & Total_2 are two variables which are taken as globals with two mutex locks to show 
 *                    deadlocks. We create two threads to run them parallely.
 * ------------------------------------------------------------------------------------------------------------------
 * Output Description: In output(1) we see output of the condition when we don't have a deadlock condition.
 *                     Both mutex locks p1 & p2 are acquired sequentially so after one thread is done with them they
 *                     are sequentially unlocked. And the other thread waiting for those mutex locks wake up to 
 *                     resume their work and thus we can see an atomic result with no race condition exhibited so we
 *                     a consistent outcome of Total_1 being reduced by a constant value and Total_2 increased by the
 *                     same value.
 *
 *                     In output(2) we get to see the deadlock occuring where we use a sleep() function to simulate
 *                     a context switch between threads and having the mutex locks in reverse order to each other.
 *                     In the output we can see thread 1 acquires mutex lock 1 and thread 2 acquires mutex lock 2 and
 *                     when thread 1 tries to acquire mutex lock 2 and thread 2 tries to acquire lock 1 they are stuck
 *                     waiting for the other to release the lock to proceed with their instructions.
 * ------------------------------------------------------------------------------------------------------------------
 * Compilation sequence: gcc 06_6.c -lpthread -Werror
 * ------------------------------------------------------------------------------------------------------------------
 * Execution sequence: ./a.out
 * ------------------------------------------------------------------------------------------------------------------
 * Output (1) :
                Waiting to acquire mutex 1 on thread 1
                Mutex1 acquired on thread 1!!
                Waiting to acquire mutex 2 on thread 1
                Mutex2 acquired on thread 1!!
                Waiting to acquire mutex 1 on thread 2
                Before performing the operation, the value of Total_1 is: 1000
                Performing operation on Total_1!!
                After performing the operation, the value of Total_1 is: 983
                Mutex1 unlocked on thread 1!!
                Mutex2 unlocked on thread 1!!
                Mutex1 acquired on thread 2!!
                Waiting to acquire mutex 2 on thread 2
                Mutex2 acquired on thread 2!!
                Before performing the operation, the value of Total_2 is: 1000
                Performing operation on Total_2!!
                After performing the operation, the value of Total_2 is: 1017
                Mutex1 unlocked on thread 2!!
                Mutex2 unlocked on thread 2!!


 * Output (2) :
                Waiting to acquire mutex 1 on thread 1
                Mutex1 acquired on thread 1!!
                Waiting to acquire mutex 2 on thread 2
                Mutex2 acquired on thread 2!!
                Waiting to acquire mutex 1 on thread 2
                Waiting to acquire mutex 2 on thread 1
                ^C
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

// global declarations of data variables and mutex variables
int Total_1 = 1000, Total_2 = 1000;
pthread_mutex_t p1, p2;

// function to execute on thread 1
void *fun1(void *args)
{
    // type cast to int from void pointer
    int *params = (int *)args;

    printf("Waiting to acquire mutex 1 on thread 1\n");
    // function to acquire respective lock
    pthread_mutex_lock(&p1);
    printf("Mutex1 acquired on thread 1!!\n");

    // The sleep statement here is present to simulate context switch
    sleep(5);

    printf("Waiting to acquire mutex 2 on thread 1\n");
    // function to acquire respective lock
    pthread_mutex_lock(&p2);

    printf("Mutex2 acquired on thread 1!!\n");
    printf("Before performing the operation, the value of Total_1 is: %d\n", Total_1);
    printf("Performing operation on Total_1!!\n");
    Total_1 = Total_1 - *(params);
    printf("After performing the operation, the value of Total_1 is: %d\n", Total_1);

    // function to acquire respective lock
    pthread_mutex_unlock(&p1);
    printf("Mutex1 unlocked on thread 1!!\n");

    // function to acquire respective lock
    pthread_mutex_unlock(&p2);
    printf("Mutex2 unlocked on thread 1!!\n");

    return NULL;
}

// function to run on 2nd thread
void *fun2(void *args)
{
    int *params = (int *)args;

    printf("Waiting to acquire mutex 2 on thread 2\n");
    // function to acquire respective lock
    pthread_mutex_lock(&p2);
    printf("Mutex2 acquired on thread 2!!\n");

    printf("Waiting to acquire mutex 1 on thread 2\n");
    // function to acquire respective lock
    pthread_mutex_lock(&p1);

    printf("Mutex1 acquired on thread 2!!\n");
    printf("Before performing the operation, the value of Total_2 is: %d\n", Total_2);
    printf("Performing operation on Total_2!!\n");
    Total_2 = Total_2 + *(params);
    printf("After performing the operation, the value of Total_2 is: %d\n", Total_2);

    // function to acquire respective lock
    pthread_mutex_unlock(&p2);
    printf("Mutex2 unlocked on thread 2!!\n");

    // function to acquire respective lock
    pthread_mutex_unlock(&p1);
    printf("Mutex1 unlocked on thread 2!!\n");

    return NULL;
}

int main()
{

    // Initializing the mutexes
    if (pthread_mutex_init(&p1, NULL) != 0)
    {
        perror("Mutex1 could not be initialised!!");
        return 0;
    }
    if (pthread_mutex_init(&p2, NULL) != 0)
    {
        perror("Mutex2 could not be initialised!!");
        return 0;
    }

    // Declaring the threads
    pthread_t thread1, thread2;

    srand(time(0));

    int args; // Stores a random number less than 50
    args = rand() % 50;

    // creating threads
    if (pthread_create(&thread1, NULL, &fun1, (void *)&args) != 0)
    {
        perror("Thread 1 could not be created!!");
        return 0;
    }
    if (pthread_create(&thread2, NULL, &fun2, (void *)&args) != 0)
    {
        perror("Thread 2 could not be created!!");
        return 0;
    }

    // waiting for the threads to complete their execution
    if (pthread_join(thread1, NULL) != 0)
    {
        perror("The created thread could not be terminated!!");
        return 0;
    };
    if (pthread_join(thread2, NULL) != 0)
    {
        perror("The created thread could not be terminated!!");
        return 0;
    };

    // destroying the mutex after we are done with it
    if (pthread_mutex_destroy(&p1) != 0)
    {
        perror("The mutex could not be destroyed!!");
        return 0;
    }
    if (pthread_mutex_destroy(&p2) != 0)
    {
        perror("The mutex could not be destroyed!!");
        return 0;
    }

    return 0;
}
