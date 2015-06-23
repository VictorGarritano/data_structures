#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Constantes para o count-min
#define D 5
#define MOD 127
#define min(a,b) a < b ? a : b

//Macros para a heap
#define FILHOESQ(x) 2 * x + 1
#define FILHODIR(x) 2 * x + 2
#define PAI(x) x / 2

typedef struct _NO {
	int chave;
} no;

typedef struct _MIN_HEAP {
	int tamanho;
	no* elem;
} minHeap;

//Funcoes para a heap
minHeap init();
void insere(int chave);
void troca(no *n1, no *n2);
void heapify(int i);
void deleta();
void liberaMinHeap();
void percorrePorNivel();
int achaMin();

//Funcoes para o count-min
void inicializaCMS();
void inicializaHashes();
void incrementa(int x);
int estimaFrequencia(int x);
int hash(int x, int i);
int mod(int x);

minHeap heap;
int cms[D][MOD];
int a[D], b[D];

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

//Implementacao das funcoes da heap
minHeap init() {
	heap.tamanho = 0;
	return heap;
}

void insere(int chave) {
	//Alocando espaço
	if(heap.tamanho)
		heap.elem = realloc(heap.elem, (heap.tamanho + 1) * sizeof(no));
	else {
		heap.elem = malloc(sizeof(no));
	}
	//Inicializando no com a chave
	no node;
	node.chave = chave;
	//Posicionando o novo no na posicao correta
	int i = (heap.tamanho)++;
	while(i && node.chave < heap.elem[PAI(i)].chave) {
		heap.elem[i] = heap.elem[PAI(i)];
		i = PAI(i);
	}
	heap.elem[i] = node;
}

void troca(no *n1, no *n2) {
	no temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

void heapify(int i) {
	int menor = (FILHOESQ(i) < heap.tamanho && heap.elem[FILHOESQ(i)].chave < heap.elem[i].chave) ? FILHOESQ(i) : i;
	if (FILHODIR(i) < heap.tamanho && heap.elem[FILHODIR(i)].chave < heap.elem[menor].chave) {
		menor = FILHODIR(i);
	}
	if(menor != i) {
		troca(&(heap.elem[i]), &(heap.elem[menor]));
		heapify(menor);
	}
}

void deleta() {
	if(heap.tamanho) {
		heap.elem[0] = heap.elem[--(heap.tamanho)];
		heap.elem = realloc(heap.elem, heap.tamanho * sizeof(no));
		heapify(0);
	}
	else {
		free(heap.elem);
	}
}


void percorrePorNivel() {
	int i;
	for(i = 0; i < heap.tamanho; i++) {
		printf("%d ", heap.elem[i].chave);
	}
		printf("\n");
}

int achaMin() {
	return heap.elem[0].chave;
}

void liberaMinHeap() {
    free(heap.elem);
}


//Funcoes para o count-min
void inicializaCMS() {
    int i, j;
    for(i = 0; i < D; i++) {
        for(j = 0; j < MOD; j ++) {
            cms[i][j] = 0;
        }
    }
}

void inicializaHashes() {
    int i;
    for(i = 0; i < D; i++) {
        a[i] = rand() % MOD;
        b[i] = rand() % MOD;
    }
}

int hash(int x, int i) {
    return mod((a[i] * x + b[i]));
}

int mod(int x) {
    (x = x % MOD) > 0 ? x : x + MOD;
}

void incrementa(int x) {
    int i;
    for(i = 0; i < D; i++) {
        cms[i][hash(x,i)]++;
    }
}

int estimaFrequencia(int x) {
    int minimo = INT_MAX;
    int i;
    for(i = 0; i < D; i ++) {
        minimo = min(minimo, cms[i][hash(x, i)]);
    }
    return minimo;
}
