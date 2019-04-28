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


//Hashing sem overflow
void imprimeHashingTable(LSH *tab);
void insertHSC(LSH *tab, char *content, int ind);
void inicializarHT(LSH *tab);

//Hashing com overflow
void startHTS(LSHO *tab);
void insertHCO(LSHO *tab, char *content, int ind);
void printHashingWOver(LSHO *tab);

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

    //Hashing básico com overflow
    printf("=====HASHING CO=====\n");
    LSHO *listahover = malloc(sizeof(LSHO));
    startHTS(listahover);
    insertHCO(listahover, "OPA!", hash("OPA!", MAX));
    insertHCO(listahover, "ED", hash("ED", MAX));
    insertHCO(listahover, "APA!", hash("APA!", MAX));
    insertHCO(listahover, "EPA!", hash("EPA!", MAX));
    insertHCO(listahover, "UPA!", hash("UPA!", MAX));
    insertHCO(listahover, "IPA!", hash("IPA!", MAX));
    insertHCO(listahover, "RPA!", hash("RPA!", MAX));
    insertHCO(listahover, "QPA!", hash("QPA!", MAX));
    insertHCO(listahover, "GPA!", hash("GPA!", MAX));
    insertHCO(listahover, "VSF RONALDO!!", hash("VSF RONALDO!!", MAX));
    printHashingWOver(listahover);
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
    while(i < OVER){
        if(tab->O[i].content == NULL)
            break;
        i++;
    }

    if(i >= OVER){
        printf("Overflow cheio.\nItem: '%s' não foi gravado.\n\n", content);
        return;
    }

    if(i == 0)
        tab->P[ind].prox = i;
    else
        tab->O[i-1].prox = i;
    tab->O[i].content = content;
    tab->O[i].prox = -1;

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

void printHashingWOver(LSHO *tab){
    if(tab == NULL){
        printf("Tabela nula.");
        return;
    }

    for(int i = 0; i < MAX; i++){
        if(tab->P[i].content != NULL){
            printf("Indice %d: ", i);
            printf("%s", tab->P[i].content);

            if(tab->P[i].prox != -1){
                printf("\nOverflow: ");
                int ind = tab->P[i].prox;
                while(ind != -1){
                    printf("%s ", tab->O[ind].content);
                    ind = tab->O[ind].prox;
                }
            }

            printf("\n\n");
        }
    }
}