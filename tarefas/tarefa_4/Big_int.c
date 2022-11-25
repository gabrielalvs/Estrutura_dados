#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Big_int.h"
#include "Util.h"

#define N_alg 4
typedef struct classe_st CLASSE;

struct classe_st
{
    int numero;
    CLASSE* proximo;
};

struct big_int_st {
    CLASSE* cabeca;
    CLASSE* fim;
    int tamanho;
    int sinal;
};

static void big_int_remove_tudo(BIG_INT *big_int);
static int big_int_inserir(BIG_INT *big_int, int numero);
static void big_int_imprimir_recursivo(BIG_INT *big_int, CLASSE *classeAtual);
static boolean big_int_comparacao_igual(BIG_INT *big_int_1, BIG_INT *big_int_2, CLASSE *classe_1, CLASSE *classe_2);
static boolean big_int_comparaca_maior(BIG_INT *big_int_1, BIG_INT *big_int_2, CLASSE *classe_1, CLASSE *classe_2);

static BIG_INT *big_int_criar_vazio()
{
    BIG_INT *big_int = (BIG_INT*) malloc(sizeof(BIG_INT));
    if(big_int != NULL)
    {
        big_int->cabeca = (CLASSE*) malloc(sizeof(CLASSE));
        if(big_int->cabeca == NULL)
        {
            return NULL;
        }
        big_int->cabeca->proximo = NULL;
        big_int->fim = NULL;
        big_int->tamanho = 0;
        big_int->sinal=1;
    }
    return big_int;
}

boolean big_int_vazia(const BIG_INT *big_int)
{
    if((big_int != NULL) && (big_int->cabeca->proximo == NULL))
    {
        return TRUE;
    }
    return FALSE;
}

int lista_tamanho(const BIG_INT *big_int) {
    if(big_int != NULL)
    {
        return big_int->tamanho;
    }
    return ERRO;
}

BIG_INT* big_int_criar(char *algarismos)
{
    BIG_INT *big_int = big_int_criar_vazio();
    int aux_numero = 0;
    int digito = 0;

    if(big_int != NULL)
    {
        int n_char = (int)strlen(algarismos);

        for (int i = n_char-1; i >= 0; i--)
        {
            if (algarismos[i]=='-')
            {
                big_int->sinal*=-1;
                if (aux_numero>0)
                {
                    big_int_inserir(big_int, aux_numero);
                }

                return big_int;
            }

            digito = (int)algarismos[i]-(int)'0'; 

            aux_numero += (digito * pow(10, (n_char-i-1) % (N_alg)));
    
            if(((n_char-i-1)%(N_alg)==N_alg-1 || i==0)){
                big_int_inserir(big_int, aux_numero);
                aux_numero=0;
            }
        }
         return big_int;
    }
    return NULL;
}

static int big_int_inserir(BIG_INT *big_int, int numero)
{
    if(big_int != NULL)
    {
        CLASSE *novaClasse = (CLASSE *) malloc(sizeof(CLASSE));
        if (novaClasse != NULL) {
            novaClasse->numero = numero;
            novaClasse->proximo = NULL;
            if(big_int_vazia(big_int))
            {
                big_int->cabeca->proximo = novaClasse;
            }
            else
            {
                big_int->fim->proximo = novaClasse;
            }
            big_int->fim = novaClasse;
            big_int->tamanho++;
        
            return TRUE;
        }
    }
    return ERRO;
}

boolean big_int_apagar(BIG_INT **big_int)
{
    if ((*big_int != NULL) && (!big_int_vazia(*big_int)))
    {
        big_int_remove_tudo(*big_int);
        free (*big_int);
        *big_int = NULL;
        return TRUE;
    }
    return FALSE;
}


static void big_int_remove_tudo(BIG_INT *big_int)
{
    CLASSE *classeAtual;
    classeAtual = big_int->cabeca;
    while((classeAtual->proximo != NULL))
    {
        CLASSE *classeRemovido;
        classeRemovido = classeAtual;
        classeAtual = classeRemovido->proximo;
        classeRemovido->proximo = NULL;
        big_int->tamanho--;
        free(classeRemovido);
        classeRemovido = NULL;
    }

    free(classeAtual);
    classeAtual = NULL;
    big_int->cabeca = NULL;
    big_int->fim = NULL;
}

