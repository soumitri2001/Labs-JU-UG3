/* Name: Soumitri Chattopadhyay
Roll: 001911001083
Year: UG-3 (5th Semester)
Subject: Compiler Lab Assignment 1

Question 8:
Implement 'wc' command of LINUX system (i.e., count number of characters, words and lines in a file). 
Also implement 'mwc' (multiple file names in wc command)
*/

%{
  int cnt_words = 0;  
  int cnt_lines = 0;
  int word_flag = 0;
  int cnt_char = 0;
%}

%%

\n          { word_flag = 0; ++cnt_lines; ++cnt_char;}
[ \t\f\r]   { word_flag = 0; ++cnt_char; }
.           { ++cnt_char; if(word_flag == 0) { ++cnt_words; word_flag = 1; }}

%%

int yywrap(){}

int main(int agrc, char **argv){

  yyin = fopen(argv[1],"r");  
  yylex();
  printf("Nos of words : %d\n", cnt_words);
  printf("Nos of lines : %d\n", cnt_lines);
  printf("Nos of characters : %d\n", cnt_char);
        
  return 0;
}
