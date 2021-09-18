/* Name: Soumitri Chattopadhyay
Roll: 001911001083
Year: UG-3 (5th Semester)
Subject: Compiler Lab Assignment 1

Question 9:
Write a Lex Program that will validate a password.A password is correct if it contains:
a. At least 1 uppercase character
b. At least 1 lowercase character
c. At least 1 digit
d. At least 1 of these special character ~`!@#$%^&*()_-+={[}]|\:;"'<,>.?/
e. Minimum length 8 (characters). Maximum length 15 (characters)
*/

/*definition*/
%{
    int cnt_lowercase = 0;
    int cnt_uppercase = 0;
    int cnt_digits = 0;
    int cnt_splchar = 0;
    int pass_len = 0;
%}

/*rules*/
%%


[a-z]    { cnt_lowercase++; }
[A-Z]    { cnt_uppercase++; }
[0-9]    { cnt_digits++; }
[~`!@#$%^&*()_+={[}|\:;"'<,>.?/-]  { cnt_splchar++; }
.|[\n] {;}  // ignore all other characters

%%

int yywrap(){}

int main(int argc, char **argv){

    printf("Enter the password : ");
    yylex();
    
    printf("Nos of uppercase characters: %d\n", cnt_uppercase);
    printf("Nos of lowercase characters: %d\n", cnt_lowercase);
    printf("Nos of special characters : %d\n", cnt_splchar);
    printf("Nos of digits : %d\n",cnt_digits);
    
    /* check validity of password */

    if (cnt_uppercase>0 && cnt_lowercase>0 && cnt_digits>0 && cnt_splchar>0) {
        pass_len = cnt_lowercase + cnt_uppercase + cnt_digits + cnt_splchar;
        if (pass_len>= 8 && pass_len <= 15)
            printf("Password Validated !\n");
    }
    else
        printf("Password NOT valid, please try again.\n");

    return 0;
}