BIG_INT *big_int_somar(BIG_INT *big_int_1, BIG_INT *big_int_2)
{

    BIG_INT *big_int_3 = big_int_criar_vazio();
    CLASSE *classeAux1 = big_int_1->cabeca->proximo;
    CLASSE *classeAux2 = big_int_2->cabeca->proximo;
    int aux;
    int resto = 0;
    int Valor_max = pow(10, N_alg);

    while((classeAux1 != NULL) || (classeAux2 != NULL) || resto != 0)
    {

        aux = resto;

        if(classeAux1 != NULL){
            aux += classeAux1->numero;
            classeAux1 = classeAux1->proximo;
        }

        if(classeAux2 != NULL){
            aux += classeAux2->numero;
            classeAux2 = classeAux2->proximo;;
        }

        resto = aux/Valor_max;
        aux = aux % Valor_max;
        big_int_inserir(big_int_3, aux);
    }

    return big_int_3;
}

void big_int_imprimir(BIG_INT *big_int)
{
    if( big_int != NULL){
        big_int_imprimir_recursivo(big_int, big_int->cabeca->proximo);
    }
}

static void big_int_imprimir_recursivo(BIG_INT *big_int, CLASSE *classeAtual){

   if( classeAtual != NULL){

        if(classeAtual==big_int->fim){
            if (big_int->sinal==-1){
                printf("-");
            }
            printf("%d",classeAtual->numero);
        }
        else{
            big_int_imprimir_recursivo(big_int,classeAtual->proximo);
            printf("%.4d",classeAtual->numero);
        }  
   }
}

boolean big_int_igual(BIG_INT *big_int_1, BIG_INT *big_int_2){

    if(big_int_vazia(big_int_1) && big_int_vazia(big_int_2)){
        return FALSE;
    }
        
    if(big_int_1->tamanho!=big_int_2->tamanho || big_int_1->sinal!=big_int_2->sinal){
        return FALSE;
    }

    if(big_int_comparacao_igual(big_int_1,big_int_2,big_int_1->cabeca->proximo,big_int_2->cabeca->proximo)==TRUE){
        return TRUE;
    }else{
        return FALSE;
    }
}

boolean big_int_maior(BIG_INT *big_int_1, BIG_INT *big_int_2)
{
    if(big_int_1==NULL && big_int_2==NULL){
        return FALSE;
    }

    if(big_int_1->sinal!=big_int_2->sinal){
        return (big_int_1->sinal > big_int_2->sinal ? TRUE:FALSE);
    }
    if(big_int_1->tamanho != big_int_2->tamanho){
         if(big_int_1->sinal==1){
            return (big_int_1->tamanho > big_int_2->tamanho ? TRUE:FALSE);
         }else{
            return (big_int_1->tamanho > big_int_2->tamanho ? FALSE:TRUE);
         }  
    }

    if(big_int_comparaca_maior(big_int_1,big_int_2,big_int_1->cabeca->proximo,big_int_2->cabeca->proximo)==TRUE){
        return TRUE;
    }

    return FALSE;
}

static boolean big_int_comparacao_igual(BIG_INT *big_int_1, BIG_INT *big_int_2, CLASSE *classe_1, CLASSE *classe_2)
{

    if(classe_1==big_int_1->fim){

         if(classe_1->numero == classe_2->numero){
            return TRUE;
         }

        return FALSE;

    }else{

        if (big_int_comparacao_igual(big_int_1, big_int_2, classe_1->proximo, classe_2->proximo) == TRUE){

            if(classe_1->numero == classe_2->numero){
                return TRUE;
            }
            return FALSE;
        }

        return FALSE;
    }
}

static boolean big_int_comparaca_maior(BIG_INT *big_int_1, BIG_INT *big_int_2, CLASSE *classe_1, CLASSE *classe_2)
{

    if(classe_1==big_int_1->fim){

        if(classe_1->numero > classe_2->numero){
            return TRUE;
        }

        return FALSE;

    }else{

        if (big_int_comparaca_maior(big_int_1, big_int_2, classe_1->proximo, classe_2->proximo) == TRUE){
            return TRUE;
        }

        if((classe_1->proximo->numero == classe_2->proximo->numero) && (classe_1->numero > classe_2->numero)){
            return TRUE;
        }

        return FALSE;
    }
}