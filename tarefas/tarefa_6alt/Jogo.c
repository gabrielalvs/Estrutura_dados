#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Jogo.h"

struct jogo_st
{   char nome_jogo[100];
    char produtora[100];
    int ano;
};

JOGO *jogo_new (const char *nome_jogo, const char *produtora, int ano)
{
    JOGO *jogo;

    jogo = (JOGO *) malloc(sizeof(JOGO));

    if (jogo != NULL)
    {
        strcpy(jogo->nome_jogo, nome_jogo);
        strcpy(jogo->produtora, produtora);
        jogo->ano = ano;
        return jogo;
    }
    return NULL;
}

boolean jogo_delete(JOGO **jogo)
{
    if (*jogo != NULL)
    {
        free (*jogo);
        *jogo = NULL;
        return TRUE;
    }
    return FALSE;
}

void jogo_print(const JOGO *jogo)
{
    if (jogo != NULL)
    {
        printf("%s\n", jogo->nome_jogo);
    }
}

int jogo_get_ano(JOGO *jogo)
{
    if (jogo != NULL)
    {
       return jogo->ano;
    }

    return -1;
}

char *jogo_get_produtora(JOGO *jogo)
{
    if (jogo != NULL)
    {
       return jogo->produtora;
    }

    return NULL;
}

char *jogo_get_nome_jogo(JOGO *jogo)
{
    if (jogo != NULL)
    {
       return jogo->nome_jogo;
    }

    return NULL;
}
