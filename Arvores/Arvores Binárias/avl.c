#include <stdlib.h>
#include <stdio.h>

typedef struct{
    struct NO *esq;
    struct NO *dir;
    struct NO *pai;
    int data;
    int fatB;
} NO;

int altura(NO* t);
void imprimeArvore(NO *raiz);
void rotacionaDireita(NO *pai);
void defineBalanceamento(NO *raiz);
int main(){
    NO *raiz = malloc(sizeof(NO));
    raiz->pai = NULL;
    raiz->data = 27;

    NO *d1 = malloc(sizeof(NO));
    d1->pai = raiz;
    d1->data = 49;
    d1->esq = NULL;
    d1->dir = NULL;

    NO *e1 = malloc(sizeof(NO));
    e1->data = 15;
    e1->dir = NULL;
    e1->esq = NULL;

    NO *e2 = malloc(sizeof(NO));
    e2->data = 10;
    e2->dir = NULL;
    e2->esq = NULL;

    NO *e3 = malloc(sizeof(NO));
    e3->data = 8;
    e3->dir = NULL;
    e3->esq = NULL;

    raiz->dir = d1;
    raiz->esq = e1;
    e1->esq = e2;
    e2->esq = e3;

    rotacionaDireita(e1);
    imprimeArvore(raiz);
    defineBalanceamento(raiz);

    printf("\n\n\n%d", d1->fatB);
}

void defineBalanceamento(NO *raiz){
    int aE = 0, aD = 0;
    aD = altura(raiz->dir);
    aE = altura(raiz->esq);
    raiz->fatB = aE - aD;

    if(raiz->dir != NULL)
        defineBalanceamento(raiz->dir);
    if(raiz->esq != NULL)
        defineBalanceamento(raiz->esq);
}

void rotacionaDireita(NO *pai){
    //Filho a direita vira PAI do pai
    //Se o pai toma o lugar de algum elem, o elem passa a ser filho dele

    NO *aux = pai;
    if(aux->dir != NULL) {
        NO *auxII = aux->dir;
        auxII->pai = pai;
        pai->dir = aux->dir;
    }
     if(aux->esq != NULL){
         NO *auxII = aux->esq;
         aux->esq = pai->esq;
         auxII->pai = pai;
         pai->esq = auxII;
     }
     aux->pai = pai->pai;
     pai->pai = aux;
}

void rotacionaEsq(NO *pai){
    //Filho a direita vira PAI do pai
    //Se o pai toma o lugar de algum elem, o elem passa a ser filho dele
    NO *aux = pai;
    if(aux->esq != NULL) {
        NO *auxII = aux->esq;
        auxII->pai = pai;
        pai->esq = aux->esq;
    }
    if(aux->dir != NULL){
        NO *auxII = aux->dir;
        aux->dir = pai->dir;
        auxII->pai = pai;
        pai->dir = auxII;
    }
    aux->pai = pai->pai;
    pai->pai = aux;
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

int altura(NO* t)
{
    int altE =0, altD=0;
    NO *q, *temp;
    if(t == NULL)
        return -1;
    else
    {
        altE = altura(t->esq);
        altD = altura(t->dir);
        if(altE < altD)
            return altD+1;
        else
            return altE+1;
    }
}