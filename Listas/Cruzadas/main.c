#include <stdio.h>
#include <stdlib.h>

#define MAXC 5
#define MAXL 6

typedef struct {
    int content;
    int lin;
    int col;
    struct Elem *proxLin;
    struct Elem *proxCol;
} Elem;

typedef struct{
    Elem *colunas[MAXC];
    Elem *linhas[MAXL];
} Matrix;

void iniciaMatrix(Matrix *mat);
int insereLinha(Matrix *mat, Elem *e, int col, int linha);
int insereColuna(Matrix *mat, Elem *e, int col, int linha);
void insereElem(int col, int linha, Matrix *mat, int conteudo);
void imprimeMatrix(Matrix *mat);

void main(){
    Matrix *mt = malloc(sizeof(Matrix));
    iniciaMatrix(mt);
    insereElem(0, 0, mt, 2);
    insereElem(1, 1, mt, 3);
    insereElem(2, 2, mt, 4);
    insereElem(3, 3, mt, 5);
    insereElem(4, 4, mt, 6);
    insereElem(4, 5, mt, 7);
    imprimeMatrix(mt);
    free(mt);
}

void iniciaMatrix(Matrix *mat){
    for(int i = 0; i < MAXC; i++)
        mat->colunas[i] = NULL;

    for(int i = 0; i < MAXL; i++)
        mat->linhas[i] = NULL;
}
void insereElem(int col, int linha, Matrix *mat, int conteudo){

    if(mat == NULL){
        printf("Matriz nula.\n");
        return;
    }

    if(col > MAXC){
        printf("Indíce da coluna inválido.\n");
        return;
    }
    else if(linha > MAXL){
        printf("Indíce da linha inválido.\n");
        return;
    }


    Elem *n = malloc(sizeof(Elem));
    n->content = conteudo;
    n->col = col;
    n->lin = linha;
    n->proxCol = NULL;
    n->proxLin = NULL;

    insereColuna(mat, n, col, linha);
    insereLinha(mat, n, col, linha);

}
int insereLinha(Matrix *mat, Elem *e, int col, int linha){
    if(mat->linhas[linha] == NULL){
        mat->linhas[linha] = e;
    }else{
        Elem *p = mat->linhas[col];
        while(p->proxLin != NULL){
            if(p->col < col)
                p = p->proxLin;
            else{
                if(p->col == linha){
                    printf("Já existe um elemento nessa posição.\n");
                    return 0;
                }
                else{
                    e->proxLin = p->proxLin;
                    p->proxLin = e;
                    return 1;
                }
            }
        }
        p->proxLin = e;
        return 1;
    }
}
int insereColuna(Matrix *mat, Elem *e, int col, int linha){
    if(mat->colunas[col] == NULL){
        mat->colunas[col] = e;
    }else{
        Elem *p = mat->colunas[col];
        while(p->proxCol != NULL){
            if(p->lin < col)
                p = p->proxCol;
            else{
                if(p->lin == linha){
                    printf("Já existe um elemento nessa posição.\n");
                    return 0;
                }
                else{
                    e->proxCol = p->proxCol;
                    p->proxCol = e;
                    return 1;
                }
            }
        }
        p->proxCol = e;
        return 1;
    }
}
void imprimeMatrix(Matrix *mat){
    for(int i = 0; i < MAXL; i++){
        if(mat->linhas[i] == NULL){
            for(int j = 0; j < MAXC; j++){
                printf("0 ");
            }
        }
        else{
            Elem *n = mat->linhas[i];
            for(int j = 0; j < MAXC; j++){
                if(n != NULL) {
                    if (n->col == j)
                        printf("%d ", n->content);
                    else
                        printf("0 ");
                    n->proxLin;
                }else
                    printf("0 ");
            }
        }
        printf("\n");
    }
}