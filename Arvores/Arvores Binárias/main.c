#include<stdio.h>
#include<stdlib.h>


struct no{
    int val;
    struct no *esq;
    struct no *dir;
}no;
typedef struct no No;

No *MoreRLoMoreLR(No *raiz){
    No *atual= raiz;
    while(atual && atual->esq != NULL)
        atual=atual->esq;
    return atual;
}
No *removeNo(No *raiz, int item){
    if(item < raiz->val){
        raiz->esq = removeNo(raiz->esq, item);
    }else if (item > raiz->val){
        raiz->dir = removeNo(raiz->dir, item);
    }
    else{
        if(raiz->esq == NULL){
            No *temp = raiz->dir;
            free(raiz);
            return temp;
        }else if (raiz->dir == NULL){
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        No *temp = MoreRLoMoreLR(raiz->dir);
        raiz->val = temp->val;
        raiz->dir = removeNo(raiz->dir, temp->val);
    }
    return raiz;

}

No *novoNo(int item){
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->val = item;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

No *insereNo(No *No, int item){
    if(No == NULL) return novoNo(item);
    if(No->val < item){
        No->dir = insereNo(No->dir, item);
    }else if (No->val > item){
        No->esq = insereNo(No->esq, item);
    }
    return No;

}

void PosO(No * raiz){
    if(raiz != NULL){
        printf("%d\n", raiz->val);
        PosO(raiz->esq);
        PosO(raiz->dir);
    }
}

int main(){
    struct no *raiz = NULL;
    raiz = insereNo(raiz, 10);
    raiz =insereNo(raiz, 20);
    raiz =insereNo(raiz, 30);
    raiz =insereNo(raiz, 40);
    raiz = insereNo(raiz, 50);
    raiz =insereNo(raiz, 60);
    PosO(raiz);
    raiz = removeNo(raiz, 100);
    PosO(raiz);

    return 0;
}
