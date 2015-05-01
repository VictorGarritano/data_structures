#include <stdio.h>
#include <stdlib.h>

typedef struct _NO {
    int chave;
    struct _NO* prox;
} no;

int TAM, aresta, key;
no* vizinhosDeEntrada;
no* vizinhosDeSaida;

no* init(no* lista);
void insere(no* lista, int vertice, int chave);
void libera(no* lista);
// void imprime(no* lista);

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
    char *buffer;
    char string[1000];
    
    for(i = 0; i < TAM; i++) {
        fgets(string, sizeof(string), stdin);
        buffer = strtok (string," ");
        while(buffer != NULL) {
            if(sscanf(buffer, " %d", &key) == -1)
                printf("Nenhuma tarefa depende da tarefa %d.\n", i + 1);
            else {
                printf("A tarefa %d depende da tarefa %d.\n", key, i + 1);
                insere(vizinhosDeSaida, i + 1, key);
                insere(vizinhosDeEntrada, key, i + 1);
            }
            buffer = strtok (NULL, " ");
        }
    }
    free(buffer);
/*
Roda em O(n + m):
->Esse não precisa percorrer a lista inteira para encontrar uma nova fonte...
->Esse for que segue é mais um pré-processamento, que será nossa lista encadeada de fontes.
    Iteraremos por ela ao invés de percorrermos a lista toda quando precisarmos de uma nova fonte.

    for(i = 1; i < TAM + 1; i ++) {
        if(vizinhosDeEntrada[i].chave == 0) {
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
    free(aux1);

->Imprime a lista de fontes

    aux1 = vizinhosDeEntrada[0].prox;
    while(aux1 != NULL) {
        printf("%d ", aux1->chave);
        aux1 = aux1->prox;
    }
    free(aux1);

*/


/* Roda em tempo O(n^2 + m): 
n * T("encontrar a fonte") + m(nº de arestas)...
    
    int objeto = TAM;
    while(objeto != 0) {
        for(i = 1; i < TAM + 1; i ++) {
            if(vizinhosDeEntrada[i].chave == 0) {
                no* aux = vizinhosDeSaida[i].prox;
                saida[k] = i;
                vizinhosDeEntrada[i].chave = -1;
                k++;
                objeto--;
                while(aux != NULL) {
                    vizinhosDeEntrada[aux->chave].chave--;
                    aux = aux->prox;
                }
            }
        }
    }

*/
    for(i = 0; i < k; i ++) {
        printf("%d ", saida[i]);
    }

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

// void imprime(no* lista){
//     int i;
//     no* tmp;
//     for(i = 1; i < TAM + 1; i++) {
//         tmp = lista[i].prox;
//         printf("%2d: (%d) ==> ", i, lista[i].chave);
//         while (tmp != NULL) {
//             printf("%d  ", tmp->chave);
//             tmp = tmp->prox;
//         }
//         printf("\n");
//     }
// }