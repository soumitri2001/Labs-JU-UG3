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
#  * Assignment No. : 3  |  Question: 14
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details:  Count the number of occurrences of “{“ and “}” in a given .c file
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: chmod +x 14.sh
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence:  ./14.sh
#  * ------------------------------------------------------------------------------------------------------------------
    #  Output: 
    #   sagnik@LAPTOP-I58N2SVI:~/OSLab/ass3$ chmod +x 14.sh
    #   sagnik@LAPTOP-I58N2SVI:~/OSLab/ass3$ ./14.sh
    #   Enter file name : 1.c
    #   Number of occurances of { or } in file 1.c : 2
#  */

echo -n "Enter file name : "
read FILE

if [ -f "$FILE" ]
then
    echo -n "Number of occurances of { or } in file $FILE : "
    grep -o '\{\|\}' $FILE | wc -l
else
    echo "$FILE does not exist"
fi