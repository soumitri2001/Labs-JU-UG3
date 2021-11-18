/**
 * Group No.: 6 (Batch-A2)
 * Group Members : 1) Sk Asif      -- Roll No. 64
 *                 2) Sagnik Haldar -- Roll No. 74
 *                 3) Soumitri Chattopadhyay -- Roll No. 83
 * -----------------------------------------------------------------------------------------------------------
 * Assignment No. : 7
 * -----------------------------------------------------------------------------------------------------------
 * Assignment details: The objective of this assignment is to use thread programming technique to write a
 *                     parallel program which will find the minimum number from a huge unsigned character 
 *                     array.
 * -----------------------------------------------------------------------------------------------------------
 * Input description: This program should take two command line arguments. The first argument is size
 *                    of the array in Gigabyte. For example, the value of the first argument will be any
 *                    among 1, 2, 3 etc.; signifying array size of 1GB, 2GB, 3GB etc. The array size should
 *                    be at least 3x10^9. This array needs to be initialised using random number.
 *                    The second argument is about no of threads. For example, the value of the second
 *                    argument will be 1, 2, 3, and 4 etc.; signifying total no of threads which will be
 *                    created.
 * -----------------------------------------------------------------------------------------------------------
 * Output description: In order to investigate the behaviour of time elapsed for finding the minimum of the 
 *                     array using multithreading versus the number of threads considered, we provide the 
 *                     respective execution times while varying the number of threads, keeping the array 
 *                     size fixed. The outputs of this setup have been attached below in "output(1)". 
 * 
 *                     From the trend in output(1), it can be observed that as we increase the number of 
 *                     threads in the system, the execution timing significantly decreases, thereby showing 
 *                     a satisfactory improvement in execution.
 * -----------------------------------------------------------------------------------------------------------
 * Sequence to track CPU utilization: mpstat -P ALL 1 1000
 * -----------------------------------------------------------------------------------------------------------
 * Compilation sequence: gcc 06_7.c -lpthread -Werror
 * -----------------------------------------------------------------------------------------------------------
 * Execution sequence: ./a.out [size_in_GB] [nos_of_threads]
 * -----------------------------------------------------------------------------------------------------------
 * Output: [The outputs have been shown upon running the code for different values of number of threads]
 * 
 * output(1):
 *           soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3$ ./a.out 2 1
 *           global minimum element = 0
 *           Time taken to find minimum element using 1 threads = 6.850879 seconds 
 * 
 *           soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3$ ./a.out 2 2
 *           global minimum element = 0
 *           Time taken to find minimum element using 2 threads = 4.235917 seconds
 * 
 *           soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3$ ./a.out 2 3
 *           global minimum element = 0
 *           Time taken to find minimum element using 3 threads = 3.552427 seconds 
 * 
 *           soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3$ ./a.out 2 4
 *           global minimum element = 0
 *           Time taken to find minimum element using 4 threads = 3.144848 seconds
 * 
 *           soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3$ ./a.out 2 5
 *           global minimum element = 0
 *           Time taken to find minimum element using 5 threads = 2.834502 seconds 
 * 
 *           soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3$ ./a.out 2 6
 *           global minimum element = 0
 *           Time taken to find minimum element using 6 threads = 2.606178 seconds 
 * 
 *           soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3$ ./a.out 2 7
 *           global minimum element = 0
 *           Time taken to find minimum element using 7 threads = 1.728281 seconds
 * 
 *           soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3$ ./a.out 2 8
 *           global minimum element = 0
 *           Time taken to find minimum element using 8 threads = 1.699072 seconds  
 * 
 * -----------------------------------------------------------------------------------------------------------
 **/

