#include "TAD3.h"
#include<stdio.h>
#include<stdlib.h>

#define MAX 7

struct fila
{
    struct carros no[MAX];
    int ini, fim;
};



Fila cria_fila()
{
    Fila F;
    F = (Fila)malloc(sizeof(struct fila));

    if(F != NULL)
    {
        F->ini = 0;
        F->fim = 0;
    }

    return F;

}

int fila_vazia(Fila F)
{
    if(F->ini == F->fim)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int fila_cheia(Fila F)
{
    if(F->ini == (F->fim+1)%MAX)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int insere_fim(Fila F, struct carros C)
{
    if(fila_cheia(F)== 1)
    {
        return 0;
    }
    else
    {
        F->no[F->fim] = C;
        F->fim = (F->fim+1)%MAX;

        return 1;
    }
}

int remove_ini(Fila F, struct carros *C)
{
    if(fila_vazia(F)==1)
    {
        return 0;
    }
    else
    {
        *C = F->no[F->ini];
        F->ini = (F->ini+1)%MAX;

        return 1;
    }
}

int tamanho(Fila F)
{
   return F == NULL ? -1 : F->fim >= F->ini ? F->fim - F->ini : MAX - (F->ini - F->fim);
}

int apaga_fila(Fila *F)
{
    free(*F);
    *F = NULL;
}
