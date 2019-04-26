#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int conteudo;
    struct NO *prox;
} NO;

typedef struct{
    NO *no;
} LS;

typedef struct{
    NO *no;
    int r;
    int a;
} LSRA;

typedef struct{
    LS *l1;
    LS *l2;
} LSIP;

void insereLista(LS *lista, int conteudo);
void imprimeLista(LS *lista);
int contaLista(LS *lista);
int contaListaR(NO *item);
int qntMatchR(NO *no, int item);
int qntMatch(LS *lista, int item);
int qntMatchBig(LS *lista, int item);
int qntMatchSmall(LS *lista, int item);
void *splitIPList(LS *lista);
void *splitBSList(LS *lista, int x);
int replaceXY(LS *lista, int x, int y);
void removeX(LS *lista, int x);
void removeRA(LSRA *lista, int x);
void insereListaRA(LSRA *lista, int conteudo);
int returnPNO(LS *lista);
int returnUNO(LS *lista);

int main() {
    LS *lista = malloc(sizeof(LS));
    lista->no = NULL;

    insereLista(lista, 3);
    insereLista(lista, 2);
    insereLista(lista, 3);
    insereLista(lista, 3);
    insereLista(lista, 4);
    insereLista(lista, 5);
    insereLista(lista, 3);

    printf("Lista: \n");
    imprimeLista(lista);
    printf("\n\n");

    //Exercício 1
    printf("======Exercício 1======");
    printf("\nA lista possui: %d elementos", contaLista(lista));
    printf("\n\n");

    //Exercício 2
    printf("======Exercício 2======");
    printf("\nA lista possui: %d elementos", contaListaR(lista->no));
    printf("\n\n");

    //Exercício 3
    printf("======Exercício 3======");
    printf("\nO número %d se repete %d vezes", 2, qntMatch(lista, 2));
    printf("\nO número %d se repete %d vezes", 2, qntMatchR(lista->no, 2)); //Recursivo
    printf("\n\n");

    //Exercício 4
    printf("======Exercício 4======");
    printf("\nA lista possui %d elementos maiores do que %d", qntMatchBig(lista, 3), 3);
    printf("\n\n");

    //Exercício 5
    printf("======Exercício 5======");
    printf("\nA lista possui %d elementos menores do que %d", qntMatchSmall(lista, 5), 5);
    printf("\n\n");


    //Exercicio 6
    LSIP *ip = splitIPList(lista);

    printf("======Exercício 6======");
    printf("\nImpares: \n");
    imprimeLista(ip->l1);
    printf("\nPares: \n");
    imprimeLista(ip->l2);
    printf("\n\n");
    free(ip);

    //Exercício 7
    ip = splitBSList(lista, 3);

    printf("======Exercício 7======");
    printf("\nMaiores que %d: \n", 3);
    imprimeLista(ip->l1);
    printf("\nMenores que %d: \n", 3);
    imprimeLista(ip->l2);
    printf("\n\n");
    free(ip);

    //Exercício 8
    printf("======Exercício 8======");
    printf("\nVezes em que o 3 foi trocado por 7: %d", replaceXY(lista, 3, 7));
    printf("\nNova lista: \n");
    imprimeLista(lista);
    printf("\n\n");

    //Exercício 9
    removeX(lista, 7);
    printf("======Exercício 9======");
    printf("\nNova lista: \n");
    imprimeLista(lista);
    printf("\n\n");

    //Exercício 10
    LSRA *listara = malloc(sizeof(LSRA));

    listara->r = 0;
    listara->a = 0;
    listara->no = NULL;

    insereListaRA(listara, 2);
    insereListaRA(listara, 3);
    insereListaRA(listara, 3);
    insereListaRA(listara, 6);
    insereListaRA(listara, 150);
    insereListaRA(listara, 10);
    insereListaRA(listara, 8);
    insereListaRA(listara, 11);

    printf("======Exercício 10======");
    printf("\nLista inicial (A: %d | R: %d): \n", listara->a, listara->r);
    imprimeLista(listara);
    removeRA(listara, 3);
    printf("\nLista final (A: %d | R: %d): \n", listara->a, listara->r);
    imprimeLista(listara);
    printf("\n\n");

    //Exercício 11
    printf("======Exercício 11======");
    printf("\nConteúdo primeiro nó: %d", returnPNO(lista));
    printf("\n\n");

    //Exercício 12
    printf("======Exercício 12======");
    printf("\nConteúdo último nó: %d", returnUNO(lista));
    printf("\n\n");

    return 0;
}

void insereLista(LS *lista, int conteudo){
    if(lista == NULL)
        return;
    if(lista->no == NULL)
    {
        lista->no = malloc(sizeof(NO));
        lista->no->conteudo = conteudo;
        lista->no->prox = NULL;
    }
    else
    {
        NO *p = lista->no;
        while(p->prox != NULL)
            p = p->prox;
        p->prox = malloc(sizeof(NO));
        p = p->prox;
        p->conteudo = conteudo;
        p->prox = NULL;
    }
}

void insereListaRA(LSRA *lista, int conteudo){
    if(lista == NULL)
        return;
    if(lista->no == NULL)
    {
        lista->no = malloc(sizeof(NO));
        lista->no->conteudo = conteudo;
        lista->no->prox = NULL;
        lista->a = 1;
    }
    else
    {
        NO *p = lista->no;
        while(p->prox != NULL)
            p = p->prox;
        p->prox = malloc(sizeof(NO));
        p = p->prox;
        p->conteudo = conteudo;
        p->prox = NULL;
        lista->a++;
    }
}

