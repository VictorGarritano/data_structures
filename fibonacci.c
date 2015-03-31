#include<stdio.h>

int main()
{
    int n, first = 0, second = 1, contador;
    printf("Entre com o numero de termos: ");
    scanf("%d", &n);
    printf("Os %d primeiros membros da sequencia de Fibonacci sao:\n", n);
    for(contador = 0; contador <= (n-1); ++contador) {
        first += second;
        second = first - second;
        printf("F%d = %d\n",contador, second);
    }

    return 0;
}
