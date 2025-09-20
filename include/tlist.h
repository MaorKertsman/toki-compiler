#ifndef TLIST_H
#define TLIST_H

#include "token.h"

typedef struct tNode {
    token   data;
    struct tNode*  next;
} tNode;

int initTokenList(token tok, tNode** result);

int appendToken(tNode* root, token tok);

void printList(tNode* root);

void freeList(tNode* root); 

tNode* nodeAt(tNode* root, int i);

int connect(tNode* root, token between, int leftCon, int rightCon);

#endif