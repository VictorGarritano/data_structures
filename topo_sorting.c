#include <stdio.h>
#include <stdlib.h>

typedef struct _NO {
	int chave;
	struct _NO* prox;
} no;

int TAM;
no* lista;

void init();
void insere(int vertice, int chave);

int main(void) {
	init();
    if (lista == NULL) {
        printf("Erro na criacao da lista!!!\n");
        exit(EXIT_FAILURE);
    }

	for(i = 1; i < TAM + 1; i ++) {
        int key;
        scanf("%d", &n);
        for(j = 0; j < n; j ++) {
            scanf("%d", &key);
            insere(i,key);
        }
    }

    free(lista);

	return 0;
}

void init() {
	int i;

	scanf("%d", &TAM);
	lista = (no*) malloc(sizeof(no)*(TAM+1));
	for (i = 1; i < TAM + 1; i ++){
        lista[i].chave = 0;
        lista[i].prox = NULL;
	}
}

void insere(int vertice, int chave) {
	no* aux;
	aux = (no*) malloc(sizeof(no));
	aux->prox= NULL;
	aux->chave = chave;

    if(lista[vertice].prox == NULL) {
        lista[vertice].prox = aux;
    }
    else {
        no* temp;
        temp = lista[vertice].prox;

        while(temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = aux;
    }
	lista[vertice].chave++;
}