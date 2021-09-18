/* Name: Soumitri Chattopadhyay
Roll: 001911001083
Year: UG-3 (5th Semester)
Subject: Compiler Lab Assignment 1

Question 5:
Write a LEX program to count and identify the operators and identifiers from a valid arithmetic expression.Print them separately.
*/

%{
    int operators_count = 0;
    int identifiers_count = 0;
    char operators[100][100] = {0};
    char identifiers[100][100] = {0};
%}

%%

[-\+\*\/\%][=]?|[=]     { strcpy(operators[operators_count++], yytext);}
[a-zA-Z_][a-zA-Z0-9_]*  { strcpy(identifiers[identifiers_count++], yytext);}
.|[\n]                  {;}

%%

int yywrap(){}

int main(){
    printf("Enter valid expression : ");
    yylex();

    printf("Operators : \n");
    operators_count--;
    while(operators_count >= 0){
        printf("%s\n", operators[operators_count--]);
    }

    printf("\nIdentifiers : \n");
    identifiers_count--;
    while(identifiers_count >=0 ){
        printf("%s\n", identifiers[identifiers_count--]);
    }
    return 0;
}

