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
#  * Assignment No. : 4  |  Question: 1
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details: Write a program that creates four threads, each of which finds the smallest entry of a
                         quarter of the elements of an input array, and then adds up the four smallest entries
                         to print the result.
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: gcc 1.c -lpthread -Werror
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence:  ./a.out
#  * ------------------------------------------------------------------------------------------------------------------
     Output :
            sagnik@LAPTOP-I58N2SVI:~/OSLab/ass4$ ./a.out 
            Enter size of array : 14
            Enter elements of the array : 
            1 2 3 4 5 6 7 8 9 10 11 12 13 14
            Summation of the smallest element of each quarter = 28
#  */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//current thread index
int step = 0;

struct paramInfo
{
    int *arr;
    int quarterSize;
    int size;
};

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void *findMin(void *arg)
{

    struct paramInfo *args = (struct paramInfo *)arg;

    int currentIndex = step++, start = currentIndex * args->quarterSize;
    int end = start + args->quarterSize;

    //for the last segment we search till the end of the array
    if (currentIndex == 3)
        end = args->size;

    // printf("CurrentIndex = %d, Start = %d, End = %d ...", currentIndex, start, end);

    //return value
    int *ans = (int *)malloc(sizeof(int));
    if (start < args->size)
        *ans = args->arr[start];
    // printf("ans = %d\n", *ans);

    for (int i = start + 1; i < end; i++)
    {
        *ans = min(*ans, args->arr[i]);
    }

    return ans;
}

int main(int argc, char **argv)
{

    int size, i;
    printf("Enter size of array : ");
    scanf("%d", &size);

    if (size <= 0)
    {
        printf("Enter valid size of array\n");

        return 0;
    }

    //argument structure to be sent while creating threads
    struct paramInfo args;

    //incase size < 4
    args.size = max(size, 4);

    //storing size of each quarter segment
    args.quarterSize = args.size / 4;

    //in case of non multiples of 4
    if (args.size % 4 != 0)
        args.quarterSize++;

    args.arr = (int *)malloc(size * sizeof(int));

    printf("Enter elements of the array : \n");
    for (i = 0; i < size; i++)
    {
        scanf("%d", &args.arr[i]);
    }

    //0 padding incase size of array less than 4
    while (i < args.size)
    {
        args.arr[i++] = 0;
    }

    //initializing threads
    pthread_t threads[4];

    for (int i = 0; i < 4; i++)
    {
        pthread_create(&threads[i], NULL, findMin, (void *)&args);
    }

    //result stores the return value from findMin function
    int *result, ans = 0;

    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], (void *)&result);

        ans += *result;
    }

    printf("Summation of the smallest element of each quarter = %d\n", ans);

    return 0;
}