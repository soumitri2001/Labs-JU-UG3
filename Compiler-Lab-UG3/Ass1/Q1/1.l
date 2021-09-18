/* Name: Soumitri Chattopadhyay
Roll: 001911001083
Year: UG-3 (5th Semester)
Subject: Compiler Lab Assignment 1

Question 1:
Write a program to counts number of vowels and consonants in given string.Then findwhich vowels occur how many times.
 */

%{
    int cnt_a=0;
    int cnt_e=0;
    int cnt_i=0;
    int cnt_o=0;
    int cnt_u=0;
    int cnt_vow=0;
    int cnt_cons=0;
%}

%%

[aA] {cnt_a++; cnt_vow++;}
[eE] {cnt_e++; cnt_vow++;}
[iI] {cnt_i++; cnt_vow++;}
[oO] {cnt_o++; cnt_vow++;}
[uU] {cnt_u++; cnt_vow++;}
[a-zA-Z] {cnt_cons++;}
.|[\n] {;} // other characters to be ignored 

%%

int yywrap(){}

int main(int argc, char** argv) 
{
    printf("Enter any string: ");
    yylex();
    printf("The No of A/a's = %d\n",cnt_a);
    printf("The No of E/e's = %d\n",cnt_e);
    printf("The No of I/i's = %d\n",cnt_i);
    printf("The No of O/o's = %d\n",cnt_o);
    printf("The No of U/u's = %d\n",cnt_u);
    printf("The No of Consonants = %d\n",cnt_cons);
    return 0;
}