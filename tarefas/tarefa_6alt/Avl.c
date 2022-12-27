#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Avl.h"

typedef struct node_st NODE;

static void avl_apagar_aux(NODE **raiz);

static NODE *avl_inserir_no_e_rotacionar(NODE *raiz, JOGO *jogo);

static boolean DesbalanceamentoEhNegativo(NODE *raiz);

static boolean DesbalanceamentoEhPositivo(NODE *raiz);

static boolean ItemEhMaior(NODE *raiz, JOGO *jogo);

static boolean ItemEhMenor(NODE *raiz, JOGO *jogo);

static NODE *selecionar_e_executar_rotacao(NODE *raiz, JOGO *jogo);

static NODE *inserir_no(NODE *raiz, JOGO *jogo); 

static void pre_ordem_recursao(NODE *raiz);

static void em_ordem_recursao(NODE *raiz);

static void pos_ordem_recursao(NODE *raiz);

static JOGO *avl_busca_no(NODE *raiz, int chave);

struct node_st
{
    JOGO *jogo;
    NODE *direita;
    NODE *esquerda;
    int altura;
};

struct avl
{
    NODE* raiz;
    int profundidade;
};

AVL *avl_criar() {
    AVL *arvore = (AVL *) malloc(sizeof(AVL));
    if (arvore != NULL) {
        arvore->raiz = NULL;
        arvore->profundidade = -1;
    }
    return arvore;
}

static void avl_apagar_aux(NODE **raiz) {
    if (*raiz != NULL) {
        avl_apagar_aux(&((*raiz)->esquerda));
        avl_apagar_aux(&((*raiz)->direita));
        jogo_delete(&(*raiz)->jogo);
        free(*raiz);
    }
}

