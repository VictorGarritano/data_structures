#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 2000

int *vetor;
int nelem;
int* init(int* v);
FILE *arq;
void insere(int* v, int x);
int busca(int* v, int x);
void remove_elem(int* v, int x);
void imprime(int* v);
void grava();
void overflow(int* v);
void intercala(int p, int q, int r, int* v);
void mergesort(int p, int r, int* v);


int main()
{
    vetor = init(vetor);
    short int i;
    srand((unsigned)time(NULL));
    for (i = 0; i < 1000; i++) insere(vetor, rand() % 1000);
    printf("Vetor desordenado: \n");
    imprime(vetor);
    mergesort(0,nelem,vetor);
    printf("\nVetor ordenado utilizando o Mergesort: \n");
    imprime(vetor);
    grava();
    printf("\nO vetor tem %d elementos", nelem);
    free(vetor);

    return 0;
}

int* init(int* v) {
    v =(int*) malloc(sizeof(int) * TAM);
    nelem = 0;
    return v;
}

void insere(int* v, int x) {
    if(nelem == TAM) {
        overflow(v);
    }
    v[nelem++] = x;
}

int busca(int* v, int x) {
   int k;
   k = nelem-1;
   while (k >= 0 && v[k] != x)
      k--;
   return k;
}

void remove_elem(int* v, int x) {
    int j;
    for(j = x+1; j<nelem; ++j)
        v[j-1] = v[j];
    nelem--;
}

void imprime(int* v) {
    int i, count;
    for(i=0,count=1;i<nelem;i++,count++) {
        printf("%d ",v[i]);
        if(count==10) {
            printf("\n");
            count=1;
        }
    }
}

void overflow(int* v) {
    v = (int*) realloc(v, TAM*2*sizeof(int));
}

void intercala(int p, int q, int r, int* v) {
   int i, j, k, *w;
   w = (int*) malloc((r-p) * sizeof (int));
   i = p; j = q;
   k = 0;

   while (i < q && j < r) {
      if (v[i] <= v[j])  w[k++] = v[i++];
      else  w[k++] = v[j++];
   }
   while (i < q)  w[k++] = v[i++];
   while (j < r)  w[k++] = v[j++];
   for (i = p; i < r; ++i)  v[i] = w[i-p];
   free( w);
}

void mergesort(int p, int r, int* v) {
   if (p < r-1) {
      int q = (p + r)/2;
      mergesort( p, q, v);
      mergesort( q, r, v);
      intercala( p, q, r, v);
   }
}

void grava() {
    int i, j, count;
    arq = fopen("merge.txt", "w");
    if(arq == NULL) {
        printf("Erro na abertura\n");
        system("pause");
        exit(1);
    }
    for(i=0,count=1;i<nelem;i++,count++) {
        fprintf(arq, "%d ", vetor[i]);
        if(count == 10) {
            fprintf(arq, "\n");
            count = 1;
        }
    }
    printf("\nArquivo com o vetor ordenado foi gravado com sucesso!\n");
    fclose(arq);
}
