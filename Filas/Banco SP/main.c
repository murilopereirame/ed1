#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/*
 * Declara a estrutura pessoa
 * nome -> Inicial gerada randomicamente;
 * op -> Nº da operação;
 * prox -> ponteiro para proxima pessoa da fila
 */
struct pessoa {
    char nome;
	int op;
	struct pessoa *prox;
};


/*
 * Declara a struct fila
 * inicio -> primeira pessoa da fila
 * fim -> ultima pessoa da fila
 */
struct fila {
	struct pessoa *inicio;
	struct pessoa *fim;
} *F;

void insere(int elem, struct fila *f);
void imprimeCaixas(struct fila c[], int qntCaixas);
int filaVazia(struct fila *f);
int contaFila(struct fila *f);
int escolherFilaSair(struct fila c[], int nCaixas);
int escolherFilaEntrar(struct fila c[], int nCaixas);
void removerFila(struct fila *f);
void imprimeFila(struct fila *f, int nCaixa);


void main(){

    /* Cria um vetor com 4 posições
     * Cada posição armazena uma fila
     * Cada posição representa um caixa
     */
    struct fila caixas[4];

    //Inicia o seed do random;
    srand(time(NULL));

    //Aloca espaço para os "caixas" e insere no vetor
    for(int i = 0; i < 4; i++)
    {
        F = (struct fila*)malloc(sizeof(struct fila));
        F->inicio = NULL;
        F->fim = NULL;

        caixas[i] = *F;
    }

    //Inicia um loop infinito para imprimir e gerir os caixas
    while(1){
        /* Declara uma variavel auxiliar para determinar
         * se eh possivel remover de alguma fila
         */
        int remover = escolherFilaSair(caixas, 4);

        //Caso possa, remove o da posição retornada
        if(remover >= 0)
            removerFila(&caixas[remover]);

        //Insere na fila
        insere(rand() % 4, &caixas[escolherFilaEntrar(caixas, 4)]);

        //Imprime os caixas
        imprimeCaixas(caixas, 4);
    }

}

int escolherFilaEntrar(struct fila c[], int nCaixas){
    //Loop infinito pra previnir de não inserir
    while(1){
        //Gera uma posição aleatoria (Random menos viciado que o normal)
        int poss = (int)( 4.0 * rand() / ( RAND_MAX + 1.0 ) );

        //Caso a fila não esteja cheia, retorna a posição
        //Caso contrario, reinicia o loop.
        if(contaFila(&c[poss]) < 4)
            return poss;
    }
}

int escolherFilaSair(struct fila c[], int nCaixas){

    //Short pra saber se todas as filas
    //estão vazias
    short pode = 1;

    //Int para determinar de qual caixa
    //vai sair cliente
    int caixaSair = -1;

    //For verificando se os caixas estão vazios
    for(int i = 0; i < nCaixas; i++){
        if(contaFila(&c[i]) < 1)
            pode = 0;
    }

    //Caso vazios, retorna -1
    if(pode == 0)
        return caixaSair;
    else{
        //Não há caixas vazios, podemos remover
        while(1){

            //Random não tão viciado gerando o caixa que vai sair um cliente
            int melhor = (int)( 4.0 * rand() / ( RAND_MAX + 1.0 ) );


            //Se a contagem for maior do que 1, pode remover, caso contrario retira de um caixa aleatorio
            //PS: Inclui esse, possíbildade de caixa vazio.
            if(contaFila(&c[melhor]) > 1)
                return melhor;
            else
                return (int)( 4.0 * rand() / ( RAND_MAX + 1.0 ) );
        }
    }
}

void removerFila(struct fila *f){
    //Referencia o segundo na fila
    struct pessoa *p = f->inicio->prox;

    //Limpa o espaço de memória com o primeiro
    free(f->inicio);

    //Troca o primeiro pelo segundo
    f->inicio = p;
}

void insere(int elem, struct fila *f){
    //Aloca o espaço da estrutura pessoa
	struct pessoa *cliente = malloc(sizeof(struct pessoa));

	//Determina as informações do cliente
 	cliente->op = elem;
 	cliente->prox = NULL;
 	cliente->nome = ((int)rand() % 26) + 65;

 	/* ====== MODELO FIFO ======*/

 	//Verifica se a fila ta vazia
	if (filaVazia(f)){
	    //Vazia --> cliente vai no inicio
 		f->inicio = cliente;
	}
	else {
	    //Não vazia --> Cliente vai no fim
 		f->fim->prox = cliente;
	}
	//Ultimo da fila é o novo cliente
 	f->fim = cliente;
}

int contaFila(struct fila *f) {
    struct pessoa *p;

    int count = 0;

    for (p = f->inicio; p != NULL; p = p->prox)
        count++;

    return count;
}

int filaVazia(struct fila *f){
	if (f->inicio == NULL) {
		return 1;
	}
	return 0;
}

void imprimeCaixas(struct fila c[], int qntCaixas){
    //Limpa o console
    system("cls");

    //Inicia um foor pelos caixas imprimindo-os
    for(int i = 0; i < qntCaixas; i++){
        printf("\n");
        imprimeFila(&c[i], i);
    }
}

void imprimeFila(struct fila *f, int nCaixa){
    struct pessoa *p; // variável auxiliar para percorrer a lista
    printf("[CAIXA %d] ", nCaixa); //Imprime [CAIXA N]
    if(contaFila(f) == 0) //Verifica se o caixa esta vazio
        printf("CAIXA VAZIO!");
    else {
        for (p = f->inicio; p != NULL; p = p->prox) //Percorre o caixa até o ponteiro ficar nulo
            printf("(%c, %d) | ", p->nome, p->op); //Imprime no modelo (INICIAL, OPERAÇÃO)
    }
}
