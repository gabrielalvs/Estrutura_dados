#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Catologo.h"
#include "Jogo.h"

struct catalogo_st
{   
    int n_elements;
    int n_jogos;
    JOGO **jogos;
};

CATALOGO *catalogo_new ()
{
    CATALOGO *catalogo;

    catalogo = (CATALOGO *) malloc(sizeof(CATALOGO));

    if (catalogo != NULL)
    {
        catalogo->n_elements = 10;
        catalogo->n_jogos = 0;
        catalogo->jogos = (JOGO **) malloc(catalogo->n_elements * sizeof(JOGO*));
        return catalogo;
    }
    return NULL;
}

boolean catalogo_delete(CATALOGO **catalogo)
{
    if (*catalogo != NULL)
    {
        for(int i = 0; i < (*catalogo)->n_jogos; i++){
            if((*catalogo)->jogos[i] != NULL){
                free((*catalogo)->jogos[i]);
            }
        }
        free((*catalogo)->jogos);
        free(*catalogo);
        *catalogo = NULL;
        return TRUE;
    }
    return FALSE;
}

void catalogo_print(const CATALOGO *catalogo)
{
    if (catalogo != NULL)
    {
        for(int i = 0; i < catalogo->n_jogos; i++){
            if(catalogo->jogos[i] != NULL){
               jogo_print(catalogo->jogos[i]);
            }
        }
    }
}


boolean catalogo_add(CATALOGO *catalogo, JOGO *jogo)
{
    if(catalogo!=NULL && jogo != NULL){
        if(catalogo->n_jogos==catalogo->n_elements){
            catalogo->n_elements *= 2;
            catalogo->jogos = (JOGO **) realloc(catalogo->jogos, sizeof(JOGO*) * catalogo->n_elements);

        }
        catalogo->jogos[catalogo->n_jogos] = jogo;
        catalogo->n_jogos++;
        return TRUE;
    }
    return FALSE;
}

void catalogo_search_ano(const CATALOGO *catalogo, int ano)
{
    int aux = 0;
    for (int i = 0; i < catalogo->n_jogos; i++)
    {
        int aux_ano = jogo_get_ano(catalogo->jogos[i]);

        if(aux_ano == ano)
        {
            printf("%s\n", jogo_get_nome_jogo(catalogo->jogos[i]));
            aux++;
        }
    }

    if(aux==0) printf("Nada encontrado\n");
}

void catalogo_search_nome_empresa(const CATALOGO *catalogo, char *nome_empresa)
{
    int aux = 0;
    for (int i = 0; i < catalogo->n_jogos; i++)
    {   
        char *aux_nome_empresa = jogo_get_nome_empresa(catalogo->jogos[i]);
        if(strcmp(aux_nome_empresa, nome_empresa)==0)
        {       
            printf("%s\n", jogo_get_nome_jogo(catalogo->jogos[i]));
            aux++;
        }
    }

    if(aux==0) printf("Nada encontrado\n");
}

