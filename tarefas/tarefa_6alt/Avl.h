#ifndef TADGENERICO_AVL_H
#define TADGENERICO_AVL_H

#include "Jogo.h"

#define TRUE 1
#define FALSE 0
#define boolean char
#define ERRO -32000

#define max(a, b) ((a > b) ? a : b)
typedef struct avl AVL;

void avl_apagar(AVL **arvore);
AVL *avl_criar();
boolean avl_inserir(AVL *arvore, JOGO *jogo);
void arvore_binaria_pre_ordem(AVL *arvoreBinaria);
void arvore_binaria_em_ordem(AVL *arvoreBinaria);
void arvore_binaria_pos_ordem(AVL *arvoreBinaria);
boolean set_jogos_file(AVL *T,const char *nfile);
boolean avl_remover(AVL *T, int chave);
JOGO *avl_busca(AVL *T, int chave);

#endif //TADGENERICO_AVL_H
