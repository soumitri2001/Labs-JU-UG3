/* Name: Soumitri Chattopadhyay
Roll: 001911001083
Year: UG-3 (5th Semester)
Subject: Compiler Lab Assignment 1

Question 2:
Write a LEX program to count the number of Positive and negativeintegers and fractions. 
*/

%{
    int cnt_pos=0;
    int cnt_neg=0;
    int cnt_posfrac=0;
    int cnt_negfrac=0;
%}

%%

[0-9]+ {cnt_pos++;}
-?[0-9]+ {cnt_neg++;}
([0-9]+\.[0-9]+) {cnt_posfrac++;}
-?([0-9]+\.[0-9]+) {cnt_negfrac++;}


%%

int yywrap(){}

int main(int argc, char** argv) {
    printf("Enter numbers and fractions consecutively: ");
    yylex();
    printf("Nos of positive numbers: %d\n",cnt_pos);
    printf("Nos of positive fractions: %d\n",cnt_posfrac);
    printf("Nos of negative numbers: %d\n",cnt_neg);
    printf("Nos of negative fractions: %d\n",cnt_negfrac);
    return 0;
}