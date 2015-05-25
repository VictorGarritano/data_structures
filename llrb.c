#include <stdio.h>
#include <stdlib.h>

typedef struct _NO
{
    int chave;
    struct _NO *esq;
    struct _NO *dir;
    char cor;
} no;

int isRed(no* x);
no* novoNo(int chave);
no* insere(no* no, int chave);
no*insereLL(no* no, int chave);
no* rodaEsquerda(no* x);
no* rodaDireita(no* h);
no* recolore(no* h);
void preOrdem(no* raiz);
void libera(no* raiz);

no* raiz;
char string[1000];
char comando;
int chave;

int main(void) {

    raiz = NULL;

    while(fgets(string, sizeof(string), stdin) != NULL) {
        sscanf(string, "%c %d", &comando, &chave);
        if(comando == 'p')
            preOrdem(raiz);
        else if(comando == 'i') {
            raiz = insereLL(raiz, chave);
        }
    }

    return 0;
}

int isRed(no* x) {
    if(x == NULL)
        return 0;
    return(x->cor == 'R');
}

no* novoNo(int chave) {
    no* node = (no*)malloc(sizeof(no));
    node->chave = chave;
    node->esq = node->dir = NULL;
    node->cor = 'R';
    return node;
}

no* insere(no* no, int chave) {
    if(no == NULL)
        return(novoNo(chave));

    if(isRed(no->esq) && isRed(no->dir))
        recolore(no);

    if(chave < no->chave)
        no->esq = insere(no->esq, chave);
    else
        no->dir = insere(no->dir, chave);

    if(isRed(no->dir))
        no = rodaEsquerda(no);

    if(isRed(no->esq) && isRed(no->esq->esq))
        no = rodaDireita(no);

    return no;
}

no*insereLL(no* no, int chave) {
    no = insere(no, chave);
    no->cor = 'N';
    return no;
}

no* rodaEsquerda(no* x) {
    no* y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    y->cor = (y->esq)->cor;
    (y->esq)->cor = 'R';

    return y;
}

no* rodaDireita(no* h) {
    no* x = h->esq;
    h->esq = x->dir;
    x->dir = h;
    x->cor = (x->dir)->cor;
    (x->dir)->cor = 'R';
    return x;
}

no* recolore(no* h) {
    if(isRed(h))
        h->cor = 'N';
    else
        h->cor = 'R';

    if(isRed(h->esq))
        (h->esq)->cor = 'N';
    else
        (h->esq)->cor = 'R';

    if(isRed(h->dir))
        (h->dir)->cor = 'N';
    else
        (h->dir)->cor = 'R';

    return h;
}

void preOrdem(no* raiz) {

    if(raiz != NULL) {
        printf("%d %c\n", raiz->chave, raiz->cor);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}
void libera(no* raiz) {

    if(raiz == NULL)
        return;
    libera(raiz->esq);
    libera(raiz->dir);
    free(raiz);
}
