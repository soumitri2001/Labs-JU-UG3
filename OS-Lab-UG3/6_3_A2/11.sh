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
#  * Assignment No. : 3  |  Question: 11
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details:  Create a directory “backup”. Make a soft link of all your .C files in this directory.
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: chmod +x 11.sh
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence:  ./11.sh
#  * ------------------------------------------------------------------------------------------------------------------
#  */

mkdir backup

i=1
for FILE in `ls *.c`
do
    ln -s /home/sagnik/OSLab/ass3/$FILE backup/"t${i}.c"
    let "i++"
done