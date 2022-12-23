#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ArvoreBinaria.h"

#define COUNT 8
typedef struct node_st NODE;

struct node_st
{
    JOGO *jogo;
    NODE *direita;
    NODE *esquerda;
    int altura;
};

struct arvore_binaria
{
    NODE* raiz;
    int profundidade;
};

static void pre_ordem_recursao(NODE *raiz);
static void em_ordem_recursao(NODE *raiz);
static void pos_ordem_recursao(NODE *raiz);
static NODE* cria_no(JOGO* jogo);
static void troca_max_esq(NODE *troca, NODE *raiz, NODE *ant);
//static boolean ehMaior(NODE *raiz, JOGO *jogo);
//static boolean ehMenor(NODE *raiz, JOGO *jogo);
static boolean abb_remover_aux (NODE **raiz, int chave);
static int altura(NODE *raiz);
static int max(int a, int b); 
static int getBalance(NODE *no);
//static int profundidade(NODE *no);
static NODE *rightRotate(NODE *y);
static NODE *leftRotate(NODE *x);
static void print2DUtil(NODE *root, int space);
boolean comparar_maior(JOGO *jogo1, JOGO *jogo2);

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

static NODE* cria_no(JOGO *jogo)
{
    NODE *novoNode = (NODE *) malloc(sizeof(NODE));
    if (novoNode != NULL) {
        novoNode->jogo = jogo;
        novoNode->direita = NULL;
        novoNode->esquerda = NULL;
        novoNode->altura = 1;
    }
    return novoNode;
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

void arvore_binaria_pre_ordem(ARVORE_BINARIA *arvoreBinaria)
{
    pre_ordem_recursao(arvoreBinaria->raiz);
}

void arvore_binaria_em_ordem(ARVORE_BINARIA *arvoreBinaria)
{
    em_ordem_recursao(arvoreBinaria->raiz);
}

void arvore_binaria_pos_ordem(ARVORE_BINARIA *arvoreBinaria)
{
    pos_ordem_recursao(arvoreBinaria->raiz);
}

void apagar_arvore(NODE **raiz) {
    if (*raiz != NULL) {
        apagar_arvore(&(*raiz)->esquerda);
        apagar_arvore(&(*raiz)->direita);
        jogo_delete(&(*raiz)->jogo);
        free(*raiz);
        *raiz = NULL;
    }
}

void ab_apagar_arvore(ARVORE_BINARIA **T) {
    apagar_arvore(&(*T)->raiz);
    free(*T);
    *T = NULL;
}

NODE *insertNode(NODE *raiz, JOGO *jogo) 
{

    if (raiz == NULL)
        return cria_no(jogo);
    //else if(ehMaior(raiz, jogo))
    else if(comparar_maior(jogo, raiz->jogo))
        raiz->direita = insertNode(raiz->direita,jogo);
    //else if(ehMenor(raiz, jogo))
    else if(comparar_maior(raiz->jogo, jogo))
        raiz->esquerda = insertNode(raiz->esquerda,jogo);
    else
        return raiz;   

    raiz->altura = 1 + max(altura(raiz->esquerda),altura(raiz->direita));

    int balance = getBalance(raiz);

    //if (balance > 1 && ehMenor(raiz->esquerda, jogo)){//key < node->left->key
    if (balance > 1 && comparar_maior(raiz->esquerda->jogo, jogo)){
        return rightRotate(raiz);
    } 

    //if (balance < -1 && ehMaior(raiz->direita, jogo)){//key > node->right->key
    if (balance < -1 && comparar_maior(jogo, raiz->direita->jogo)){
        return leftRotate(raiz);
    } 
        
    //if (balance > 1 && ehMaior(raiz->esquerda, jogo)) { //key > node->left->key
    if (balance > 1 && comparar_maior(jogo, raiz->esquerda->jogo)) {
        raiz->esquerda = leftRotate(raiz->esquerda);
        return rightRotate(raiz);
    }

    //if (balance < -1 && ehMenor(raiz->direita, jogo)) { //key < node->right->key
    if (balance < -1 && comparar_maior(raiz->direita->jogo, jogo)) {
        raiz->direita = rightRotate(raiz->direita);
        return leftRotate(raiz);
    }

  return raiz;
}

/*boolean ehMenor(NODE *raiz, JOGO *jogo) {
    if(jogo_get_ano(jogo) == jogo_get_ano(raiz->jogo)){
        if (strcmp(jogo_get_nome_jogo(jogo), jogo_get_nome_jogo(raiz->jogo)) < 0)
        {
            return TRUE;
        }else{
            return FALSE;
        }
    }else{
        return jogo_get_ano(jogo) < jogo_get_ano(raiz->jogo);
    }
}

boolean ehMaior(NODE *raiz, JOGO *jogo) {
    if(jogo_get_ano(jogo) == jogo_get_ano(raiz->jogo)){
         if (strcmp(jogo_get_nome_jogo(jogo), jogo_get_nome_jogo(raiz->jogo)) > 0)
        {
            return TRUE;
        }else{
            return FALSE;
        }
    }else{
        return jogo_get_ano(jogo) > jogo_get_ano(raiz->jogo);
    }
}*/

boolean comparar_maior(JOGO *jogo1, JOGO *jogo2){
    if(jogo_get_ano(jogo1) == jogo_get_ano(jogo2)){
        return strcmp(jogo_get_nome_jogo(jogo1), jogo_get_nome_jogo(jogo2)) > 0;
    }else{
        return jogo_get_ano(jogo1) > jogo_get_ano(jogo2);
    }
}

boolean arvore_binaria_inserir(ARVORE_BINARIA *T, JOGO *jogo){
    return((T->raiz = insertNode(T->raiz, jogo)) != NULL);
}

JOGO *abb_busca_no(NODE *raiz, int chave){
    if(raiz == NULL)
        return NULL;
    if(chave == jogo_get_ano(raiz->jogo))
        return (raiz->jogo);
    if(chave < jogo_get_ano(raiz->jogo))
        return (abb_busca_no(raiz->esquerda, chave));
    else
        return (abb_busca_no(raiz->direita, chave));
}

JOGO *abb_busca(ARVORE_BINARIA *T, int chave){
    return(abb_busca_no(T->raiz, chave));
}

static boolean abb_remover_aux(NODE **raiz, int chave){
    NODE *noRemovido;
    
    if(*raiz == NULL)
    {
        return FALSE;
    }

    if(chave == jogo_get_ano((*raiz)->jogo))
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
            troca_max_esq((*raiz)->esquerda, (*raiz), (*raiz));
        }

        (*raiz)->altura = 1 + max(altura((*raiz)->esquerda),altura((*raiz)->direita));

        int balance = getBalance((*raiz));

        if (balance > 1 && getBalance((*raiz)->esquerda) >= 0){ 
            (*raiz) = rightRotate((*raiz));
            return TRUE;
        }

        if (balance > 1 && getBalance((*raiz)->esquerda) < 0) {
            (*raiz)->esquerda = leftRotate((*raiz)->esquerda);
            (*raiz) = rightRotate((*raiz));
            return TRUE;
        }

        if (balance < -1 && getBalance((*raiz)->direita) <= 0){
            (*raiz) = leftRotate((*raiz));
            return TRUE;
        }

        if (balance < -1 && getBalance((*raiz)->direita) > 0) {
            (*raiz)->direita = rightRotate((*raiz)->direita);
            (*raiz) = leftRotate((*raiz));
            return TRUE;
        }

        return TRUE;
    }
    else
    {
        if(chave < jogo_get_ano((*raiz)->jogo))
            return abb_remover_aux (&(*raiz)->esquerda, chave);
        else
            return abb_remover_aux (&(*raiz)->direita, chave);
    }

}

