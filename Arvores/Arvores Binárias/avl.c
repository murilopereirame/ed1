#include <stdlib.h>
#include <stdio.h>

typedef struct{
    struct NO *esq;
    struct NO *dir;
    struct NO *pai;
    int data;
    int fatB;
} NO;

NO *noProblema(NO *raiz);
NO *buscaItem(int content, NO *raiz);
NO *criaNo(int content, NO *pai);
NO *moreRightOfLeft(NO *raiz);

int altura(NO* t);
int estaBalanceada(NO *raiz);

void deletaFilho(int content, NO *raiz);
void imprimeArvore(NO *raiz);
void rotacionaDireita(NO *pai);
void rotacionaEsq(NO *pai);
void defineBalanceamento(NO *raiz);
void insereElem(int content, NO *raiz);
void balancearArvore(NO *raiz);

int main(){
    NO *raiz = malloc(sizeof(NO));
    raiz->pai = NULL;
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->data = -2;

    insereElem(-9, raiz);
    insereElem(4, raiz);
    insereElem(6, raiz);
    insereElem(-4, raiz);
    insereElem(-13, raiz);
    insereElem(-411, raiz);
    insereElem(-7, raiz);
    insereElem(-3, raiz);

    imprimeArvore(raiz);

    printf("\n\n");
    deletaFilho(-4, raiz);
    balancearArvore(raiz);
    imprimeArvore(raiz);
}

void insereElem(int content, NO *raiz){
    while(!estaBalanceada(raiz)){
        balancearArvore(raiz);
    }

    if(raiz->esq == NULL && content < raiz->data){
        raiz->esq = criaNo(content, raiz);
        return;
    }
    else if(raiz->dir == NULL && content > raiz->data){
        raiz->dir = criaNo(content, raiz);
        return;
    }
    else if(raiz->data != content){
        if(content > raiz->data){
            insereElem(content, raiz->dir);
            return;
        }
        else{
            insereElem(content, raiz->esq);
            return;
        }
    }

    balancearArvore(raiz);
    defineBalanceamento(raiz);
}

NO *criaNo(int content, NO *pai){
    NO *elem = malloc(sizeof(NO));
    elem->data = content;
    elem->esq = NULL;
    elem->dir = NULL;
    elem->pai = pai;
    return elem;
}

int estaBalanceada(NO *raiz) {
    if(raiz->fatB == 0)
        return 1;
    else
        return 0;
}

void balancearArvore(NO *raiz){
    if(raiz->fatB > 1 || raiz->fatB < -1) {
        if(raiz->fatB > 1)
            rotacionaEsq(noProblema(raiz));
        else if(raiz->fatB < -1)
            rotacionaDireita(noProblema(raiz));
    }
    else
        return;
}

NO *noProblema(NO *raiz){
    if(raiz->fatB > 1){
        NO *aux = raiz->esq;
        while (aux != NULL){
            if(aux->fatB > 1)
                aux = aux->esq;
            else if(aux->fatB < -1)
                aux = aux->dir;
            else
                break;
        }

        return aux->pai;
    }
    else if(raiz->fatB < -1){
        NO *aux = raiz->dir;
        while (aux != NULL){
            if(aux->fatB < -1)
                aux = aux->dir;
            else if(aux->fatB > 1)
                aux = aux->esq;
            else
                break;
        }

        return aux->pai;
    }
    else
        return NULL;
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

NO *buscaItem(int content, NO *raiz){
    NO *aux = NULL;
    if(content > raiz->data){
        if(raiz->dir != NULL)
            aux = buscaItem(content, raiz->dir);
        else
            aux = NULL;

        return aux;
    }
    else if(content < raiz->data){
        if(raiz->esq != NULL)
            aux = buscaItem(content, raiz->esq);
        else
            aux = NULL;
        return aux;
    }
    else {
        if(raiz->data == content)
            aux = raiz;
        return aux;
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

void deletaFilho(int content, NO *raiz){
    if(content == raiz->data){
        NO *temp = moreRightOfLeft(raiz);
        NO *tempPai = temp->pai;

        if(tempPai->data < temp->data)
            tempPai->dir = NULL;
        else
            tempPai->esq = NULL;

        raiz->data = temp->data;
        raiz->pai = temp->pai;
    } else if(content < raiz->data)
        deletaFilho(content, raiz->esq);
    else if(content > raiz->data)
        deletaFilho(content, raiz->dir);

    balancearArvore(raiz);
    defineBalanceamento(raiz);
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