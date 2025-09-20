#include "tlist.h"
#include "token.h"
#include <stdlib.h>
#include <stdio.h>

int initTokenList(token tok, tNode** result){
    *result = malloc(sizeof(struct tNode));

    if (*result == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    (*result)->data = tok;
    (*result)->next = NULL;

    return 0;
}

int appendToken(tNode* root, token tok){
    tNode* p = root;
    
    while(p->next){ p=p->next; }
    if(initTokenList(tok, &p->next)){return 1;}
    return 0;
}

void printList(tNode* root){
    tNode* p = root; int i = 0;

    while(p){ 
        printf("(%d)\t", i);
        printToken(p->data);
        p=p->next; 
        i++;
    }
}

tNode* nodeAt(tNode* root, int i){
    tNode* p = root;

    while(i-- && p->next){
        p=p->next;
    }

    return p;
}

void freeList(tNode* root) {
    while (root) {
        tNode* nxt = root->next;
        free(root);
        root = nxt;
    }
}

int connect(tNode* root, token between, int leftCon, int rightCon){
    tNode* rightP = nodeAt(root, rightCon);
    tNode* leftP = nodeAt(root, leftCon);
    tNode* next = rightP->next;
    rightP->next = NULL;

    freeList(leftP->next);
    leftP->data = between;
    leftP->next = next;

    return 0;
}