/** 
 * System Diagnostics during execution of the program: 
 * -----------------------------------------------------------------------------------------------------------
 * 1. To show CPU utilization (for each increment in thread count) : mpstat -P ALL 1 1000 
 *  
 * [Note: each set of stats is w.r.t. the number of threads being considered, increasing stepwise from 1 to 8.]
 * 
 * 01:37:18     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 * 01:37:19     all   12.58    0.00    0.00    0.00    0.00    0.25    0.00    0.00    0.00   87.17
 * 01:37:19       0    0.00    0.00    0.00    0.00    0.00    1.96    0.00    0.00    0.00   98.04
 * 01:37:19       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:37:19       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:37:19       3    0.99    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.01
 * 01:37:19       4  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:37:19       5    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:37:19       6    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:37:19       7    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 
 * 01:37:32     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 * 01:37:33     all   24.27    0.00    0.00    0.00    0.00    3.16    0.00    0.00    0.00   72.57
 * 01:37:33       0    0.00    0.00    0.00    0.00    0.00   20.80    0.00    0.00    0.00   79.20
 * 01:37:33       1  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:37:33       2  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:37:33       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:37:33       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:37:33       5    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:37:33       6    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:37:33       7    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 *
 * 01:41:01     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 * 01:41:02     all   36.76    0.00    0.12    0.00    0.00    2.08    0.00    0.00    0.00   61.03
 * 01:41:02       0    0.00    0.00    0.00    0.00    0.00   14.53    0.00    0.00    0.00   85.47
 * 01:41:02       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:41:02       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:41:02       3  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:41:02       4    0.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00
 * 01:41:02       5  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:41:02       6  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:41:02       7    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 
 * 01:41:27     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 * 01:41:28     all   50.00    0.00    0.12    0.00    0.00    0.12    0.00    0.00    0.00   49.75
 * 01:41:28       0  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:41:28       1    0.00    0.00    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01
 * 01:41:28       2    0.00    0.00    0.00    0.00    0.00    0.99    0.00    0.00    0.00   99.01
 * 01:41:28       3  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:41:28       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:41:28       5  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:41:28       6    1.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00
 * 01:41:28       7  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 
 * 01:41:54     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 * 01:41:55     all   62.50    0.00    0.12    0.00    0.00    0.00    0.00    0.00    0.00   37.38
 * 01:41:55       0  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:41:55       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:41:55       2  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:41:55       3  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:41:55       4    0.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00
 * 01:41:55       5  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:41:55       6    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:41:55       7  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 *
 * 01:46:06     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 * 01:46:07     all   74.44    0.00    0.00    0.00    0.00    0.87    0.00    0.00    0.00   24.69
 * 01:46:07       0  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:07       1    0.00    0.00    0.00    0.00    0.00    6.60    0.00    0.00    0.00   93.40
 * 01:46:07       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
 * 01:46:07       3  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:07       4  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:07       5  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:07       6  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00 
 *  
 * 01:46:29     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 * 01:46:30     all   86.10    0.00    0.12    0.00    0.00    1.48    0.00    0.00    0.00   12.30
 * 01:46:30       0  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:30       1  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:30       2    0.00    0.00    0.89    0.00    0.00   10.71    0.00    0.00    0.00   88.39
 * 01:46:30       3  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:30       4  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:30       5  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:30       6  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:30       7  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 
 * 01:46:55     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
 * 01:46:56     all  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:56       0  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:56       1  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:56       2  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:56       3  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:56       4  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:56       5  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:56       6  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
 * 01:46:56       7  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  
 *  
 * -----------------------------------------------------------------------------------------------------------
 * 2. To show CPU and Memory utilization per process : ps aux 
 * 
 * The execution sequence for the program been taken as: ./a.out 2 8
 * 
 * From the outputs shown below, we observe how the the CPU and memory utilization gradually increases with 
 * time while the code is being executed, and then finally dropping to 0.0 after execution is complete.
 * 
 * [Note: we have excluded the unnecessary processes to keep the comment size concise.]
 * 
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * root         1  0.0  0.0   1312   856 ?        Sl   19:51   0:01 /init
 * root       510  0.0  0.0    896    80 ?        Ss   20:11   0:00 /init
 * root       511  0.0  0.0    896    80 ?        S    20:11   0:00 /init
 * soumitri   512  0.0  0.1  26236  8380 pts/1    Ss+  20:11   0:00 -bash
 * root       785  0.0  0.0    904    88 ?        Ss   20:16   0:00 /init
 * root       786  0.0  0.0    904    88 ?        S    20:16   0:00 /init
 * soumitri   787  0.0  0.1  26236  8280 pts/0    Ss   20:16   0:00 -bash
 * soumitri  1709  0.0  0.0  13316  3144 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1734  0.0  0.0  40096  3588 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3144 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 55.0  0.8 2103856 56024 pts/1   R+   20:42   0:00 ./a.out 2 8
 * soumitri  1737  0.0  0.0  40096  3492 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3144 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 78.0  2.6 2103856 170712 pts/1  R+   20:42   0:01 ./a.out 2 8
 * soumitri  1739  0.0  0.0  40096  3600 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3144 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 85.3  4.4 2103856 287448 pts/1  R+   20:42   0:02 ./a.out 2 8
 * soumitri  1741  0.0  0.0  40096  3520 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3144 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 89.2  6.4 2103856 412376 pts/1  R+   20:42   0:03 ./a.out 2 8
 * soumitri  1743  0.0  0.0  40096  3580 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3144 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 91.4  8.2 2103856 529112 pts/1  R+   20:42   0:04 ./a.out 2 8
 * soumitri  1745  0.0  0.0  40096  3552 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3144 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 93.0 10.1 2103856 649944 pts/1  R+   20:42   0:05 ./a.out 2 8
 * soumitri  1747  0.0  0.0  40096  3560 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3148 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 94.8 13.9 2103856 893656 pts/1  R+   20:42   0:07 ./a.out 2 8
 * soumitri  1751  0.0  0.0  40096  3512 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3148 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 95.4 15.8 2103856 1016536 pts/1 R+   20:42   0:08 ./a.out 2 8
 * soumitri  1753  0.0  0.0  40096  3552 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3148 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 96.3 19.6 2103856 1256152 pts/1 R+   20:42   0:10 ./a.out 2 8
 * soumitri  1757  0.0  0.0  40096  3548 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3148 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 96.7 21.5 2103856 1379032 pts/1 R+   20:42   0:11 ./a.out 2 8
 * soumitri  1759  0.0  0.0  40096  3504 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3148 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 97.0 23.3 2103856 1493720 pts/1 R+   20:42   0:12 ./a.out 2 8
 * soumitri  1761  0.0  0.0  40096  3580 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3148 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 97.6 28.9 2103856 1856216 pts/1 R+   20:42   0:15 ./a.out 2 8
 * soumitri  1767  0.0  0.0  40096  3516 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3148 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736 98.0 32.7 2103856 2097880 pts/1 R+   20:42   0:17 ./a.out 2 8
 * soumitri  1771  0.0  0.0  40096  3564 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * soumitri  1709  0.0  0.0  13316  3148 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1736  135 32.7 2169424 2098576 pts/1 Sl+  20:42   0:25 ./a.out 2 8
 * soumitri  1781  0.0  0.0  40096  3596 pts/0    R+   20:42   0:00 ps -aux
 *
 * USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
 * root         1  0.0  0.0   1312   856 ?        Sl   19:51   0:01 /init
 * root       510  0.0  0.0    896    80 ?        Ss   20:11   0:00 /init
 * root       511  0.0  0.0    896    80 ?        S    20:11   0:00 /init
 * soumitri   512  0.0  0.1  26236  8380 pts/1    Ss+  20:11   0:00 -bash
 * root       785  0.0  0.0    904    88 ?        Ss   20:16   0:00 /init
 * root       786  0.0  0.0    904    88 ?        R    20:16   0:00 /init
 * soumitri   787  0.0  0.1  26236  8280 pts/0    Ss   20:16   0:00 -bash
 * soumitri  1709  0.0  0.0  13316  3148 pts/0    S+   20:42   0:00 /bin/bash ./script.sh
 * soumitri  1783  0.0  0.0  40096  3492 pts/0    R+   20:42   0:00 ps -aux
 * 
 * -----------------------------------------------------------------------------------------------------------
 * 3. To show the running threads (using process listing command) : ps -eLf
 * 
 * The execution sequence for the code been taken as: ./a.out 2 8
 * 
 * From the outputs shown below, we observe that 8 child threads, each having distinct thread IDs (LWP values) 
 * have been created, all having same process ID (=2436), as well as the pecentage of CPU utilized by each of 
 * them (shown in the 'C' column).
 * 
 * [Note: we have excluded the unnecessary processes/threads to keep the comment size concise.]
 * 
 * UID         PID  PPID   LWP  C NLWP STIME TTY          TIME CMD
 * soumitri  2429   787  2429  0    1 20:58 pts/0    00:00:00 /bin/bash ./script.sh
 * soumitri  2436   512  2436 99    1 20:58 pts/1    00:00:16 ./a.out 2 8
 * soumitri  2469  2429  2469  0    1 20:58 pts/0    00:00:00 ps -eLf
 *
 * UID         PID  PPID   LWP  C NLWP STIME TTY          TIME CMD
 * soumitri  2429   787  2429  0    1 20:58 pts/0    00:00:00 /bin/bash ./script.sh
 * soumitri  2436   512  2436 93    9 20:58 pts/1    00:00:16 ./a.out 2 8
 * soumitri  2436   512  2471 98    9 20:58 pts/1    00:00:00 ./a.out 2 8
 * soumitri  2436   512  2472 98    9 20:58 pts/1    00:00:00 ./a.out 2 8
 * soumitri  2436   512  2473 98    9 20:58 pts/1    00:00:00 ./a.out 2 8
 * soumitri  2436   512  2474 99    9 20:58 pts/1    00:00:00 ./a.out 2 8
 * soumitri  2436   512  2475 98    9 20:58 pts/1    00:00:00 ./a.out 2 8
 * soumitri  2436   512  2476 98    9 20:58 pts/1    00:00:00 ./a.out 2 8
 * soumitri  2436   512  2477 98    9 20:58 pts/1    00:00:00 ./a.out 2 8
 * soumitri  2436   512  2478 98    9 20:58 pts/1    00:00:00 ./a.out 2 8
 * soumitri  2479  2429  2479  0    1 20:58 pts/0    00:00:00 ps -eLf
 *
 * UID         PID  PPID   LWP  C NLWP STIME TTY          TIME CMD
 * soumitri  2429   787  2429  0    1 20:58 pts/0    00:00:00 /bin/bash ./script.sh
 * soumitri  2481  2429  2481  0    1 20:58 pts/0    00:00:00 ps -eLf
 * 
 * -----------------------------------------------------------------------------------------------------------
 **/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

