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
#  * Assignment No. : 3  |  Question: 13
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details:  Find all files containing the word “main()”
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: chmod +x 13.sh
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence:  ./13.sh
#  * ------------------------------------------------------------------------------------------------------------------
    #  Output: 
    #   sagnik@LAPTOP-I58N2SVI:~/OSLab/ass3$ ./13.sh
    #   1.c:int main() 
    #   13.sh:#  * Assignment Details:  Find all files containing the word “main()”
    #   13.sh:grep -r 'main()' *
    #   2.c:int main() {
#  */

grep -r 'main()' *