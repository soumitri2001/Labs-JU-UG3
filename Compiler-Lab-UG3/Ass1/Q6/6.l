/* Name: Soumitri Chattopadhyay
Roll: 001911001083
Year: UG-3 (5th Semester)
Subject: Compiler Lab Assignment 1

Question 6:
Write a program to convert a simple arithmetic Expression from Infix to Postfix.
*/
 
%{
    int getPrecedence(char c);
    char postfix[256];
    int top = -1;
%}

%%

[A-Za-z]*           { printf("%s ", yytext); }
[-\+\*\/\(\)\^]       {
                        char c = yytext[0];

                        if(top == -1 || c == '('){
                            postfix[++top] = c;
                        }
                        else if(c == ')'){
                            while(postfix[top] != '('){
                                printf("%c ", postfix[top]);
                                top--;
                            }
                            top--;
                        }
                        else if(getPrecedence(c) > getPrecedence(postfix[top])){
                            postfix[++top] = c;
                        }
                        else{
                            while(top != -1 && getPrecedence(postfix[top]) >= getPrecedence(c)){
                                printf("%c ", postfix[top]);
                                top--;
                            }
                            postfix[++top] = c;
                        }
                    } 

[\n]                {
                        while(top != -1){
                            printf("%c ", postfix[top--]);
                        }
                    }

.|[\s]                 {;}

%%

int yywrap(){}

int getPrecedence(char c){
    switch(c){
        case '^':
            return 3;
        case '/': case '*':
            return 2;
        case '+': case '-':
            return 1;
        default:
            return -1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    char infix[256];

    printf("Enter the infix expression : ");
    yylex();
    printf("\n");
    return 0;
}