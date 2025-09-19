#include "token.h"
#include "ctype.h"
#include "stdio.h"


int consumeNumber(char** ptr, token* result){
    int buff = 0;

    while(**ptr){
        if(!isdigit(**ptr)){
            *result = (token){INT_CONST, buff};
            return 0;
        }
        buff = buff * 10 + ((**ptr) - '0');
        (*ptr)++;
    }
    return 1;
}

void printTokens(token* tokens, int size){
    for(int i = 0; i < size; i++){
        printf("<type = %d, data = %d>\n", tokens[i].type, tokens[i].data);
    }
}