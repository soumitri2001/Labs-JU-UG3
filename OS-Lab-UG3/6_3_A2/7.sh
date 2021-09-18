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
#  * Assignment No. : 3  |  Question: 7
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details:  Write a shell script to count number of files in a directory.
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: chmod +x 7.sh
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence:  ./7.sh
#  * ------------------------------------------------------------------------------------------------------------------
#    Output: 
#    Current working directory: 
#    /home/soumitri/OS-Lab-UG3/6_3_A2
#    Nos of files in this directory: 
#    15
#
#  */

echo "Current working directory: "
pwd

echo "Nos of files in this directory: "
ls -1 | wc -l