#include <stdio.h>
#include <stdlib.h>

//Constantes para o count-min
#define D 5
#define MOD 127
#define INT_MAX 2147483647
#define min(a,b) a < b ? a : b

//Macros para a heap
#define FILHOESQ(x) 2 * x + 1
#define FILHODIR(x) 2 * x + 2
#define PAI(x) x / 2

typedef struct _NO {
	int chave;
	int frequencia;
} no;

typedef struct _MIN_HEAP {
	int tamanho;
	no* elem;
} minHeap;

//Funcoes para a heap
minHeap init();
void insere(no node);
void troca(no *n1, no *n2);
void heapify(int i);
void deleta();
void liberaMinHeap();
void percorrePorNivel();
int achaMin();

//Funcoes para o count-min
void inicializaCMS();
void incrementa(int x);
int estimaFrequencia(int x);
int hash(int x);

minHeap heap;

int cms[D][MOD];

int main(int argc, char *argv[])
{
	int count = 0, n, flag = 0;
	if(argc != 3) {
		printf("Erro!");
		exit(0);
	}

	int k = atoi(argv[2]);
	//Inicializando as estruturas
	heap = init();
	inicializaCMS();

	while(scanf("%d ", &n) != EOF) {
		count++;
       	incrementa(n);
       	int freq = estimaFrequencia(n);
       	no node;
       	if(count < k) {

       	}
       	else if(freq >= count/k) {
       		node.chave = n;
       		node.frequencia = freq;
       		if(heap.tamanho && estimaFrequencia(achaMin()) < count/k) {
       			deleta();
       		}
           	int i;
           	for(i = 0; i < heap.tamanho; i ++) {
           		if(heap.elem[i].chave == n) {
           			flag = 1;
           		}
           	}
           	if(!flag) insere(node);
       	}
   	}
   	
   	percorrePorNivel();
    liberaMinHeap();

	return 0;
}

//Implementacao das funcoes da heap
minHeap init() {
	heap.tamanho = 0;
	return heap;
}

void insere(no node) {
	//Alocando espaço
	if(heap.tamanho)
		heap.elem = realloc(heap.elem, (heap.tamanho + 1) * sizeof(no));
	else {
		heap.elem = malloc(sizeof(no));
	}
	//Posicionando o novo no na posicao correta
	int i = (heap.tamanho)++;
	while(i && node.chave < heap.elem[PAI(i)].frequencia) {
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
	int menor = (FILHOESQ(i) < heap.tamanho && heap.elem[FILHOESQ(i)].frequencia < heap.elem[i].frequencia) ? FILHOESQ(i) : i;
	if (FILHODIR(i) < heap.tamanho && heap.elem[FILHODIR(i)].chave < heap.elem[menor].frequencia) {
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

int hash(int x) {
    return (67 * x + 7919) % MOD;
}


void incrementa(int x) {
    int i;
    for(i = 0; i < D; i++) {
        cms[i][hash(x)]++;
    }
}

int estimaFrequencia(int x) {
    int minimo = INT_MAX;
    int i;
    for(i = 0; i < D; i ++) {
        minimo = min(minimo, cms[i][hash(x)]);
    }
    return minimo;
}
