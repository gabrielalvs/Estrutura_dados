#ifndef CATALOGO_H
#define CATALOGO_H

#define TRUE 1
#define FALSE 0
#define boolean char
#define ERRO -32000
#include "Jogo.h"

typedef struct catalogo_st CATALOGO;

CATALOGO *catalogo_new();
boolean catalogo_delete(CATALOGO **catalogo);
void catalogo_print(const CATALOGO *catalogo);
boolean catalogo_add(CATALOGO *catalogo, JOGO *jogo);
void catalogo_search_ano(const CATALOGO *catalogo, int ano);
void catalogo_search_nome_empresa(const CATALOGO *catalogo, char *nome_empresa);

#endif //CATALOGO_H
