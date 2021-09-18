#!/usr/bin/bash

# /**
#  * Group No.: 6 (Batch-A2)
#  * Group Members : 1) Sk Asif      -- Roll No. 64
#  *                 2) Sagnik Haldar -- Roll No. 74
#  *                 3) Soumitri Chattopadhyay -- Roll No. 83
#  * 
#  * Dept : Information Technology
#  * Year : 3rd Year 1st Semester
#  * Subject: Operating Systems Lab
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment No. : 3  |  Question: 12
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details:  Find all files that have been modified 30 minutes ago
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: chmod +x 12.sh
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence:  ./12.sh
#  * ------------------------------------------------------------------------------------------------------------------
    #  Output: 
    #   sagnik@LAPTOP-I58N2SVI:~/OSLab/ass3$ ./12.sh
    #   46847      4 -rwxr-xr-x   1 sagnik   sagnik       1183 Sep 10 00:07 ./12.sh
    #   46849      4 -rwxr-xr-x   1 sagnik   sagnik       1567 Sep 10 00:04 ./14.sh
    #   46839      4 -rwxr-xr-x   1 sagnik   sagnik       1287 Sep 10 00:01 ./11.sh
    #   46848      4 -rwxr-xr-x   1 sagnik   sagnik       1385 Sep 10 00:06 ./13.sh
#  */

find . -type f -mmin -30 -ls