#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdio.h>
#include "Util.h"

#define INICIO 0
#define ERRO (-32000)


typedef struct big_int_st BIG_INT;

BIG_INT* big_int_criar(char *algarismos);
boolean big_int_apagar(BIG_INT **big_int);
BIG_INT *big_int_somar(BIG_INT *big_int_1, BIG_INT *big_int_2);
void big_int_imprimir(BIG_INT *big_int);
boolean big_int_igual(BIG_INT *big_int_1, BIG_INT *big_int_2);
boolean big_int_maior(BIG_INT *big_int_1, BIG_INT *big_int_2);

#endif //LISTA_H

