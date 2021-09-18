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
    char* str = NULL;
    int len = 0;
    char end_char; 
    int isNumeric(char);  

%}

%%

.*\-\r$      { return 0; }
.*@.*\.\-.*  { return 0; }
.*@.*\-\..*  { return 0; }
([a-zA-Z0-9!#\$%&'\*\+\-/=\?\^_`\{\|\}~])+(\.?[a-zA-Z0-9!#\$%&'\*\+\-/=\?\^_`\{\|\}~]+)*@[a-zA-Z0-9]+(\-*[a-zA-Z0-9]+)*\.[a-zA-Z0-9\-\.]+ { str = yytext; len = yyleng; return 1; }
.* { return 0; }

%%

int yywrap(){}

int main()
{
    printf("Enter the Email ID: ");
    int ret_flag = yylex();
    int valid_flag = 0;

    end_char = str[len-1];
    
    if(end_char == '-')
    ret_flag = 0;

    if(ret_flag == 1)
    {
        int i = len-1;
        while(str[i]!='.')
        {
            if(!isNumeric(str[i]))
            {
                printf("Email ID is Valid\n"); 
                valid_flag=1;
                break;
            }

            i--;
        } 

        if(valid_flag==0)
        {
            printf("Email ID is Invalid\n");
        }
    }

    else
    {
        printf("Email ID is Invalid\n");
    }

      return 0;
}

int isNumeric(char ch)
{
    return (ch >= '0') && (ch <= '9');

}