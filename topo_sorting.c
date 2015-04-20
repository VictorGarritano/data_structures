#include <stdio.h>
#include <stdlib.h>

typedef struct _NO {
    int chave;
    struct _NO* prox;
} no;

int TAM, aresta, vertice, key;
no* vizinhosDeEntrada;
no* vizinhosDeSaida;

no* init(no* lista);
void insere(no* lista, int vertice, int chave);
//void imprime(no* lista);

int main(void) {
    scanf("%d %d", &TAM, &aresta);
    int saida[TAM];
    int i, k = 0;
    vizinhosDeEntrada = init(vizinhosDeEntrada);
    vizinhosDeSaida = init(vizinhosDeSaida);
    if (vizinhosDeEntrada == NULL) {
        printf("Erro na criacao da lista da entrada!!!\n");
        exit(EXIT_FAILURE);
    }
    else if (vizinhosDeSaida == NULL) {
        printf("Erro na criacao da lista de saida!!!\n");
        exit(EXIT_FAILURE);
    }
    for(i = 1; i < aresta + 1; i ++) {
        scanf("%d %d",&vertice, &key);
        insere(vizinhosDeEntrada,vertice,key);
        insere(vizinhosDeSaida,key,vertice);
    }

//  imprime(vizinhosDeEntrada);
//  printf("\n");
//  imprime(vizinhosDeSaida);

    int objeto = TAM;
    while(objeto != 0) {
        for(i = 1; i < TAM + 1; i ++) {
            if(vizinhosDeEntrada[i].chave == 0) {
                no* aux = vizinhosDeSaida[i].prox;
                    while(aux != NULL) {
                        vizinhosDeEntrada[aux->chave].chave--;
                        aux = aux->prox;
                    }
                saida[k] = i;
                vizinhosDeEntrada[i].chave = -1;
                k++;
                objeto--;
            }
        }
   }


    for(i = 0; i < k; i ++) {
        printf("%d ", saida[i]);
    }

    return 0;
}

no* init(no* lista) {
    int i;

    lista = (no*) malloc(sizeof(no)*(TAM+1));
    for (i = 1; i < TAM + 1; i ++){
        lista[i].chave = 0;
        lista[i].prox = NULL;
    }

    return lista;
}

void insere(no* lista,int vertice, int chave) {
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

//void imprime(no* lista) {
//    int i;
//    no* tmp;
//
//    for(i = 1; i< TAM + 1; i ++) {
//        tmp = lista[i].prox;
//        printf("%2d: (%d) ==> ", i, lista[i].chave);
//        while (tmp != NULL) {
//        printf("%d  ", tmp->chave);
//        tmp = tmp->prox;
//    }
//
//        printf("\n");
//    }
//}
