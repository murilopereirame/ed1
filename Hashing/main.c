#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 10
#define OVER 5

typedef struct{
    char *content;
    struct NOH *prox;
} *NOH;

typedef struct{
    int prox;
    char *content;
}NOS;

typedef struct{
    NOS P[MAX];
    NOS O[OVER];
} LSHO;

typedef struct{
    NOH *V[MAX];
}LSH;

void imprimeHashingTable(LSH *tab);
void insertHSC(LSH *tab, char *content, int ind);
void inicializarHT(LSH *tab);
int hash(char *info, int tam);

void main(){

    //HASHING
    //Hashing básico, com colisão
    printf("======HASH CC======\n");
    LSH *listahash = malloc(sizeof(LSH));
    inicializarHT(listahash);
    insertHSC(listahash, "OPA", hash("OPA", MAX));
    insertHSC(listahash, "ED", hash("ED", MAX));
    insertHSC(listahash, "UM", hash("UM", MAX));
    insertHSC(listahash, "PORRE", hash("PORRE", MAX));
    imprimeHashingTable(listahash);

    printf("=====HASHING CO=====\n");
}

/*========================
 *=========HASHING========
 *========================
 */

int hash(char *info, int tam){
    int soma = 0;

    for(int i =0; strlen(info) > i; i++){
        soma += ((int)info[i]) * i;
    }
    if((int)(soma%tam) > MAX)
        while((int)(soma%tam) > MAX)
            soma = (int)(soma/10);

    return (int)(soma%tam);
}
void inicializarHT(LSH *tab){
    for(int i = 0; i < MAX; i++){
        tab->V[i] = NULL;
    }
}
void startHTS(LSHO *tab){
    if(tab == NULL){
        printf("Tabela nula.");
        return;
    }

    for(int i = 0; i < MAX; i++) {
        tab->P[i].prox = -1;
        tab->P[i].content = NULL;
    }

    for(int i = 0; i < OVER; i++){
        tab->O[i].prox = -1;
        tab->O[i].content = NULL;
    }
}
void insertHCO(LSHO *tab, char *content, int ind){
    if(tab == NULL){
        printf("Table nula.");
        return;
    }

    if(tab->P[ind].content == NULL){
        tab->P[ind].content = content;
        tab->P[ind].prox = -1;
        return;
    }

    int i = 0;
    while(i < MAX){
        if(tab->O[i].content == NULL)
            break;
        i++;
    }

    if(i >= MAX){
        printf("Overflow cheio.");
        return;
    }

    tab->P[ind].prox = i;
    tab->O[ind].content = content;
    tab->O[ind].prox = -1;

}
void insertHSC(LSH *tab, char *content, int ind){
    if(tab == NULL)
    {
        printf("Tabela nula.");
        return;
    }

    if(tab->V[ind] == NULL)
    {
        NOH n = malloc(sizeof(NOH));
        n->content = content;
        n->prox = NULL;
        tab->V[ind] = n;
        return;
    }

    NOH n = tab->V[ind];
    while(n->prox != NULL)
        n = n->prox;

    n->prox = malloc((sizeof(NOH)));
    n = n->prox;
    n->content = content;
    n->prox = NULL;
}

void insertHCC(LSH *tab, char *content, int ind){
    if(tab == NULL)
    {
        printf("Tabela nula.");
        return;
    }

    if(tab->V[ind] == NULL)
    {
        NOH n = malloc(sizeof(NOH));
        n->content = content;
        n->prox = NULL;
        tab->V[ind] = n;
        return;
    }
}

void imprimeHashingTable(LSH *tab){
    if(tab == NULL){
        printf("Tabela nula.");
        return;
    }

    for(int i = 0; i < MAX; i++){
        if(tab->V[i] != NULL) {
            NOH p = tab->V[i];
            printf("\nIndice %d:", i);
            while (p->prox != NULL) {
                printf("\n  %s", p->content);
                p = p->prox;
            }
            printf("\n  %s", p->content);
            printf("\n");
        }
    }
}

void printHashingWOver(LSH *tab){
    if(tab == NULL){
        printf("Tabela nula.");
        return;
    }
}