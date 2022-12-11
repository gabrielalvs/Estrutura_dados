#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "conta.h"
#include "cpf.h"

struct conta_st
{
    CPF *cpf;
    char nome[50];
    int idade;
    float saldo;
};

CONTA *conta_criar(char *str)
{
    CONTA *conta;

    conta = (CONTA *) malloc(sizeof(CONTA));

    if (conta != NULL)
    {

        char *cpf = strsep(&str, ";");
        char *nome = strsep(&str, ";");
        int idade = atoi(strsep(&str, ";"));
        float saldo = atof(str);

        conta->cpf = cpf_criar(cpf);
        strcpy(conta->nome, nome);
        conta->idade = idade;
        conta->saldo = saldo;
        return conta;
    }
    return NULL;
}

boolean conta_apagar(CONTA **conta)
{
    if (*conta != NULL)
    {
        cpf_apagar(&(*conta)->cpf);
        free (*conta);
        *conta = NULL;
        return TRUE;
    }
    return FALSE;
}

void conta_imprimir(const CONTA *conta)
{
    if (conta != NULL)
    {
        printf("Conta :: %s\n", conta->nome);
        cpf_imprimir(conta->cpf);
        printf("Idade :: %i\n", conta->idade);
        printf("Saldo atual :: R$ %.2f\n", conta->saldo);
    }
}

CPF *conta_get_cpf(CONTA *conta)
{
    if (conta != NULL)
    {
       return conta->cpf;
    }

    return NULL;
}