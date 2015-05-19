#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _NO {
    int chave;
    struct _NO* prox;
} no;

int TAM, aresta;
no* vizinhosDeEntrada;
no* vizinhosDeSaida;

no* init(no* lista);
void insere(no* lista, int vertice, int chave);
void libera(no* lista);

int main(void) {
    scanf("%d %d\n", &TAM, &aresta);
    int i, key;
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
    
    char *buffer;
    char string[1000];
    
    for(i = 0; i < TAM; i++) {
        fgets(string, sizeof(string), stdin);
        buffer = strtok (string," ");
        while(buffer != NULL) {
            if(sscanf(buffer, " %d", &key) == -1) {
            }
            else {
                insere(vizinhosDeSaida, i + 1, key);
                insere(vizinhosDeEntrada, key, i + 1);
            }
            buffer = strtok (NULL, " ");
        }
    }
    free(buffer);

    for(i = 1; i < TAM + 1; i ++) {
        if(vizinhosDeEntrada[i].chave == 0) {
            //Inicia a lista encadeada de fontes, que será armazenada em vizinhosDeEntrada[0]
            insere(vizinhosDeEntrada, 0, i);
        }
    }
    
    no* aux1 = vizinhosDeEntrada[0].prox;
    while(aux1 != NULL) {
        no* aux2 = vizinhosDeSaida[aux1->chave].prox;
        while(aux2 != NULL) {
            vizinhosDeEntrada[aux2->chave].chave--;
            if(vizinhosDeEntrada[aux2->chave].chave == 0) {
                insere(vizinhosDeEntrada, 0, aux2->chave);
            }
            aux2 = aux2->prox;
        }
        free(aux2);
        aux1 = aux1->prox;
    }
    
    //Imprime uma ordenação topológica possível
    aux1 = vizinhosDeEntrada[0].prox;
    while(aux1 != NULL) {
        printf("%d\n", aux1->chave);
        aux1 = aux1->prox;
    }
    free(aux1);

    libera(vizinhosDeEntrada);
    libera(vizinhosDeSaida);
    vizinhosDeEntrada = NULL;
    vizinhosDeSaida = NULL;
    
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

void libera(no* lista) {
    int i;
    for(i = 0; i <= TAM; i ++) {
        no* atual = lista[i].prox;
        while(atual != NULL) {
            no* prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }
    free(lista);
}
