#ifndef CONTA_H
#define CONTA_H

#define ERRO (-32000)
#define TRUE 1
#define FALSE 0
typedef int boolean;
#include "cpf.h"

typedef struct conta_st CONTA;

CONTA *conta_criar(char *str);
boolean conta_apagar(CONTA **conta);
void conta_imprimir(const CONTA *conta);
CPF *conta_get_cpf(CONTA *conta);
#endif //CONTA_H