// macro to define the maximum possible value for unsigned char
#define UCHAR_MAX 255

/* to define constant for conversion from GB to bytes. Note that this
value is greater than 10^9 (3e9 caused the present system to hang up)
*/
long MIN_ARR_SIZE = 1024 * 1024 * 1024;

long NUM_CPUS; // constant to store the number of available CPUs in the system

unsigned char global_minimum = UCHAR_MAX; // initializing the global minimum variable
pthread_mutex_t mutex_global;             // declaring the mutex variable

// to obtain the current thread index
int step = 0;

// structure to store attributes of array
struct arrayInfo
{
    unsigned char *arr; // stores the numerical array
    long segmentSize;   // stores the segment size to be operated by a thread
    long currentIndex;  // to store the current thread index during execution
    long size;          // to store length of the array
    int num_threads;    // constant to store the number of threads
};

/* utility function to find minimum between two numbers */
int min(int a, int b)
{
    return a < b ? a : b;
}

/* utility function to find maximum between two numbers */
int max(int a, int b)
{
    return a > b ? a : b;
}

/* utility function that finds minimum in a given segment of the array for the current thread using mutex lock */
void *findMin(void *arg)
{
    //type cast to defined structure from void pointer
    struct arrayInfo *args = (struct arrayInfo *)arg;

    args->currentIndex = step++; // obtaining the current thread index

    // defining start and end points of the current sequence
    long start = args->currentIndex * args->segmentSize;
    long end = start + args->segmentSize;

    // for the last segment we search till the end of the array
    if (step == args->num_threads)
        end = args->size;

    // obtaining the local minimum of the segment
    int local_min = args->arr[start];
    for (long i = start; i < end; i++)
    {
        local_min = min(local_min, args->arr[i]);
    }

    // locking the mutex to avoid race condition on the shared global_minimum variable
    pthread_mutex_lock(&mutex_global);

    // updating the global minimum after mutex lock
    global_minimum = min(global_minimum, local_min);

    // unlock the mutex after updating the shared resource
    pthread_mutex_unlock(&mutex_global);

    pthread_exit(NULL);
}

