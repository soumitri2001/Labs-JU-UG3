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
#  * Assignment No. : 3  |  Question: 1
#  * ------------------------------------------------------------------------------------------------------------------
#  * Assignment Details:  Write a shell script that accepts a file name starting and ending line 
#                         numbers as arguments and display all the lines between given line no.
#  * ------------------------------------------------------------------------------------------------------------------
#  * Compilation sequence: chmod +x 1.sh
#  * ------------------------------------------------------------------------------------------------------------------
#  * Execution sequence:  ./1.sh
#  * ------------------------------------------------------------------------------------------------------------------
    #  Output: 
    #     soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3/6_3_A2$ chmod +x 1.sh
    #     soumitri@LAPTOP-48UB98QH:~/OS-Lab-UG3/6_3_A2$ ./1.sh
    #     enter the filename
    #     TextFile_1.txt
    #     enter the starting line number
    #     2
    #     enter the ending line number
    #     6
    #     Output file contents: 
    #     molestiae quas vel sint commodi repudiandae consequuntur voluptatum laborum
    #     numquam blanditiis harum quisquam eius sed odit fugiat iusto fuga praesentium
    #     optio, eaque rerum! Provident similique accusantium nemo autem. Veritatis
    #     obcaecati tenetur iure eius earum ut molestias architecto voluptate aliquam
    #     nihil, eveniet aliquid culpa officia aut! Impedit sit sunt quaerat, odit,
#  */

echo "enter the filename"
read fname

echo "enter the starting line number"
read s

echo "enter the ending line number"
read n

sed -n $s,$n\p $fname | cat > output_1.txt

echo "Output file contents: "
cat output_1.txt