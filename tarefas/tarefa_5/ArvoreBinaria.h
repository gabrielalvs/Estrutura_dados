#ifndef TADGENERICO_ARVOREBINARIA_H
#define TADGENERICO_ARVOREBINARIA_H

#include "conta.h"
#include "cpf.h"

#define FILHO_ESQ 0
#define FILHO_DIR 1

typedef struct arvore_binaria ARVORE_BINARIA;

ARVORE_BINARIA *arvore_binaria_criar();
void arvore_binaria_pre_ordem(ARVORE_BINARIA *arvoreBinaria);
boolean abb_inserir (ARVORE_BINARIA *T, CONTA *conta);
boolean arvore_binaria_remover(ARVORE_BINARIA *T, CPF *chave);
void arvore_binaria_imprimir(ARVORE_BINARIA *T);
void ab_apagar_arvore(ARVORE_BINARIA **T);
CONTA *abb_busca(ARVORE_BINARIA *T, CPF *chave);

#endif //TADGENERICO_ARVOREBINARIA_H