/* main method */
int main(int argc, char **argv)
{
    // checking if correct number of arguments were passed
    if (argc != 3)
    {
        perror("Incorrect arguments passed -- arguments should be %s [size_of_array] [number_of_threads]\n");
        exit(1);
    }

    // obtaining the arguments passed by the user
    int size = atoi(argv[1]), num_threads = atoi(argv[2]);

    // obtaining the number of available CPUs in the system
    NUM_CPUS = sysconf(_SC_NPROCESSORS_ONLN);

    // checking validity of arguments passed
    if (size <= 0)
    {
        perror("Enter valid size of array\n");
        exit(1);
    }

    // thresholding the number of threads so that it does not exceed the number of available CPUs
    num_threads = min(NUM_CPUS, max(1, num_threads));

    // argument structure to be sent while creating threads
    struct arrayInfo args;

    // computing the actual length of the array and assigning the attributes
    args.size = MIN_ARR_SIZE * size;
    args.num_threads = num_threads;

    //storing size of each segment to be worked upon by the threads
    args.segmentSize = args.size / args.num_threads;

    // declaring the numerical array of the computed size
    args.arr = (unsigned char *)malloc(args.size * sizeof(unsigned char));

    srand(time(0)); // setting seed for random number generation, the numbers will be different for every run of the program

    // initializing the array using random numbers
    for (long i = 0; i < args.size; i++)
    {
        args.arr[i] = (unsigned char)(rand() % 256); // in range [0, 255] i.e. unsigned char
    }

    /* code relevant to multithreading starts here */

    pthread_t threads[num_threads]; // declaring the threads for multithreading
    pthread_attr_t attr;            // declaring thread attribute

    // mutex initialization
    if (pthread_mutex_init(&mutex_global, NULL) != 0)
    {
        perror("Error in initializing mutex lock on global_minimum\n");
        exit(1);
    }

    // thread attribute initialization
    if (pthread_attr_init(&attr) != 0)
    {
        perror("Error in initializing thread attribute\n");
        exit(1);
    }

    // initialising variables for evaluating execution time
    struct timeval start_time, end_time;
    double time_taken;

    // start timer
    gettimeofday(&start_time, NULL);

    // creating the threads and calling findMin(void *) to find the minimum of each segment
    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], &attr, findMin, (void *)&args);
    }

    // waiting for the threads to complete their execution
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // end timer
    gettimeofday(&end_time, NULL);

    // evaluate execution time
    time_taken = (end_time.tv_sec - start_time.tv_sec);
    time_taken += (end_time.tv_usec - start_time.tv_usec) * 1e-6;

    // print the global minimum value of the array
    printf("global minimum element = %d\n", global_minimum);

    // print the time taken to find this minimum value
    printf("Time taken to find minimum element using %d threads = %6f seconds\n\n", num_threads, time_taken);

    return 0;
}