void avl_apagar(AVL **arvore) {
    avl_apagar_aux(&(*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

int avl_altura_no(NODE* raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->altura;
    }
}

NODE *avl_cria_no(JOGO *jogo) {
    NODE *no = (NODE *) malloc(sizeof (NODE));
    if (no != NULL) {
        no->altura = 0;
        no->direita = NULL;
        no->esquerda = NULL;
        no->jogo = jogo;
    }
    return no;
}

NODE *rodar_direita(NODE *a) {
    NODE *b = a->esquerda;
    a->esquerda = b->direita;
    b->direita = a;

    a->altura = max(avl_altura_no(a->esquerda),avl_altura_no(a->direita)) + 1;
    b->altura = max(avl_altura_no(b->esquerda),a->altura) + 1;

    return b;
}

NODE *rodar_esquerda(NODE *a) {
    NODE *b = a->direita;
    a->direita = b->esquerda;
    b->esquerda = a;

    a->altura = max(avl_altura_no(a->esquerda),avl_altura_no(a->direita)) + 1;
    b->altura = max(avl_altura_no(b->direita),a->altura) + 1;

    return b;
}

NODE *rodar_esquerda_direita(NODE *a)   {
    a->esquerda = rodar_esquerda(a->esquerda);
    return rodar_direita(a);
}

NODE *rodar_direita_esquerda(NODE *a)   {
    a->direita = rodar_direita(a->direita);
    return rodar_esquerda(a);
}

static NODE *avl_inserir_no_e_rotacionar(NODE *raiz, JOGO *jogo) {
    raiz = inserir_no(raiz, jogo);

    raiz->altura = max(avl_altura_no(raiz->esquerda), avl_altura_no(raiz->direita)) + 1;

    raiz = selecionar_e_executar_rotacao(raiz, jogo);

    return raiz;
}

static NODE *inserir_no(NODE *raiz, JOGO *jogo) {
    if (raiz == NULL) {
        raiz = avl_cria_no(jogo);
    }
    else if (ItemEhMaior(raiz, jogo)) {
        raiz->direita = avl_inserir_no_e_rotacionar(raiz->direita, jogo);
    }
    else if (ItemEhMenor(raiz, jogo)) {
        raiz->esquerda = avl_inserir_no_e_rotacionar(raiz->esquerda, jogo);
    }
    
    
    return raiz;
}

static NODE *selecionar_e_executar_rotacao(NODE *raiz, JOGO *jogo) {
    if (DesbalanceamentoEhNegativo(raiz)) {
        if (ItemEhMaior(raiz->direita, jogo)) {
            raiz = rodar_esquerda(raiz);
        }
        else {
            raiz = rodar_direita_esquerda(raiz);
        }
    }

    if (DesbalanceamentoEhPositivo(raiz)) {
        if (ItemEhMenor(raiz->esquerda, jogo))
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);
    }
    return raiz;
}

static boolean ItemEhMenor(NODE *raiz, JOGO *jogo) {
    if(jogo_get_ano(jogo) == jogo_get_ano(raiz->jogo)){
        return strcmp(jogo_get_nome_jogo(jogo), jogo_get_nome_jogo(raiz->jogo)) < 0;
    }else{
        return jogo_get_ano(jogo) < jogo_get_ano(raiz->jogo);
    }
}

static boolean ItemEhMaior(NODE *raiz, JOGO *jogo) {
    if(jogo_get_ano(jogo) == jogo_get_ano(raiz->jogo)){
        return strcmp(jogo_get_nome_jogo(jogo), jogo_get_nome_jogo(raiz->jogo)) > 0;
    }else{
        return jogo_get_ano(jogo) > jogo_get_ano(raiz->jogo);
    }
}

static boolean DesbalanceamentoEhPositivo(NODE *raiz) {
    return avl_altura_no(raiz->esquerda) - avl_altura_no(raiz->direita) == 2;
}

static boolean DesbalanceamentoEhNegativo(NODE *raiz) {
    return avl_altura_no(raiz->esquerda) - avl_altura_no(raiz->direita) == -2;
}

boolean avl_inserir(AVL *arvore, JOGO *jogo) {
    arvore->raiz = avl_inserir_no_e_rotacionar(arvore->raiz, jogo);
    return arvore->raiz != NULL;
}

boolean set_jogos_file(AVL *T,const char *nfile)
{   
    char *nome_jogo;
    char *produtora;
    int ano = 0;

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(nfile, "r");
    if (fp == NULL)
        return FALSE;
    
    fseek(fp, 3, SEEK_SET);

    while ((read = getline(&line, &len, fp)) != -1) {

        nome_jogo = strsep(&line, ";");
        ano = atoi(strsep(&line, ";"));
        produtora = strsep(&line, ";");

        if (avl_inserir(T,jogo_new(nome_jogo,produtora,ano))!=TRUE)
        {
            return FALSE;
        }
        
    }

    fclose(fp);
    if (line)
        free(line);

  return TRUE;
}

static void pre_ordem_recursao(NODE *raiz) {
    if (raiz != NULL) {
        jogo_print(raiz->jogo);
        pre_ordem_recursao(raiz->esquerda);
        pre_ordem_recursao(raiz->direita);
    }
}

static void em_ordem_recursao(NODE *raiz) {
    if (raiz != NULL) {
        em_ordem_recursao(raiz->esquerda);
        jogo_print(raiz->jogo);
        em_ordem_recursao(raiz->direita);
    }
}

static void pos_ordem_recursao(NODE *raiz) {
    if (raiz != NULL) {
        pos_ordem_recursao(raiz->esquerda);
        pos_ordem_recursao(raiz->direita);
        jogo_print(raiz->jogo);
    }
}

void arvore_binaria_pre_ordem(AVL *arvoreBinaria)
{
    pre_ordem_recursao(arvoreBinaria->raiz);
}

void arvore_binaria_em_ordem(AVL *arvoreBinaria)
{
    em_ordem_recursao(arvoreBinaria->raiz);
}

void arvore_binaria_pos_ordem(AVL *arvoreBinaria)
{
    pos_ordem_recursao(arvoreBinaria->raiz);
}

static void troca_max_esq(NODE *troca, NODE *raiz, NODE *ant)
{
    if(troca->direita != NULL)
    {
        troca_max_esq(troca->direita, raiz, troca);
        return;
    }
    if(raiz == ant) {
        ant->esquerda = troca->esquerda;
    }
    else {
        ant->direita = troca->esquerda;
    }
    raiz->jogo = troca->jogo;
    free(troca);
    troca = NULL;
}

NODE *avl_remover_aux(NODE **raiz, int chave) {
    NODE *p;

    if (raiz == NULL){
        return NULL;
    }else if (chave == jogo_get_ano((*raiz)->jogo)){
        if((*raiz)->esquerda == NULL || (*raiz)->direita == NULL){
            p = *raiz;
            if((*raiz)->esquerda == NULL)
                *raiz = (*raiz)->direita;
            else
                *raiz = (*raiz)->esquerda;
            free (p);
            p = NULL;
        }else{
            troca_max_esq((*raiz)->esquerda, (*raiz), (*raiz));
        }
    }else if(chave < jogo_get_ano((*raiz)->jogo)){
        (*raiz)->esquerda = avl_remover_aux(&(*raiz)->esquerda, chave);
    }else if(chave > jogo_get_ano((*raiz)->jogo)){
        (*raiz)->direita = avl_remover_aux(&(*raiz)->direita, chave);
    }

    if(*raiz != NULL) {
        (*raiz)->altura = max(avl_altura_no((*raiz)->esquerda), avl_altura_no((*raiz)->direita))+1;
        if(avl_altura_no((*raiz)->esquerda) - avl_altura_no((*raiz)->direita) == -2) {
            if(avl_altura_no((*raiz)->direita->esquerda) - avl_altura_no((*raiz)->direita->direita) <= 0) {
                //printf("\n rodar esquerda...");
                *raiz = rodar_esquerda(*raiz);
            } else {
                //printf("\n rodar direita_esquerda...");
                *raiz = rodar_direita_esquerda(*raiz);
            }
        }

        if(avl_altura_no((*raiz)->esquerda) - avl_altura_no((*raiz)->direita) == 2) {
            if(avl_altura_no((*raiz)->esquerda->esquerda) - avl_altura_no((*raiz)->esquerda->direita) >= 0) {
                //printf("\n rodar direita...");
                *raiz = rodar_direita(*raiz);
            } else {
                //printf("\n rodar esquerda_direita...");
                *raiz = rodar_esquerda_direita(*raiz);
            }
        }
    }
    return *raiz;
}

boolean avl_remover(AVL *T, int chave){
    if (T != NULL){
        while (avl_busca_no(T->raiz,chave)!=NULL)
        {
           T->raiz = avl_remover_aux(&T->raiz,chave);
        }
    }
        
    return FALSE;
}

static JOGO *avl_busca_no(NODE *raiz, int chave){
    if(raiz == NULL)
        return NULL;
    if(chave == jogo_get_ano(raiz->jogo))
        return (raiz->jogo);
    if(chave < jogo_get_ano(raiz->jogo))
        return (avl_busca_no(raiz->esquerda, chave));
    else
        return (avl_busca_no(raiz->direita, chave));
}

JOGO *avl_busca(AVL *T, int chave){
    return(avl_busca_no(T->raiz, chave));
}




