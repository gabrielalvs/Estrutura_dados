#ifndef CATALOGO_H
#define CATALOGO_H

#define TRUE 1
#define FALSE 0
#define boolean char
#define ERRO -32000
#include "Jogo.h"

typedef struct catologo_st CATALOGO;

CATALOGO *catologo_new();
boolean catologo_delete(CATALOGO **catologo);
void catologo_print(const CATALOGO *catologo);
boolean catologo_add(CATALOGO *catologo, JOGO *jogo);

#endif //CATALOGO_H
