#include "token.h"
#include "ctype.h"
#include "stdio.h"


int consumeNumber(char** ptr, token* result){
    int buff = 0;

    while(**ptr){
        if(!isdigit(**ptr)){
            *result = (token){INT_CONST, buff};
            (*ptr)--;
            return 0;
        }
        buff = buff * 10 + ((**ptr) - '0');
        (*ptr)++;
    }

    return 1;
}


void printToken(token tok) {
    const char *typeNames[] = {"INT_CONST", "OPERATOR"};
    const char *opNames[]   = {"ADD", "SUB", "MUL", "DIV", "LEFT", "RIGHT"};

    printf("<type = %s,\t", typeNames[tok.type]);
    if (tok.type == INT_CONST) {
        printf("data = %d>\n", tok.data);
    } else if (tok.type == OPERATOR) {
        printf("data = %s>\n", opNames[tok.data]);
    }
}

int isRightPar(token token){
    if(token.type==OPERATOR && token.data==RIGHT){return 1;}
    return 0;
}

int isLeftPar(token token){
    if(token.type==OPERATOR && token.data==LEFT){return 1;}
    return 0;
}

int isMul(token token){
    if(token.type==OPERATOR && token.data==MUL){return 1;}
    return 0;
}

int isDiv(token token){
    if(token.type==OPERATOR && token.data==DIV){return 1;}
    return 0;
}

int isAdd(token token){
    if(token.type==OPERATOR && token.data==ADD){return 1;}
    return 0;
}

int isSub(token token){
    if(token.type==OPERATOR && token.data==SUB){return 1;}
    return 0;
}
