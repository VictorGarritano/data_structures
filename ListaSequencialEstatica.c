#define MAX 100

//Definicao dos tipos de estruturas que serao utilizadas 

struct aluno{
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

struct lista{
    int qtd;
    struct aluno dados[MAX];
};

typedef struct lista Lista;


struct aluno cria_aluno(struct aluno a);
Lista* cria_lista();
void libera_lista(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);
int lista_vazia(Lista* li);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista_final(Lista* li);
int remove_lista_inicio(Lista* li);
int remove_lista(Lista* li, int mat);
int consulta_lista_pos(Lista* li, int pos, struct aluno *al);
int consulta_lista_mat(Lista* li, int mat, struct aluno *al);

//Main

int main()
{
    struct aluno a1, a2, a3, *c;
    a1 = cria_aluno(a1);
    a2 = cria_aluno(a2);
    a3 = cria_aluno(a3);

    Lista* li = cria_lista();
    insere_lista_inicio(li,a3);
    insere_lista_final(li, a1);
    insere_lista_ordenada(li,a2);

    printf("\nO tamanho da lista e: %d", tamanho_lista(li));

    consulta_lista_pos(li, 1, c);
    printf("\nA matricula do aluno na pos 1 e: %d\n", c->matricula);
    printf("O nome do aluno na pos 1 e: %s\n", c->nome);
    printf("As notas do aluno na pos 1 sao: (%.1f, %.1f, %.1f)\n", c->n1, c->n2, c->n3);

    remove_lista_final(li);

    printf("\nO tamanho da lista e : %d\n", tamanho_lista(li));

    libera_lista(li);

   return 0;

}

//Implementacao dos prototipos de funcoes

Lista* cria_lista() {
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if(li != NULL) {
        li->qtd = 0;
    }
    return li;
}

struct aluno cria_aluno(struct aluno a) {
    printf("Entre com a matricula do aluno: ");
    scanf("%d", &a.matricula);
    printf("\nEntre com o nome do aluno: ");
    getchar();
    fgets(a.nome, sizeof a.nome, stdin);
    printf("\nEntre com as notas do aluno separadas por espaco: ");
    scanf("%f %f %f", &a.n1, &a.n2, &a.n3);
    printf("\nAluno criado com sucesso.\n\n");
    return a;
};

void libera_lista(Lista* li) {
    free(li);
}

int tamanho_lista(Lista* li) {
    if(li == NULL) {
        return -1;
    }
    else {
        return li->qtd;
    }
}

int lista_cheia(Lista* li) {
    if(li == NULL) {
        return -1;
    }
    return(li->qtd == MAX);
}

int lista_vazia(Lista* li) {
    if(li == NULL) {
        return -1;
    }
    return(li->qtd == 0);
}

int insere_lista_final(Lista* li, struct aluno al) {
    if(li == NULL) {
        return 0;
    }
    if(lista_cheia(li)) {
        return 0;
    }
    li->dados[li->qtd] = al;
    li->qtd++;
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al) {
    if(li == NULL) return 0;
    if(lista_cheia(li)) return 0;
    int i;
    for(i = li->qtd-1; i>=0; i--) {
        li->dados[i+1] = li->dados[i];
    }
    li->dados[0] = al;
    li->qtd++;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if(li == NULL) return 0;
    if(lista_cheia(li)) return 0;
    int k, i = 0;
    while(i < li->qtd && li->dados[i].matricula < al.matricula)
        i++;
    for(k = li->qtd-1; k >= i; k--)
        li->dados[k+1] = li->dados[k];
    li->dados[i] = al;
    li->qtd++;
    return 1;
}

int remove_lista_final(Lista* li) {
    if(li == NULL) return 0;
    if(li->qtd == 0) return 0;
    li->qtd--;
    return 1;
}

int remove_lista_inicio(Lista* li) {
    if(li == NULL) return 0;
    if(li->qtd == 0) return 0;
    int k = 0;
    for(k = 0; k < li->qtd-1; k++)
        li->dados[k] = li->dados[k+1];
    li->qtd--;
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if(li == NULL) return 0;
    if(li->qtd == 0) return 0;
    int k, i = 0;
    while(i < li->qtd && li->dados[i].matricula != mat)
        i++;
    if(i == li->qtd) return 0;
    for(k = i; k < li->qtd-1; k++)
        li->dados[k] = li->dados[k+1];
    li->qtd--;
    return 1;
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al) {
    if(li == NULL || pos <= 0 || pos > li->qtd) return 0;
    *al = li->dados[pos-1];
    return 1;
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al) {
    if(li == NULL) return 0;
    int k, i = 0;
    while(i < li->qtd && li->dados[i].matricula != mat)
        i++;
    if(i == li->qtd) return 0;
    *al = li->dados[i];
    return 1;
}

