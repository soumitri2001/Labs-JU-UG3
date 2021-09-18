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
#  * Assignment No. : 3  |  Question: 3
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details:  Write a shell script that receives any number of file names as arguments checks 
#                         if every argument supplied is a file or a directory and reports accordingly.
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: chmod +x 3.sh
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence:  ./3.sh
#  * ------------------------------------------------------------------------------------------------------------------
#  Output: 
#       soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3/6_3_A2$ chmod +x 3.sh
#       soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3/6_3_A2$ ./3.sh temp_dir temp_dir/temp_txt.txt
#       temp_dir is a directory
#       temp_dir/temp_txt.txt is  a file
#       Nos of lines in the file are: 
#       15 temp_dir/temp_txt.txt
#  */

for x in $*
do
if [ -f $x ]
then
echo "$x is  a file"
echo "Nos of lines in the file are: "
wc -l $x
elif [ -d $x ]
then
echo "$x is a directory"
else
echo "enter valid filename or directory name"
fi
done