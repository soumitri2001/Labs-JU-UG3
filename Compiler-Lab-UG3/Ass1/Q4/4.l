/* Name: Soumitri Chattopadhyay
Roll: 001911001083
Year: UG-3 (5th Semester)
Subject: Compiler Lab Assignment 1

Question 4:
write a LEX program to count the no of ‘scanf’ and ‘printf’statements in agiven C program. 
Replace them with ‘readf’ and ‘writef’statements respectively. 
*/

%{
    int cnt_scanf=0;
    int cnt_printf=0;
%}

%%

"scanf" {cnt_scanf++; fprintf(yyout, "readf");}
"printf" {cnt_printf++; fprintf(yyout, "writef");}

%%

int yywrap(){}

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("Incorrect number of arguments given.");
        return 1;
    }
    FILE* orig_file = fopen(argv[1], "r");
    if(orig_file==NULL) {
        printf("Error in opening original file");
        return 1;
    }

    yyin = orig_file;

    FILE* new_file = fopen(argv[2], "w");
    if(new_file==NULL) {
        printf("Error in opening new file");
        return 1;
    }

    yyout = new_file;

    yylex();

    printf("Nos of scanf in %s is: %d\n", argv[1], cnt_scanf);
    printf("Nos of printf in %s is: %d\n", argv[2], cnt_printf);

    printf("New file saved at %s\n", argv[2]);

    return 0;
}

