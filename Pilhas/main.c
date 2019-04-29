#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int con;
    struct Elem *prox;
} Elem;

typedef struct{
    Elem *top;
} Pilha;

void imprimePilha(Pilha *p);
void pop(Pilha *p);
void push(Pilha *p, int con);
void iniciaPilha(Pilha *p);

void main(){
    Pilha *p = malloc(sizeof(Pilha));

    iniciaPilha(p);

    printf("===Pilha inicial===\n");
    push(p, 10);
    push(p, 3);
    push(p, 0);
    push(p, 7);
    push(p, -2);
    push(p, -5);
    push(p, 3);
    imprimePilha(p);

    printf("\n\n");

    printf("===Pilha após remoção===\n");
    pop(p);
    pop(p);
    pop(p);
    imprimePilha(p);
}

void iniciaPilha(Pilha *p){
    p->top = NULL;
}
void push(Pilha *p, int con){
    if(p == NULL){
        printf("Pilha nula.\n");
        return;
    }

    Elem *e = malloc(sizeof(Elem));
    e->con = con;
    e->prox = NULL;

    if(p->top == NULL){
        p->top = e;
        return;
    }

    e->prox = p->top;
    p->top = e;
}
void pop(Pilha *p){
    if(p == NULL){
        printf("Pilha nula.\n");
        return;
    }
    if(p->top == NULL){
        printf("Pilha vazia.\n");
        return;
    }
    Elem *e = p->top;
    p->top = e->prox;
    free(e);
}
void imprimePilha(Pilha *p){
    if(p == NULL){
        printf("Pilha nula.\n");
        return;
    }
    if(p->top == NULL){
        printf("Pilha vazia.\n");
        return;
    }

    Elem *e = p->top;
    while(e->prox != NULL){
        printf("%d\n", e->con);
        e= e->prox;
    }
    printf("%d\n", e->con);
}