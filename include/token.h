#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenType{
    INT_CONST,
    OPERATOR
} TokenType;

typedef enum OparetorType{
    ADD, SUB, MUL, DIV
}OparetorType;

typedef struct token {
    TokenType   type;
    int         data;
} token;

int consumeNumber(char** ptr, token* result);

void printTokens(token* tokens, int size);

#endif