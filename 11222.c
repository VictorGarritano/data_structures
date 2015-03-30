#include <stdio.h>
#include <stdlib.h>

int T, i, j, k, S, numero, cont1, cont2, cont3, max;
int** amigo;
int** resolvido;
int** alocaMatriz(int Linhas,int Colunas);
void liberaMatriz(int** m, int Colunas);

int main(){
    amigo = alocaMatriz(3,10001);
    if(amigo == NULL){
        printf("Socorro! malloc devolveu NULL!\n");
        exit(EXIT_FAILURE);
    }
    resolvido = alocaMatriz(3,10001);
    if(resolvido == NULL){
        printf("Socorro! malloc devolveu NULL!\n");
        exit(EXIT_FAILURE);
    }
    scanf("%d", &T);
    for(i = 0; i < T; i++) {
        printf("Case #%d:\n",i+1);
        for(j = 0; j < 3; j++) {
            scanf("%d", &S);
            for(k = 0; k < S; k++){
                scanf("%d", &numero);
                amigo[j][numero] = numero;
            }
        }
        cont1 = 0;
        cont2 = 0;
        cont3 = 0;
        for(k = 0; k <= 10000; k ++) {
            if(amigo[0][k]!=0 && amigo[1][k]==0 && amigo[2][k]==0){
                resolvido[0][cont1] = amigo[0][k];
                cont1++;
            }
            else if(amigo[0][k]==0 && amigo[1][k]!=0 && amigo[2][k]==0 ){
                resolvido[1][cont2]=amigo[1][k];
                cont2++;
            }

            else if(amigo[0][k]==0 && amigo[1][k]==0 && amigo[2][k]!=0){
                resolvido[2][cont3] = amigo[2][k];
                cont3++;
            }
        }
        max = -1;
        if(max<cont1) max=cont1;
        if(max<cont2) max=cont2;
        if(max<cont3) max=cont3;

        if(max==cont1){
            printf("%d %d", 1, max);
            for(k = 0; k < max; k++)printf(" %d",resolvido[0][k]);
            printf("\n");
        }
        if(max==cont2){
            printf("%d %d", 2, max);
            for(k = 0; k < max; k++)printf(" %d",resolvido[1][k]);
            printf("\n");
        }
        if(max==cont3){
            printf("%d %d", 3, max);
            for(k = 0; k < max; k++)printf(" %d",resolvido[2][k]);
            printf("\n");
        }

        for(k=0;k<=10000;k++){
            amigo[0][k]=0;
            amigo[1][k]=0;
            amigo[2][k]=0;
        }
    }

    liberaMatriz(amigo,10001);
    liberaMatriz(resolvido,10001);
    return 0;
}

int** alocaMatriz(int Linhas,int Colunas){
    int i,j;
    int **m = (int**)malloc(Linhas * sizeof(int*));
    for (i = 0; i < Linhas; i++){
        m[i] = (int*) malloc(Colunas * sizeof(int));
        for (j = 0; j < Colunas; j++){
            m[i][j] = 0;
       }
    }
    return m;
}

void liberaMatriz(int** m, int Colunas) {
    int i;
    for(i = 0; i < Colunas; i ++) {
        free(m[Colunas]);
    }
    free(m);
}
