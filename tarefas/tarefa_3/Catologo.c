#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Catologo.h"
#include "Jogo.h"

struct catologo_st
{   
    int n_elements;
    int n_jogos;
    JOGO **jogos;
};

CATALOGO *catologo_new ()
{
    CATALOGO *catologo;

    catologo = (CATALOGO *) malloc(sizeof(CATALOGO));

    if (catologo != NULL)
    {
        catologo->n_elements = 10;
        catologo->n_jogos = 0;
        catologo->jogos = (JOGO **) malloc(catologo->n_elements * sizeof(JOGO*));
        return catologo;
    }
    return NULL;
}

boolean catologo_delete(CATALOGO **catologo)
{
    if (*catologo != NULL)
    {
        for(int i = 0; i < (*catologo)->n_jogos; i++){
            if((*catologo)->jogos[i] != NULL){
                free((*catologo)->jogos[i]);
            }
        }
        free((*catologo)->jogos);
        free(*catologo);
        *catologo = NULL;
        return TRUE;
    }
    return FALSE;
}

void catologo_print(const CATALOGO *catologo)
{
    if (catologo != NULL)
    {
        for(int i = 0; i < catologo->n_jogos; i++){
            if(catologo->jogos[i] != NULL){
               jogo_print(catologo->jogos[i]);
            }
        }
    }
}


boolean catologo_add(CATALOGO *catologo, JOGO *jogo)
{
    if(catologo!=NULL && jogo != NULL){
        if(catologo->n_jogos==catologo->n_elements){
            catologo->n_elements *= 2;
            catologo->jogos = (JOGO **) realloc(catologo->jogos, sizeof(JOGO*) * catologo->n_elements);

        }
        catologo->jogos[catologo->n_jogos] = jogo;
        catologo->n_jogos++;
        return TRUE;
    }
    return FALSE;
}
