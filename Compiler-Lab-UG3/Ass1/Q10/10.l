/* Name: Soumitri Chattopadhyay
Roll: 001911001083
Year: UG-3 (5th Semester)
Subject: Compiler Lab Assignment 1

Question 10:
Write a Lex Program that will validate an Email address. Formatof an email address is local-part@domainLocal part of the Email address may use any of these ASCIICharacters:a.uppercase and lowercase letters A to Z and a to zb.digits, 0 to 9c.Printable characters, !#$%&'*+-/=?^_`{|}~
d.dot ., provided that it is not the first or last characterand provided also that it does not appear consecutively (e.g.,John..Doe@example.com is not allowed)The domain name part of an email address has to conform to strictguidelines:
a.uppercase and lowercase letters A to Z and a to z;b.digits 0 to 9, provided that top-level domain names are notall-numeric;c.hyphen -, provided that it is not the first or end_character.
Example:example-indeed@strange-example.com (allowed).A@b@c@example.com (not allowed -only one @ is allowedoutside quotation marks)
*/


%{
    int valid_flag = 0;
%}

%%

.*\.[0-9]+\r*\n*        { printf("All characters of domain : digits. \n"); yyterminate(); }
.*@-.*\r*\n*|.*-\r*\n*  { printf("Starting/ending character of domain : '-' \n"); yyterminate(); }
.*@.*\-\..*\r*\n*       { printf("Ending character of domain : '-' \n"); yyterminate(); }
.*@.*\.-.*\r*\n*        { printf("Starting of top level : '-' \n"); yyterminate(); }
.*@\..*\r*\n*           { printf("First character of domain : '.' \n"); yyterminate(); }
.*\.\..*\r*\n*          { printf("Email contains '..' \n"); yyterminate();}
.*\.@.*\r*\n*           { printf("Ending character of local part is '.' \n"); yyterminate(); }
\..*\r*\n*              { printf("Starting character of email ID is '.' \n"); yyterminate(); }

[a-zA-Z0-9!#\$%&'\*\+\-\/=\?\^_`\{\|\}~]+@([a-zA-Z0-9\-]+\.)+[a-zA-Z0-9\-]+\r*\n* { valid_flag = 1; }

.*  { printf("Invalid Email ID\n"); yyterminate(); return 1; }

%%              

int yywrap(){}

int main(int argc, char **argv)
{
    printf("Enter Email ID: ");
    yylex();

    if (valid_flag == 1)
        printf("The email ID is valid.\n");
    else   
        printf("The email ID is not valid.\n");

    return 0;
} 