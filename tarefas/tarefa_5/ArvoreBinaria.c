#include <stdlib.h>
#include <stdio.h>
#include "ArvoreBinaria.h"
#include "conta.h"
#include "cpf.h"

#define COUNT 8
typedef struct node_st NODE;

struct node_st
{
    CONTA *conta;
    NODE *direita;
    NODE *esquerda;
};

struct arvore_binaria
{
    NODE* raiz;
    int profundidade;
};

static void pre_ordem_recursao(NODE *raiz);
static NODE* cria_no(CONTA* conta);
static void troca_min_dir(NODE *troca, NODE *raiz, NODE *ant);
static boolean ehMaior(const NODE *raiz, CONTA *conta);
static boolean ehMenor(const NODE *raiz, CONTA *conta);
static boolean abb_remover_aux (NODE **raiz, CPF *chave);
CONTA *abb_busca_no(NODE *raiz, CPF *chave);

ARVORE_BINARIA *arvore_binaria_criar()
{
    ARVORE_BINARIA *arvore;
    arvore = (ARVORE_BINARIA *) malloc(sizeof(ARVORE_BINARIA));
    if (arvore != NULL) {
        arvore->raiz = NULL;
        arvore->profundidade = -1;
    }
    return arvore;
}

static NODE* cria_no(CONTA *conta)
{
    NODE *novoNode = (NODE *) malloc(sizeof(NODE));
    if (novoNode != NULL) {
        novoNode->conta = conta;
        novoNode->direita = NULL;
        novoNode->esquerda = NULL;
    }
    return novoNode;
}

static void pre_ordem_recursao(NODE *raiz) {
    if (raiz != NULL) {
        cpf_imprimir_semformat(conta_get_cpf(raiz->conta));
        pre_ordem_recursao(raiz->esquerda);
        pre_ordem_recursao(raiz->direita);
    }
}

void arvore_binaria_pre_ordem(ARVORE_BINARIA *arvoreBinaria)
{
    printf("Preorder\n");
    pre_ordem_recursao(arvoreBinaria->raiz);
}

int ab_profundidade(NODE *no) {
    if (no == NULL)
        return -1;
    int e = ab_profundidade(no->esquerda);
    int d = ab_profundidade(no->direita);
    return ((e > d) ? e : d) + 1;
}

void apagar_arvore(NODE **raiz) {
    if (*raiz != NULL) {
        apagar_arvore(&(*raiz)->esquerda);
        apagar_arvore(&(*raiz)->direita);
        conta_apagar(&(*raiz)->conta);
        free(*raiz);
        *raiz = NULL;
    }
}
void ab_apagar_arvore(ARVORE_BINARIA **T) {
    apagar_arvore(&(*T)->raiz);
    free(*T);
    *T = NULL;
}

NODE *abb_inserir_no(NODE *raiz, CONTA *conta){
    if (raiz == NULL)
        raiz = cria_no(conta);
    else if(ehMaior(raiz, conta))
        raiz->direita = abb_inserir_no(raiz->direita,conta);
    else if(ehMenor(raiz, conta))
        raiz->esquerda = abb_inserir_no(raiz->esquerda,conta);
    return raiz;
}

boolean ehMenor(const NODE *raiz, CONTA *conta) {
    return cpf_maior(conta_get_cpf(raiz->conta),conta_get_cpf(conta));
}

boolean ehMaior(const NODE *raiz, CONTA *conta) {
    return cpf_maior(conta_get_cpf(conta),conta_get_cpf(raiz->conta));
}

boolean abb_inserir (ARVORE_BINARIA *T, CONTA *conta){
    if(abb_busca_no(T->raiz,conta_get_cpf(conta))==NULL){
        return((T->raiz = abb_inserir_no(T->raiz, conta)) != NULL);
    }
    
    return FALSE;
}

CONTA *abb_busca_no(NODE *raiz, CPF *chave){
    if(raiz == NULL)
        return NULL;
    if(cpf_igual(chave,conta_get_cpf(raiz->conta)))
        return (raiz->conta);
    if(cpf_maior(conta_get_cpf(raiz->conta), chave))
        return (abb_busca_no(raiz->esquerda, chave));
    else
        return (abb_busca_no(raiz->direita, chave));
}

CONTA *abb_busca(ARVORE_BINARIA *T, CPF *chave){
    return(abb_busca_no(T->raiz, chave));
}

static boolean abb_remover_aux (NODE **raiz, CPF *chave){
    NODE *noRemovido;
    if(*raiz == NULL)
    {
        return FALSE;
    }
    if(cpf_igual(chave, conta_get_cpf((*raiz)->conta)))
    {
        if ((*raiz)->esquerda == NULL|| (*raiz)->direita == NULL)
        {/*Caso 1 se resume ao caso 2: há um filho ou nenhum*/
            noRemovido = *raiz;
            if((*raiz)->esquerda == NULL) {
                *raiz = (*raiz)->direita;
            }
            else {
                *raiz = (*raiz)->esquerda;
            }
            free(noRemovido);
            noRemovido = NULL;
        }
        else /*Caso 3: há ambos os filhos*/
        {
            troca_min_dir((*raiz)->direita, (*raiz), (*raiz));
        }
        return TRUE;
    }
    else
    {
        if(cpf_maior(conta_get_cpf((*raiz)->conta),chave))
            return abb_remover_aux (&(*raiz)->esquerda, chave);
        else
            return abb_remover_aux (&(*raiz)->direita, chave);
    }
}

boolean arvore_binaria_remover(ARVORE_BINARIA *T, CPF *chave){
    if (T != NULL)
        return abb_remover_aux(&T->raiz, chave);
    return FALSE;
}

static void troca_min_dir(NODE *troca, NODE *raiz, NODE *ant)
{
    if(troca->esquerda != NULL)
    {
        troca_min_dir(troca->esquerda, raiz, troca);
        return;
    }
    if(raiz == ant) {
        ant->direita = troca->direita;
    }
    else {
        ant->esquerda = troca->direita;
    }
    raiz->conta = troca->conta;
    free(troca);
    troca = NULL;
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
// https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
static void print2DUtil(NODE *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->direita, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    cpf_imprimir(conta_get_cpf(root->conta));

    // Process left child
    print2DUtil(root->esquerda, space);
}

// Wrapper over print2DUtil()
void arvore_binaria_imprimir(ARVORE_BINARIA *root)
{
    // Pass initial space count as 0
    print2DUtil(root->raiz, 0);
}