boolean arvore_binaria_remover(ARVORE_BINARIA *T, int chave){
    if (T != NULL){

        boolean flag = TRUE;

        while (flag)
        {
            flag = abb_remover_aux(&T->raiz, chave);
        }
        
        return TRUE;
    }
        
    return FALSE;
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

static int altura(NODE *raiz) {
  if (raiz == NULL)
    return 0;
  return raiz->altura;
}

/*static int profundidade(NODE *no) {
    if (no == NULL)
        return -1;
    int e = profundidade(no->esquerda);
    int d = profundidade(no->direita);
    return ((e > d) ? e : d) + 1;
}*/

static int max(int a, int b) {
  return (a > b) ? a : b;
}

static int getBalance(NODE *no) {
  if (no == NULL)
    return 0;
  return altura(no->esquerda) - altura(no->direita);
}

// Right rotate
static NODE *rightRotate(NODE *y) {
    NODE *x = y->esquerda;
    NODE *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

// Left rotate
static NODE *leftRotate(NODE *x) {
    NODE *y = x->direita;
    NODE *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

boolean set_jogos_file(ARVORE_BINARIA *T,const char *nfile)
{   
    char *nome_jogo;
    char *produtora;
    int ano = 0;

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(nfile, "r");
    if (fp == NULL)
        return FALSE;

    while ((read = getline(&line, &len, fp)) != -1) {

        nome_jogo = strsep(&line, ";");
        ano = atoi(strsep(&line, ";"));
        produtora = strsep(&line, ";");

        //printf(" nome jogo: %s ano: %d produtora: %s \n",nome_jogo, ano, produtora);

        if (arvore_binaria_inserir(T,jogo_new(nome_jogo,produtora,ano))!=TRUE)
        {
            return FALSE;
        }
        
        
    }

    fclose(fp);
    if (line)
        free(line);

  return TRUE;
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
    jogo_print(root->jogo);

    // Process left child
    print2DUtil(root->esquerda, space);
}

// Wrapper over print2DUtil()
void arvore_binaria_imprimir(ARVORE_BINARIA *root)
{
    // Pass initial space count as 0
    print2DUtil(root->raiz, 0);
}




