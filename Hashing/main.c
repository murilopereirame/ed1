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
    int ind;
}NOS;

typedef struct{
    NOS P[MAX];
    NOS O[OVER];
} LSHO;

typedef struct{
    NOH *V[MAX];
}LSH;


//Hashing sem overflow
void inicializarHT(LSH *tab);
void insertHSC(LSH *tab, char *content, int ind);
void removeHashS(LSH *tab, int ind, const char *content);
void imprimeHashingTable(LSH *tab);
int searchHashS(LSH *tab, int ind, const char *content);

//Hashing com overflow
void startHTS(LSHO *tab);
void insertHCO(LSHO *tab, char *content, int ind);
void removeHashO(LSHO *tab, int ind, const char *content);
void printHashingWOver(LSHO *tab);
int searchHashO(LSHO *tab, int ind, const char *content);

//Hashing universal
int hash(char *info, int tam);

void main(){

    //HASHING
    //Hashing básico, com colisão
    printf("======HASH CC======\n");
    LSH *listahash = malloc(sizeof(LSH));
    inicializarHT(listahash);

    insertHSC(listahash, "OPA", hash("OPA", MAX));
    insertHSC(listahash, "ED", hash("ED", MAX));
    insertHSC(listahash, "RD", hash("RD", MAX));
    insertHSC(listahash, "PD", hash("PD", MAX));
    insertHSC(listahash, "UM", hash("UM", MAX));
    insertHSC(listahash, "PORRE", hash("PORRE", MAX));

    printf("\n===Tabela original===\n");
    imprimeHashingTable(listahash);

    printf("\n===Tabela alterada===\n");
    removeHashS(listahash, hash("RD", MAX), "RD");
    imprimeHashingTable(listahash);

    printf("\n===Busca item PD===\n");
    if(searchHashS(listahash, hash("PD", MAX), "PD") > 0)
        printf("O conteúdo existe.\n\n");
    else
        printf("O conteúdo não existe.\n\n");

    printf("\n===Reinserindo PD===\n");
    insertHSC(listahash, "PD", hash("PD", MAX));
    printf("\n\n");

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

    //Overflow a partir daqui
    insertHCO(listahover, "QPA!", hash("QPA!", MAX));
    insertHCO(listahover, "GPA!", hash("GPA!", MAX));

    insertHCO(listahover, "TOP!!", hash("TOP!!", MAX));
    printf("\n===Tabela Original===\n");
    printHashingWOver(listahover);

    printf("\n===Tabela Alterada===\n");
    removeHashO(listahover, hash("OPA!", MAX), "OPA!");
    printHashingWOver((listahover));

    printf("\n===Busca item RPA!===\n");
    if(searchHashO(listahover, hash("RPA!", MAX), "RPA!") > 0)
        printf("O conteúdo existe.\n\n");
    else
        printf("O conteúdo não existe.\n\n");

    printf("\n===Reinserindo RPA!===\n");
    insertHCO(listahover, "RPA!", hash("RPA!", MAX));



}

/*========================
 *=========HASHING========
 *========================*/

//Função hashing geral
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
//Hashing sem overflow
void inicializarHT(LSH *tab){
    for(int i = 0; i < MAX; i++){
        tab->V[i] = NULL;
    }
}
void insertHSC(LSH *tab, char *content, int ind){
    if(tab == NULL)
    {
        printf("Tabela nula.");
        return;
    }

    if(searchHashS(tab, ind, content) > 0){
        printf("O conteúdo já exite.\n");
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
void removeHashS(LSH *tab, int ind, const char *content){
    if(tab == NULL){
        printf("Tabela nula.\n");
        return;
    }
    NOH p = tab->V[ind];
    if(p->content == content){
        tab->V[ind] = p->prox;
        free(p);
    }else{
        NOH aux = p;
        p = p->prox;
        while(p->prox != NULL){
            if(content == p->content) {
                aux->prox = p->prox;
                free(p);
                return;
            }
        }

        if(p->content == content){
            aux->prox = NULL;
            free(p);
        }else{
            printf("Conteudo não encontrado.\n");
        }

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
int searchHashS(LSH *tab, int ind, const char *content){
    if(tab == NULL){
        printf("Tabela nula.\n");
        return -1;
    }

    if(tab->V[ind] == NULL){
        return -1;
    }

    NOH p = tab->V[ind];
    while(p->prox != NULL){
        if(p->content == content)
            return 1;

        p = p->prox;
    }

    if(p->content == content)
        return 1;

    return 0;
}
//Hashing com overflow
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

    if(searchHashO(tab, ind, content) > 0){
        printf("O conteúdo já existe.\n");
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
void removeHashO(LSHO *tab, int ind, const char *content){
    if(tab == NULL){
        printf("Tabela nula.\n");
        return;
    }

    if(tab->P[ind].content == content){
        if(tab->P[ind].prox != -1){
            int overStart = tab->P[ind].prox;
            tab->P[ind].content = tab->O[overStart].content;
            tab->P[ind].prox = tab->O[overStart].prox;
            tab->O[overStart].content = NULL;
            tab->O[overStart].prox = -1;
            return;
        }
        tab->P[ind].content = NULL;
        return;
    }
    int i = tab->P[ind].prox;
    int j = -1;
    while(i != -1){
        if(tab->O[i].content == content){
            if(j == -1) {
                tab->P[ind].prox = tab->O[i].prox;
                tab->O[i].content = NULL;
                tab->O[i].prox = -1;
                return;
            }
            tab->O[j].prox = tab->O[i].prox;
            tab->O[i].content = NULL;
            tab->O[i].prox = -1;
            return;
        }

        if(tab->O[i].prox == -1){
            if(tab->O[i].content == content){
                tab->O[j].prox = -1;
                tab->O[i].content = NULL;
                return;
            }
            else{
                printf("Conteudo não encontrado.\n");
                return;
            }
        }

        j = i;
        i = tab->O[i].prox;
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
int searchHashO(LSHO *tab, int ind, const char *content){
    if(tab == NULL){
        printf("Lista nula.\n");
        return -1;
    }

    if(tab->P[ind].content == content)
        return 1;

    int prox = tab->P[ind].prox;
    while(prox != -1) {
        if (tab->O[prox].content == content)
            return 1;
        else {
            if(tab->O[prox].prox == -1) {
                if (tab->O[prox].content == content)
                    return 1;
                else
                    return 0;
            }
            prox = tab->O[prox].prox;
        }
    }

}
//Hashing com overflow em arquivo
void startFile(FILE *arq){
    if(arq == NULL){
        arq = fopen("data.dat", "wb+");
        if(!arq)
            printf("Erro ao abrir arquivos.");
    }
}
void insertHFile(LSHO *tab, char *content, FILE *arq){
    NOS n = {-1, *content};
    fwrite(&n, sizeof(NOS), 1, arq);
}
void removeHFile(LSHO *tab, char *content, FILE *arq){

}