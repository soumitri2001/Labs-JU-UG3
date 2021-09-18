/* Name: Soumitri Chattopadhyay
Roll: 001911001083
Year: UG-3 (5th Semester)
Subject: Compiler Lab Assignment 1

Question 7:
Write a program to take one file as input, the file with some identifiers, 
store the identifiers in a table (using hashing) if not available; give error message if it is already present.
*/

%{
    #define MAXLEN 256
    void hashing(char *s, int len);
    int hashCode(char *s, int len);
    char hashTable[MAXLEN][100] = {0};
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*  { hashing(yytext, yyleng); }
.|[\n]                  {;}

%%

int yywrap(){}

void hashing(char *s, int len) {
    int hcode = hashCode(s, len);
    for(int i=0;i<MAXLEN;i++){
        int idx = (hcode+i) % MAXLEN;
        if(hashTable[idx][0] == 0){
            strcpy(hashTable[idx], s);
            printf("%s added to hash index %d\n", s, idx);
            return;
        }

        if(strcmp(hashTable[idx], s) == 0){
            printf("ERROR :- %s string already present in the hash table.\n", s);
            return;
        }
    }
    printf("Hash table is full!\n");
}

int hashCode(char *s, int len){
    int hcode = 31;
    for(int i=0;i<len;i++){
        hcode = (hcode + 31 * s[i]) % MAXLEN;
    }
    return hcode;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Incorrect number of arguments given.\n");
        return 1;
    }
    yyin = fopen(argv[1],"r");
    yylex();
    return 0;
}