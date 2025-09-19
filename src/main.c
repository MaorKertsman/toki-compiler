#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "token.h"

typedef enum Error{
    MATH_SYNTEX_PROBLEM
}Error;


int tokenizeExpression(char* expression){
    char* ptr = expression - 1;
    token results[10];
    int tokenIndex = 0;

    while(*++ptr){
        switch (*ptr){
        case '+': results[tokenIndex++] = (token){OPERATOR, ADD}; break;
        case '-': results[tokenIndex++] = (token){OPERATOR, SUB}; break;
        case '*': results[tokenIndex++] = (token){OPERATOR, MUL}; break;
        case '/': results[tokenIndex++] = (token){OPERATOR, DIV}; break;
        default:
            if(!isdigit(*ptr)) {break;}
            if(consumeNumber(&ptr, &results[tokenIndex++])){return 1;}
        }
    }

    printTokens(results, 5);

    return 0;
}

int main(){
    char st[100];    
    fgets(st, 100, stdin);
    token tok;

    tokenizeExpression(st);
}




