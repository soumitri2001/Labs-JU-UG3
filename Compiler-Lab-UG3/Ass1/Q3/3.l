/* Name: Soumitri Chattopadhyay
Roll: 001911001083
Year: UG-3 (5th Semester)
Subject: Compiler Lab Assignment 1

Question 3:
Write a LEX program to count the total numbers ofwordsand numbers of linespresents incomment lines in a given C program. 
Also eliminate them and copy that program into separate file.
*/

%{
    int cnt_words=0;
    int word_flag = 0;
    int cnt_lines=0;
%}

%s MULTICOMMENT
%s SINGLECOMMENT

%%
"/*" {BEGIN MULTICOMMENT;}
"//" {BEGIN SINGLECOMMENT;}
<SINGLECOMMENT>[\n] {BEGIN(0); cnt_lines++; word_flag = 0;}
<MULTICOMMENT>[\n] {cnt_lines++; word_flag = 0;}
<MULTICOMMENT>"*/" {cnt_lines++; BEGIN(0); word_flag = 0;}
<SINGLECOMMENT,MULTICOMMENT>[^\t\f\r ] {if(word_flag == 0) {cnt_words++; word_flag = 1;} }
<SINGLECOMMENT,MULTICOMMENT>[\t\f\r ] {word_flag = 0;}

.|\n {fprintf(yyout,"%s",yytext);}
%%

int yywrap(){}

int main(int argc, char **argv){

    yyin = fopen(argv[1],"r");
    yyout = fopen(argv[2],"w");
    yylex();
    printf("Nos of comment lines are : %d\n", cnt_lines);
    printf("Nos of comment words are : %d\n", cnt_words);
    return 0;

}