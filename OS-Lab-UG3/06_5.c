# /**
#  * Group No.: 6 (Batch-A2)
#  * Group Members : 1) Sk Asif      -- Roll No. 64
#  *                 2) Sagnik Haldar -- Roll No. 74
#  *                 3) Soumitri Chattopadhyay -- Roll No. 83
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment No. : 5
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details: Objective of this programming assignment is to use mmap() call and observe page-fault using 
#  *                     ‘sar’ command.
#  * ------------------------------------------------------------------------------------------------------------------
#  * Input Description: We are creating a file and using that descriptor we use fallocate function to allocate a given
#  *                    file size of 8GB. We use the mmap function to bring portions of the file into the memory.
#  *                    It gives us faster access to the file since it's in memory rather than reading from disk.
#  *                    We start an infinite loop with a message printed if the written data into the file is different
#  *                    to the read data.
#  * ------------------------------------------------------------------------------------------------------------------
#  * Output Description: We can see from the output that at first when the program isn't executing the page-faults/sec
#  *                     are lesser. As we start our program we see a spike in the number showing that a larger number
#  *                     of page faults occuring initially as the data is being loaded for the first time in memory.
#  *                     With time the page faults becomes relatively stable still higher than our starting values
#  *                     which helps us understand that a number of page faults occur to bring in required data into
#  *                     memory and swap out unused pages. And after stopping the program again we see a decrease the
#  *                     value since our memory doesn't demand that amount of huge data.
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: gcc 06_5.c -Werror
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence: sar -B 1 1000
#  *                     ./a.out
#  * ------------------------------------------------------------------------------------------------------------------
     Output :
            ❯ sar -B 1 1000
            Linux 5.11.0-38-generic (asif-Strix-15-GL503GE)     23/10/21    _x86_64_    (8 CPU)

            09:09:15 PM IST  pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s    %vmeff
            09:09:16 PM IST      0.00      0.00  11227.00      0.00  13000.00      0.00      0.00      0.00      0.00
            09:09:17 PM IST      0.00    592.00  10681.00      0.00  11996.00      0.00      0.00      0.00      0.00
            09:09:18 PM IST      0.00      0.00  12807.00      0.00  18523.00      0.00      0.00      0.00      0.00
            09:09:19 PM IST      0.00    120.00  11923.00      0.00  13387.00      0.00      0.00      0.00      0.00
            09:09:20 PM IST      0.00      0.00  11165.00      0.00  11379.00      0.00      0.00      0.00      0.00
            09:09:21 PM IST      0.00      0.00  14192.00      0.00  19558.00      0.00      0.00      0.00      0.00
            09:09:22 PM IST      0.00      0.00  52790.00      0.00  48540.00      0.00      0.00      0.00      0.00
            09:09:23 PM IST      0.00      0.00  11849.00      0.00  15829.00      0.00      0.00      0.00      0.00
            09:09:24 PM IST      0.00    772.00  82900.00      0.00  87941.00      0.00      0.00      0.00      0.00
            09:09:25 PM IST      0.00     92.00  80270.00      0.00  77803.00      0.00      0.00      0.00      0.00
            09:09:26 PM IST      0.00      0.00  58984.00      0.00  81848.00      0.00      0.00      0.00      0.00
            09:09:27 PM IST      0.00    128.00  56945.00      5.00  71439.00      0.00      0.00      0.00      0.00
            09:09:28 PM IST      0.00      0.00  58135.00      0.00  65594.00      0.00      0.00      0.00      0.00
            09:09:29 PM IST      0.00     84.00  56513.00      0.00  73928.00      0.00      0.00      0.00      0.00
            09:09:30 PM IST      0.00      0.00  61060.00      0.00  74935.00      0.00      0.00      0.00      0.00
            09:09:31 PM IST      0.00      0.00  59597.03      0.00  69116.83      0.00      0.00      0.00      0.00
            09:09:32 PM IST      0.00      0.00  58648.00      0.00  76740.00      0.00      0.00      0.00      0.00
            09:09:33 PM IST      0.00    592.00  56289.00      0.00  70006.00      0.00      0.00      0.00      0.00
            09:09:34 PM IST      0.00      0.00  59607.00      0.00  73381.00      0.00      0.00      0.00      0.00
            09:09:35 PM IST      0.00      0.00  60581.00      0.00  72521.00      0.00      0.00      0.00      0.00
            09:09:36 PM IST      0.00      0.00  60733.00      0.00  75773.00      0.00      0.00      0.00      0.00
            09:09:37 PM IST      0.00      0.00  56072.00      0.00  64434.00      0.00      0.00      0.00      0.00
            09:09:38 PM IST      0.00   4020.00  55058.00      0.00  65551.00      0.00      0.00      0.00      0.00
            09:09:39 PM IST      0.00    708.00  57821.00      0.00  70318.00      0.00      0.00      0.00      0.00
            09:09:40 PM IST      0.00    140.00  67266.00      0.00  78283.00      0.00      0.00      0.00      0.00
            09:09:41 PM IST      0.00     60.00  31701.00      0.00  35147.00      0.00      0.00      0.00      0.00
            09:09:42 PM IST      0.00      0.00  41083.00      0.00  41414.00      0.00      0.00      0.00      0.00
            09:09:43 PM IST      0.00      0.00  11415.00      0.00  15929.00      0.00      0.00      0.00      0.00
            09:09:44 PM IST      0.00    356.00  35908.00      0.00  40897.00      0.00      0.00      0.00      0.00
            09:09:45 PM IST      0.00      0.00  13341.00      0.00  18983.00      0.00      0.00      0.00      0.00
            09:09:46 PM IST      0.00      0.00  16602.00      0.00  12294.00      0.00      0.00      0.00      0.00
            09:09:47 PM IST      0.00      0.00  11031.00      0.00  13578.00      0.00      0.00      0.00      0.00
            09:09:48 PM IST      0.00      0.00  10934.00      0.00  11454.00      0.00      0.00      0.00      0.00
            09:09:49 PM IST      0.00     88.00  11244.00      0.00  12344.00      0.00      0.00      0.00      0.00
            09:09:50 PM IST      0.00     12.00  10682.00      0.00  10751.00      0.00      0.00      0.00      0.00
            09:09:51 PM IST      0.00     28.00  10993.00      0.00  11749.00      0.00      0.00      0.00      0.00
            09:09:52 PM IST      0.00      0.00  10832.00      0.00  13455.00      0.00      0.00      0.00      0.00
            09:09:53 PM IST      0.00      0.00  11397.00      0.00  14628.00      0.00      0.00      0.00      0.00
            09:09:54 PM IST      0.00   3468.00  11702.00      0.00  15940.00      0.00      0.00      0.00      0.00
            ^C

            Average:         0.00    288.64  36466.91      0.13  42837.17      0.00      0.00      0.00      0.00
