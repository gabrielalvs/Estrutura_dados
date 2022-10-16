#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Jogo.h"

struct jogo_st
{   char nome_jogo[20];
    char nome_empresa[20];
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
        printf("\n-->Nome do jogo: %s\n", jogo->nome_jogo);
        printf("\n-->Nome da empresa : %s\n", jogo->nome_empresa);
        printf("\n-->Ano de lançamento: %d\n", jogo->ano);
    }
}
