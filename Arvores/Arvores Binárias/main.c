#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int data;
    struct NO *esq;
    struct NO *dir;
} NO;

typedef struct{
    NO *raiz;
} Tree;

NO *criaNo(int content);
void insereFilho(int content, NO *raiz);
void imprimeArvore(NO *raiz);
int buscaElem(int content, NO *raiz);
NO *moreRightOfLeft(NO *raiz);
void deletaFilho(int content, NO *raiz);

int main(){
    NO *raiz = malloc(sizeof(NO));
    raiz->data = 0;
    raiz->esq = NULL;
    raiz->dir = NULL;

    //Inserção
    insereFilho(2, raiz);
    insereFilho(-2, raiz);
    insereFilho(5, raiz);
    insereFilho(7, raiz);
    insereFilho(3, raiz);
    insereFilho(-1, raiz);
    insereFilho(-3, raiz);

    //Impressão em ordem
    imprimeArvore(raiz);

    printf("\n\n\n");

    //Busca
    //printf("%d", buscaElem(-2, raiz));

    deletaFilho(0, raiz);
    imprimeArvore(raiz);
}

void deletaFilho(int content, NO *raiz){
    if(content == raiz->data){
        NO *temp = moreRightOfLeft(raiz);
        raiz->data = temp->data;
    } else if(content < raiz->data)
        deletaFilho(content, raiz->esq);
    else if(content > raiz->data)
        deletaFilho(content, raiz->dir);
}

NO *moreRightOfLeft(NO *raiz){
    if(raiz->dir == NULL){
        NO *temp = raiz->esq;
        while(temp->dir != NULL) {
            temp = temp->dir;
        }
        return temp;
    }else{
        NO *temp = raiz->dir;
        while(temp->esq != NULL) {
            temp = temp->esq;
        }
        return temp;
    }
}

void imprimeArvore(NO *raiz){
    if(raiz->dir == NULL && raiz->esq == NULL){
        printf("%d", raiz->data);
    }
    else if(raiz->dir == NULL) {
        imprimeArvore(raiz->esq);
        printf("%d", raiz->data);
    }
    else if(raiz->esq == NULL){
        imprimeArvore(raiz->dir);
        printf("%d", raiz->data);
    }
    else{
        imprimeArvore(raiz->esq);
        printf("%d", raiz->data);
        imprimeArvore(raiz->dir);
    }
}

int buscaElem(int content, NO *raiz){
    if(content < raiz->data && raiz->esq != NULL)
        buscaElem(content, raiz->esq);
    else if(content > raiz->data && raiz->dir != NULL)
        buscaElem(content, raiz->dir);
    else if(raiz->dir != NULL && raiz->esq != NULL)
        return 0;
    else
        if(content == raiz->data)
            return 1;
        else
            return 0;
}

void insereFilho(int content, NO *raiz){
    if(raiz->esq == NULL && content < raiz->data){
        raiz->esq = criaNo(content);
        return;
    }
    else if(raiz->dir == NULL && content > raiz->data){
        raiz->dir = criaNo(content);
        return;
    }
    else if(raiz->data != content){
        if(content > raiz->data){
            insereFilho(content, raiz->dir);
            return;
        }
        else{
            insereFilho(content, raiz->esq);
            return;
        }
    }
}

NO *criaNo(int content){
    NO *elem = malloc(sizeof(NO));
    elem->data = content;
    elem->esq = NULL;
    elem->dir = NULL;
    return elem;
}