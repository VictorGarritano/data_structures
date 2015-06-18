#include <stdio.h>
#include <stdlib.h>

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

minHeap init();
void insere(int chave);
void troca(no *n1, no *n2);
void heapify(int i);
void deleta();
void deletaMinHeap();
void percorrePorNivel();
int achaMin();

minHeap heap;

int main(void)
{
	heap = init();
	insere(95);
	insere(60);
	insere(78);
	insere(39);
	insere(28);
	insere(66);
	insere(70);
	insere(33);
	insere(18);
	percorrePorNivel();
	deletaMinHeap();
	return 0;
}

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
	no* temp = n1;
	n1 = n2;
	n2 = temp;
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

void deletaMinHeap() {
	free(heap.elem);
}

void percorrePorNivel() {
	int i;
	for(i = 0; i < heap.tamanho; i++) {
		printf("%d ", heap.elem[i].chave);
	}
}

int achaMin() {
	return heap.elem[0].chave;
}
