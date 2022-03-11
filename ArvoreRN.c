#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct no{
    int chave;
    char cor;
    struct no *esq, *dir, *pai;
} No;
No *externo = NULL;
No *novoNo(int chave){
    No *n = (No *)malloc(sizeof(No));
    n->chave = chave;
    n->cor = 'R';
    n->esq = externo;
    n->dir = externo;
    n->pai = externo;
    return n;
}
typedef struct rubronegra{
    No *raiz;

} rn;
rn *criaRN() {
    if (externo == NULL)
    {
        externo = (No *) malloc(sizeof(No));
        externo->cor = 'N';
        externo->dir = externo;
        externo->esq = externo;
        externo->pai = externo;
    }
    rn *novaArv = (rn *) malloc(sizeof(rn));
    novaArv->raiz = externo;
    return novaArv;
}
No *sucessor(No *x){
    No *y = x;

    while (y->esq != externo)
    {
        y = y->esq;
    }

    return y;
}
No *buscaNo(No *x, int chave){
    if (x == externo || x->chave == chave)
    {
        return x;
    }
    if (chave < x->chave)
    {
        buscaNo(x->esq, chave);
    }
    else
    {
        buscaNo(x->dir, chave);
    }
}
void rotacaoE(rn *ptraiz, No *x){
    No *y = x->dir;

    x->dir = y->esq;

    if(y->esq != externo)
    {
        y->esq->pai = x;
    }

    y->pai = x->pai;

    if(x->pai == externo)
    {
        ptraiz->raiz = y;
    }
    else if(x == x->pai->esq)
    {
        x->pai->esq = y;
    }
    else
    {
        x->pai->dir = y;
    }

    y->esq = x;
    x->pai = y;
}
void rotacaoD(rn *ptraiz, No *x){
    No *y = x->esq;

    x->esq = y->dir;

    if(y->dir != externo)
    {
        y->dir->pai = x;
    }

    y->pai = x->pai;

    if (x->pai == externo)
    {
        ptraiz->raiz = y;
    }
    else if(x == x->pai->dir)
    {
        x->pai->dir = y;
    }
    else
    {
        x->pai->esq = y;
    }

    y->dir = x;
    x->pai = y;
}
void moverPai(No *u, No *v, rn *ptraiz){
    if(u->pai == externo)
    {
        ptraiz->raiz = v;
    }
    else
    {
        if(u == u->pai->esq)
        {
            u->pai->esq = v;
        }
        else
        {
            u->pai->dir = v;
        }
    }

    v->pai = u->pai;
}
int inserirRN(rn *ptraiz, int chave){
    No *y = externo;
    No *z = novoNo(chave);
    No *pt = ptraiz->raiz;

    while(pt != externo)
    {
        y = pt;

        if(z->chave == pt->chave)
        {
            printf("Chave existente.\n\n");
            y = NULL;
            pt = externo;
            return 1;
        }
        else
        {
            if(z->chave < pt->chave)
            {
                pt = pt->esq;
            }
            else
            {
                pt = pt->dir;
            }
        }
    }

    if(y != NULL)
    {
        z->pai = y;

        if(y == externo)
        {
            ptraiz->raiz = z;
        }
        else
        {
            if(z->chave < y->chave)
            {
                y->esq = z;
            }
            else
            {
                y->dir = z;
            }
        }

        z->esq = externo;
        z->dir = externo;
        z->cor = 'R';
        rotaRN(z, ptraiz);
    }

    return 0;
}
void rotaRN(No *z, rn *ptraiz){
    while(z->pai->cor == 'R')
    {
        if(z->pai == z->pai->pai->esq)
        {
            No *y = z->pai->pai->dir;

            if(y->cor == 'R')
            {
                z->pai->cor = 'N';
                y->cor = 'N';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            }
            else
            {
                if(z == z->pai->dir)
                {
                    z = z->pai;
                    rotacaoE(ptraiz, z);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'R';
                rotacaoD(ptraiz, z->pai->pai);
            }
        }
        else
        {
            No *y = z->pai->pai->esq;

            if(y->cor == 'R')
            {
                z->pai->cor = 'N';
                y->cor = 'N';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            }
            else
            {
                if(z == z->pai->esq)
                {
                    z = z->pai;
                    rotacaoD(ptraiz, z);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'R';
                rotacaoE(ptraiz, z->pai->pai);
            }
        }
    }

    ptraiz->raiz->cor = 'N';
}
void removerRN(No *z, rn *ptraiz){
     No *y;
    No *x;
    y = z;
    char corOriginal = y->cor;

    if(z->esq == externo)
    {
        x = z->dir;
        moverPai(z, z->dir, ptraiz);
    }
    else
    {
        if(z->dir == externo)
        {
            x = z->esq;
            moverPai(z, z->esq, ptraiz);
        }
        else
        {
            y = sucessor(z->dir);
            corOriginal = y->cor;

            x = y->dir;
            if(y->pai == z)
            {
                x->pai = y;
            }
            else
            {
                moverPai(y, y->dir, ptraiz);
                y->dir = z->dir;
                y->dir->pai = y;
            }

            moverPai(z, y, ptraiz);
            y->esq = z->esq;
            y->esq->pai = y;
        }
    }

    if(corOriginal == 'N')
    {
        rotaRemoverRN(x, ptraiz);
    }

    ptraiz->raiz->cor = 'N';
}
void rotaRemoverRN(No *x, rn *ptraiz){
    No *w;

    while (x != ptraiz->raiz && x->cor == 'N')
    {
        if(x == x->pai->esq)
        {
            w = x->pai->dir;

            if(w->cor == 'R')
            {
                w->cor = 'N';
                x->pai->cor = 'R';
                rotacaoE(ptraiz, x->pai);
                w = x->pai->dir;
            }

            if(w->esq->cor == 'N' && w->dir->cor == 'N')
            {
                w->cor = 'R';
                x = x->pai;
            }
            else
            {
                if(w->dir->cor == 'N')
                {
                    w->esq->cor = 'N';
                    w->cor = 'R';
                    rotacaoD(ptraiz, w);
                    w = x->pai->dir;
                }

                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->dir->cor = 'N';
                rotacaoE(ptraiz, x->pai);
                x = ptraiz->raiz;
            }
        }
        else
        {
            w = x->pai->esq;

            if(w->cor == 'R')
            {
                w->cor = 'N';
                x->pai->cor = 'R';
                rotacaoD(ptraiz, x->pai);
                w = x->pai->esq;
            }

            if(w->dir->cor == 'N' && w->esq->cor == 'N')
            {
                w->cor = 'R';
                x = x->pai;
            }
            else
            {
                if(w->esq->cor == 'N')
                {
                    w->dir->cor = 'N';
                    w->cor = 'R';
                    rotacaoE(ptraiz, w);
                    w = x->pai->esq;
                }

                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->esq->cor = 'N';
                rotacaoD(ptraiz, x->pai);
                x = ptraiz->raiz;
            }
        }
    }

    x->cor = 'N';
}
int buscaR(rn *ptraiz, int chave){
    No *z = buscaNo(ptraiz->raiz, chave);
    No *aux = z;

    if(z == externo)
    {
        return 1;
    }
    else
    {
        removerRN(z, ptraiz);
    }

    free(aux);

    return 0;
}
void preOrdem(No *x){
    if (x == externo)
    {
        return;
    }
    printf("%d [%c] ", x->chave, x->cor);
    preOrdem(x->esq);
    preOrdem(x->dir);
}
void imprimirNo(rn *arv) {
    preOrdem(arv->raiz);
    printf("\n");
}
int ContaNo(No *x){
    if (x == externo)
    {
        return 0;
    }

    return 1 + ContaNo(x->esq) + ContaNo(x->dir);
}
int Contagem(rn *arv) {
    return ContaNo(arv->raiz);
}
int CalculaAltura(rn *arv) {
    return altura(arv->raiz);
}
int altura (No *pt) {
    if(pt == externo)
    {
        return 0;
    }

    int esquerda = 1 + altura(pt->esq);
    int direita = 1 + altura(pt->dir);
    printf("%d %d [%d] \n",esquerda, direita, pt->chave);
    if(direita > esquerda){
        return direita;
    }
    else{
        return esquerda;
    }
}

int corNe=0, corNd=0;

int alturaNegra(No *pt) {
    if(pt == externo)
    {
        return 0;
    }
    else if(pt->cor == 'N'){
        return corNe = 1 + alturaNegra(pt->esq);
        return corNd = 1 + alturaNegra(pt->dir);
    }
    else{
        int corNa = alturaNegra(pt->esq);
        int corNb = alturaNegra(pt->dir);
    }
}

void CalculaNegros(rn *arv)
{
    int numEsq = alturaNegra(arv->raiz->esq);
    int NumDir = alturaNegra(arv->raiz->dir);

    if(numEsq == NumDir){
        printf("RN!!!\n");
    } else{
        printf("Nao RN!!!\n");
    }
}

int main()
{
    int NumNo = 1000, NumRN= 100,NosQFicar = 900;
    int j = 0, i, n, k, verificador = 1;
    int vetor[NumNo];
    for (i = 0; i < NumRN; i++)
    {
        j = 0;
        rn *T = criaRN();

        while(Contagem(T) < NumNo){
            n = rand() % 100000;
            verificador = inserirRN(T, n);

            if(verificador == 0){
                vetor[j] = n;
                j++;
            }
        }

        while(Contagem(T) > NosQFicar){
            buscaR(T, vetor[rand() % NumNo]);
        }

        CalculaNegros(T);

        printf("\n");
        imprimirNo(T);
        printf("\n");
        printf("%d numero de No: %d\n",i+1,Contagem(T));
        free(T);

    }

    return 0;
}
