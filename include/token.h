#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenType{
    INT_CONST,
    OPERATOR
} TokenType;

typedef enum OparetorType{
    ADD, SUB, MUL, DIV, LEFT, RIGHT
}OparetorType;

typedef struct token {
    TokenType   type;
    int         data;
} token;

int consumeNumber(char** ptr, token* result);

void printToken(token token);

int isLeftPar(token token);

int isRightPar(token token);

int isMul(token token);

int isDiv(token token);

int isAdd(token token);

int isSub(token token);


#endif