#  */


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <unistd.h>
#define f_size (long long)8E9   //file size
#define f_s 200

int main(int argc, char* argv[]){

    //file descriptor
    int fd;
    //creating a file with read and right permissions
    fd = open("file", O_CREAT|O_RDWR, 0777);

    //using the fallocate() function to allocate desired file size with value 0
    if(fallocate(fd, 0, 0, f_size)==-1){
        perror("The desired file size couldnot be allocated!!");
        exit(1);
    }

    //a structure to hold the size of the file
    struct stat sb;
    //gets us the size of the file
    fstat(fd, &sb);
    printf("File size: %ld\n", sb.st_size);

    //mmap() function maps the data from the disk using the file descriptor to the physical memory
    void *file_memory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    //checks for possible errors while allocating the file
    if(*((int*)file_memory) == -1){
        perror("The file could not be mapped to the virtual address area.");
        exit(1);
    }

    char *file_in_memory = (char*)file_memory;
    //the infinite loop for us to observe the page faults
    while(1){
        //getting a random integer value to write into a random offset into the allocated file
        int X = rand() % 100;
        printf("%d\n", X);

        //getting a random offset within the range of the file size(8GB) to write a random number which
        //was generated earlier
        int F = rand() % f_s;

        //writing to the file offset
        file_in_memory[F] = X;

        //checking to see if both values are same
        int data_read = file_in_memory[F];
        if(data_read!=X)
            perror("The data that was written at the offset originally is not the same data that was read from the offset later!!");
    }

    return 0;
}