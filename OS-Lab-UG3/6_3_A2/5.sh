#!/bin/bash

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
#  * Assignment No. : 3  |  Question: 5
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details:  Write a shell script that accept a list of file names as arguments count and report  
#                         the occurrence of each word.
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: chmod +x 5.sh
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence:  ./5.sh temp_dir/dummy.txt temp_dir/dummy1.txt temp_dir/dummy2.txt
#  * ------------------------------------------------------------------------------------------------------------------
#    Output: 
    #  15 and
    #  12 randomness
    #   9 variety
    #   9 used
    #   9 random
    #   9 purposes
    #   9 of
    #   9 numbers
    #   9 have
    #   9 been
    #   9 a
    #   6 traditionally
    #   6 for
#  */

touch concat.txt

for file in "$@"; do
    cat $file >> concat.txt
done

cat concat.txt | tr '[:upper:]' '[:lower:]'  | tr '[:space:]' '[\n*]' | tr '[:punct:]' '[\n*]' | grep -v "^\s*$" | sort | uniq -c | sort -bnr
