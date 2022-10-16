#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Jogo.h"

struct jogo_st
{   char nome_jogo[100];
    char nome_empresa[100];
    int ano;
};

JOGO *jogo_new (const char *nome_jogo, const char *nome_empresa, int ano)
{
    JOGO *jogo;

    jogo = (JOGO *) malloc(sizeof(JOGO));

    if (jogo != NULL)
    {
        strcpy(jogo->nome_jogo, nome_jogo);
        strcpy(jogo->nome_empresa, nome_empresa);
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
        printf("%s\n", jogo->nome_empresa);
        printf("%d\n", jogo->ano);
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

char *jogo_get_nome_empresa(JOGO *jogo)
{
    if (jogo != NULL)
    {
       return jogo->nome_empresa;
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
