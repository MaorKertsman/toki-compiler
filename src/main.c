#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "token.h"
#include "tlist.h"

typedef enum Error{
    MATH_SYNTEX_PROBLEM
}Error;


int tokenizeExpression(char* expression, tNode** root){
    char* ptr = expression;
    token temp;
    int tokenIndex = 0;

    // Init first token
    switch (*ptr){
        case '+': initTokenList((token){OPERATOR, ADD}, root); break;
        case '-': initTokenList((token){OPERATOR, SUB}, root); break;
        case '*': initTokenList((token){OPERATOR, MUL}, root); break;
        case '/': initTokenList((token){OPERATOR, DIV}, root); break;
        case '(': initTokenList((token){OPERATOR, LEFT}, root); break;
        case ')': initTokenList((token){OPERATOR, RIGHT}, root); break;
        default:
            if(!isdigit(*ptr)) {break;}
            if(consumeNumber(&ptr, &temp)){return 1;}
            initTokenList(temp, root);
        }
    
    while(*++ptr){
        switch (*ptr){
        case '+': appendToken(*root, (token){OPERATOR, ADD}); break;
        case '-': appendToken(*root, (token){OPERATOR, SUB}); break;
        case '*': appendToken(*root, (token){OPERATOR, MUL}); break;
        case '/': appendToken(*root, (token){OPERATOR, DIV}); break;
        case '(': appendToken(*root, (token){OPERATOR, LEFT}); break;
        case ')': appendToken(*root, (token){OPERATOR, RIGHT}); break;

        default:
            if(!isdigit(*ptr)) {break;}
            if(consumeNumber(&ptr, &temp)){return 1;}
            appendToken(*root, temp);
        }
    }
    
    return 0;
}


int findDeepestPars(tNode* root, int* firstRight, int* lastLeft){
    int i = 0;
    tNode* p = root;

    *firstRight = 0;
    *lastLeft = 0;

    while(p){
        if(isRightPar(p->data)){
            *firstRight = i;
            return 1;
        }
        if(isLeftPar(p->data)){
            *lastLeft = i;
        }
        p=p->next; i++;
    }
    return 0;
}

int findFirstMulOrDiv(tNode* tokens){
    int i = 0; tNode* p = tokens;

    while(p){
        if(isMul(p->data) || isDiv(p->data)){
            return i;
        }
        p=p->next; i++;
    }
    return -1;
}

int evaluateNaive(tNode* tokens){
    tNode* p = tokens; int i = 0;
    tNode* last;
    
    while(p){
        if(isAdd(p->data)){
            connect(tokens, (token){INT_CONST, last->data.data + p->next->data.data}, i-1, i+1);
            p=tokens; i=0; continue; 
        }
        if(isSub(p->data)){
            connect(tokens, (token){INT_CONST, last->data.data - p->next->data.data}, i-1, i+1);
            p=tokens; i=0; continue; 
        }
        last = p;
        p=p->next;
        i++;
    }
}

int evaluateMult(tNode* tokens){
    tNode* p = tokens; int i = 0;
    tNode* last;
    
    while(p){
        if(isMul(p->data)){
            connect(tokens, (token){INT_CONST, last->data.data * p->next->data.data}, i-1, i+1);
            p=tokens; i=0; continue; 
        }
        if(isDiv(p->data)){
            connect(tokens, (token){INT_CONST, last->data.data / p->next->data.data}, i-1, i+1);
            p=tokens; i=0; continue; 
        }
        last = p;
        p=p->next;
        i++;
    }
}

int evaluateWithoutPars(tNode* tokens, int from, int to){
    tNode* connectTo = nodeAt(tokens, from-1);
    tNode* left = connectTo->next;
    tNode* right = nodeAt(tokens, to);

    tNode* next = right->next;
    right->next = NULL;

    evaluateMult(left->next);
    evaluateNaive(left->next);

    left->next->next=next;
    connectTo->next = left->next;
    free(left);
}

int evaluate(tNode* tokens){
    int deepRight, deepLeft;
    

    while(findDeepestPars(tokens, &deepRight, &deepLeft)){
        evaluateWithoutPars(tokens, deepLeft, deepRight);
        printf("\n");
        printList(tokens);
    }
    evaluateMult(tokens);
    evaluateNaive(tokens);

    printf("\n");
    printList(tokens);
}


int main(){
    char prefix[] = "0 + ";
    char st[100];    
    fgets(st, 100, stdin);

    size_t len_prefix = strlen(prefix);
    size_t len_str = strlen(st);

    memmove(st + len_prefix, st, len_str + 1); 
    memcpy(st, prefix, len_prefix);

    tNode* tokens;

    tokenizeExpression(st, &tokens);
    printList(tokens);

    int firstRight, lastLeft;

    evaluate(tokens);
}