void imprimeLista(LS *lista){
    if(lista == NULL)
        return;
    if(lista->no == NULL)
    {
        printf("A lista esta vazia.");
        return;
    }
    else {
        NO *p = lista->no;
        while (p->prox != NULL) {
            printf("%d ", p->conteudo);
            p = p->prox;
        }
        printf("%d ", p->conteudo);
    }
}

int contaLista(LS *lista){
    if(lista == NULL)
        return -1;
    if(lista->no == NULL)
        return 0;
    else {
        NO *p = lista->no;
        int qt = 1;
        while (p->prox != NULL) {
            p = p->prox;
            qt++;
        }
        return qt;
    }
}

int contaListaR(NO *item){
    if(item != NULL) {
        return contaListaR(item->prox) + 1;
    }

    return 0;
}

int qntMatchR(NO *no, int item){

    if(no != NULL) {
        if (no->conteudo == item)
            return qntMatchR(no->prox, item) + 1;
        else
            return qntMatchR(no->prox, item);
    }

    return 0;
}

int qntMatch(LS *lista, int item){
    if(lista == NULL)
        return -1;
    if(lista->no == NULL)
        return -1;

    int qt = 0;
    NO *p = lista->no;

    while(p->prox != NULL){
        if(p->conteudo == item)
            qt++;
        p = p->prox;
    }

    if(p->conteudo == item)
        qt++;

    return qt;
}

int qntMatchBig(LS *lista, int item){
    if(lista == NULL)
        return -1;

    int qt = 0;
    NO *p = lista->no;

    while(p->prox != NULL){
        if(p->conteudo > item)
            qt++;
        p = p->prox;
    }

    if(p->conteudo > item)
        qt++;

    return qt;
}
int qntMatchSmall(LS *lista, int item){
    if(lista == NULL)
        return -1;

    int qt = 0;
    NO *p = lista->no;

    while(p->prox != NULL){
        if(p->conteudo < item)
            qt++;
        p = p->prox;
    }

    if(p->conteudo < item)
        qt++;

    return qt;
}

void *splitIPList(LS *lista){
    if(lista == NULL)
        return NULL;

    LS *impar = malloc(sizeof(LS));
    LS *par = malloc(sizeof(LS));
    NO *p = lista->no;

    par->no = NULL;
    impar->no = NULL;


    while(p->prox != NULL){
        if(p->conteudo%2 == 0)
            insereLista(par, p->conteudo);
        else
            insereLista(impar, p->conteudo);

        p = p->prox;
    }

    if(p->conteudo%2 == 0)
        insereLista(par, p->conteudo);
    else
        insereLista(impar, p->conteudo);

    LSIP *listaip = malloc(sizeof(LSIP));
    listaip->l1 = impar;
    listaip->l2 = par;
    return listaip;
}

void *splitBSList(LS *lista, int x){
    if(lista == NULL)
        return NULL;
    LS *big = malloc(sizeof(LS));
    LS *small = malloc(sizeof(LS));
    NO *p = lista->no;

    big->no = NULL;
    small->no = NULL;


    while(p->prox != NULL){
        if(p->conteudo > x)
            insereLista(big, p->conteudo);
        else if(p->conteudo < x)
            insereLista(small, p->conteudo);

        p = p->prox;
    }

    if(p->conteudo > x)
        insereLista(big, p->conteudo);
    else if(p->conteudo < x)
        insereLista(small, p->conteudo);

    LSIP *listaip = malloc(sizeof(LSIP));
    listaip->l1 = big;
    listaip->l2 = small;
    return listaip;
}

int replaceXY(LS *lista, int x, int y){
    if(lista == NULL)
        return -1;

    int qt = 0;

    NO *p = lista->no;

    while(p->prox != NULL){
        if(p->conteudo == x) {
            p->conteudo = y;
            qt++;
        }
        p=p->prox;
    }

    if(p->conteudo == x) {
        p->conteudo = y;
        qt++;
    }
    return qt;
}

void removeX(LS *lista, int x){
    if(lista == NULL)
        return;

    NO *p = lista->no;
    NO *aux = NULL;

    if(p->conteudo == x){
        lista->no = p->prox;
        free(p);
        aux = lista->no;
    }

    while(aux->prox != NULL){
        p = aux;
        aux = aux->prox;
        if(aux->conteudo == x) {
            p->prox = aux->prox;
            free(aux);
            aux = p;
        }
    }
}

void removeRA(LSRA *lista, int x){
    if(lista == NULL)
        return;

    NO *p = lista->no;
    NO *a = NULL;

    if(p->conteudo == x) {
        lista->no = p->prox;
        free(p);
        p = lista->no;
        lista->r++;
    }

    while (p->prox != NULL){
        a = p;
        p = p->prox;
        if(p->conteudo == x){
            a->prox = p->prox;
            free(p);
            p = a;
            lista->r++;
        }
    }
}

int returnPNO(LS *lista){
    if(lista != NULL) {
        if (lista->no != NULL)
            return lista->no->conteudo;
        else
            printf("\nLista vazia.");
    }
    else
        printf("\nLista nula.");
}

int returnUNO(LS *lista){
    if(lista == NULL) {
        printf("Lista nula.");
        return NULL;
    }

    if(lista->no == NULL){
        printf("Lista vazia.");
        return NULL;
    }

    NO *p = lista->no;

    while(p->prox != NULL)
        p = p->prox;

    return p->conteudo;
}


