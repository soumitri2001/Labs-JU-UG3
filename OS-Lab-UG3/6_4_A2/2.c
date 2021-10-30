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
#  * Assignment No. : 4  |  Question: 2
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details: Consider a process with three threads A, B, and C. The default thread of the process
                        receives two inputs (X,Y) and places them in a queue that is accessible by all the
                        three threads A, B and C. For each pair of input (X,Y), we require that the request
                        must first be processed by thread A (Multiplication (X*Y)), then B(Division (X*Y)/2),
                        then C (Addition (X+Y)), then B again ( (X*Y) /(X+Y)), and finally by A((X+Y)* (X+Y))
                        before the pair (X,Y) can be removed and discarded from the queue. Thread A must
                        read the next request from the queue only after it is finished with all the above steps
                        of the previous one. Write down code for the functions run by the threads A, B, and
                        C, to enable this synchronization. You may use any synchronization primitive of your
                        choice to solve this question.
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: gcc 2.c -o 2.out -lpthread -lrt
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence:  ./2.out
#  * ------------------------------------------------------------------------------------------------------------------
     Output :
            soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3/Ass4$ gcc 2.c -o 2.out -lpthread -lrt
            soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3/Ass4$ ./2.out
            Enter pairs of numbers, -1 to stop...
            1 4
            -2.5 6.3
            2 7
            1 8
            -1

            -------------------------
            Operations performed:
            -------------------------
            (X*Y): 4.0000
            (X*Y)/2 : 2.0000  
            (X+Y) : 5.0000 
            (X*Y)/(X+Y) : 0.8000 
            (X+Y)(X+Y): 25.0000
            ---------------------
            (X*Y): -15.7500
            (X*Y)/2 : -7.8750  
            (X+Y) : 3.8000 
            (X*Y)/(X+Y) : -4.1447 
            (X+Y)(X+Y): 14.4400
            ---------------------
            (X*Y): 14.0000
            (X*Y)/2 : 7.0000  
            (X+Y) : 9.0000 
            (X*Y)/(X+Y) : 1.5556 
            (X+Y)(X+Y): 81.0000
            ---------------------
            (X*Y): 8.0000
            (X*Y)/2 : 4.0000  
            (X+Y) : 9.0000 
            (X*Y)/(X+Y) : 0.8889 
            (X+Y)(X+Y): 81.0000
            ---------------------
# */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/** 
 * The following codes pertain to Queue implementation using a linkedlist.
 * The queue is used to hold the input number pairs to be shared by the 3 threads. 
 */

// structure for node of linkedlist
typedef struct Node
{
    float x, y;
    struct Node *next;
} Node;

// structure for Queue implemented using linkedlist
typedef struct Queue
{
    Node *front, *rear;
} Queue;

// prototypes of utility functions for queue
Queue *createQueue();
void enqueue(Queue *, float, float);
void print(Queue *);
void dequeue(Queue *, int);
Node *front(Queue *);
Node *rear(Queue *);
int isEmpty(Queue *);

// utility function to get front node
Node *front(Queue *q)
{
    if (q->front == NULL)
    {
        printf("Empty Queue\n");
        return NULL;
    }
    else
        return q->front;
}

// utility function to get rear of queue
Node *rear(Queue *q)
{
    if (q->rear == NULL)
    {
        printf("Empty Queue\n");
        return NULL;
    }
    else
        return q->rear;
}

// check if queue is empty
int isEmpty(Queue *q)
{
    return q->front == NULL;
}

// create an instance of queue
Queue *createQueue()
{
    Queue *tmp = (Queue *)malloc(sizeof(Queue));
    tmp->front = NULL;
    tmp->rear = NULL;

    return tmp;
}

// utility function to push into queue using FIFO
void enqueue(Queue *q, float xx, float yy)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->x = xx;
    tmp->y = yy;
    tmp->next = NULL;

    if (!q->front)
    {
        q->front = q->rear = tmp;
        return;
    }
    else
    {
        q->rear->next = tmp;
        q->rear = tmp;
        return;
    }
}

