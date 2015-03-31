#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TAM 10

int* vetor;
short int i;
int nelem, inicio, fim;
int* init();
int remove_FO();
int insere_FI(int k);
int filacheia();
int filavazia();
int overflow();

int main()
{
    setlocale(LC_ALL, "Portuguese");
    vetor = init();
    insere_FI(2);
    insere_FI(9);
    insere_FI(1);
    insere_FI(3);
    insere_FI(243);
    insere_FI(65);
    insere_FI(211);
    insere_FI(10);
    remove_FO();
    remove_FO();
    remove_FO();
    remove_FO();
    remove_FO();
    insere_FI(2);
    insere_FI(21);
    insere_FI(69);
    remove_FO();
    insere_FI(4);
    insere_FI(5);
    remove_FO();

    printf("O elemento do in�cio �: %d\n", vetor[inicio]);
    printf("O �ndice do in�cio: %d", inicio);
    printf("\nO �ndice do fim: %d\n", fim);
    printf("O n�mero de elementos �: %d\n", nelem);

    free(vetor);

    return 0;
}

int* init() {
    vetor = (int*) malloc(sizeof(int) * TAM);
    nelem = 0;
    inicio = 0;
    fim = 0;
    return vetor;
}

int remove_FO() {
    if(filavazia()) return 0;
    inicio = (inicio + 1) % TAM;
    nelem--;
    return 1;
}

int insere_FI(int k) {
    if (filacheia()) {
        printf("A fila est� cheia!\n");
    return 0;
    }
    vetor[fim] = k;
    fim = (fim + 1) % TAM;
    nelem++;
    return 1;
}

int filavazia() {
    return (nelem == 0);
}

int filacheia() {
   return (nelem == TAM);
}