// utility function to dequeue using FIFO
void dequeue(Queue *q, int print_flag)
{
    Node *tmp = q->front;

    if (!tmp)
    {
        printf("Queue is empty\n");
        return;
    }
    else
    {
        if (print_flag)
            printf("Dequeued element : %0.4f, %0.4f\n", tmp->x, tmp->y);
        q->front = q->front->next;
        free(tmp);
        return;
    }
}

// to print contents of queue
void print(Queue *q)
{
    Node *tmp = q->front;

    if (!tmp)
    {
        printf("Empty Queue\n");
        return;
    }
    else
    {
        while (tmp != NULL)
        {
            printf("%0.4f %0.4f\n", tmp->x, tmp->y);
            tmp = tmp->next;
        }
    }
}

/**
 * The following codes pertain to multithreaded implementation of the relevant question 
 * using the concept of semaphores and thread synchronization. 
 */

sem_t ab, bc, cb, ba; //initialising the seamophores

// utility function for (X*Y) and ((X+Y)*(X+Y))
void *fun1(void *q)
{
    Queue *waitQueue = (Queue *)q;
    Node *p = front(waitQueue);
    float res1, res5;
    while (p != NULL)
    {
        res1 = (p->x) * (p->y);
        printf("(X*Y): %0.4f\n", res1);
        sem_post(&ab);
        sem_wait(&ba);
        res5 = (p->x + p->y) * (p->x + p->y);
        printf("(X+Y)(X+Y): %0.4f\n", res5);
        p = p->next;
        dequeue(waitQueue, 0);
        printf("---------------------\n");
    }
    pthread_exit(NULL);
}

// utility function for ((X*Y)/2) and ((X*Y)/(X+Y))
void *fun2(void *q)
{
    Queue *waitQueue = (Queue *)q;
    Node *p = front(waitQueue);
    float res2, res4;
    while (p != NULL)
    {
        sem_wait(&ab);
        res2 = ((p->x) * (p->y)) / 2;
        printf("(X*Y)/2 : %0.4f  \n", res2);
        sem_post(&bc);
        sem_wait(&cb);
        res4 = ((p->x) * (p->y)) / (p->x + p->y);
        printf("(X*Y)/(X+Y) : %0.4f \n", res4);
        p = p->next;
        sem_post(&ba);
    }
    pthread_exit(NULL);
}

// utility function for (X+Y)
void *fun3(void *q)
{
    Queue *waitQueue = (Queue *)q;
    Node *p = front(waitQueue);
    float res3;
    while (p != NULL)
    {
        sem_wait(&bc);
        res3 = (p->x) + (p->y);
        printf("(X+Y) : %0.4f \n", res3);
        p = p->next;
        sem_post(&cb);
    }
    pthread_exit(NULL);
}

/* Driver method -- main() */
int main(int argc, char **argv)
{
    // create an instance of queue ADT
    Queue *q = createQueue();

    // variables to hold pairs of numbers as input
    float x, y;

    // taking user input
    printf("Enter pairs of numbers, -1 to stop...\n");
    while (1)
    {
        scanf("%f", &x);
        if (x == -1) // check termination condition
            break;
        scanf("%f", &y);

        // enqueue the pair entered
        enqueue(q, x, y);
    }

    printf("\n-------------------------");
    printf("\n  Operations performed:\n");
    printf("-------------------------\n");

    // initialising the semaphores
    sem_init(&ab, 0, 0);
    sem_init(&bc, 0, 0);
    sem_init(&cb, 0, 0);
    sem_init(&ba, 0, 0);

    // initializing threads
    pthread_t threads[3];

    pthread_create(&threads[0], NULL, fun1, (void *)q);
    pthread_create(&threads[1], NULL, fun2, (void *)q);
    pthread_create(&threads[2], NULL, fun3, (void *)q);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

    return 0;
}