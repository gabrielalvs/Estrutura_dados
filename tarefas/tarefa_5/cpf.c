#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cpf.h"

struct cpf_st
{
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int verificador;
};

CPF *cpf_criar(const char *cpfString)
{
    CPF *cpf;

    cpf = (CPF*) malloc(sizeof(CPF));

    if (cpf != NULL)
    {
        sscanf(cpfString, "%03u.%03u.%03u-%02u", &cpf->a, &cpf->b, &cpf->c, &cpf->verificador);
        return cpf;
    }
    return NULL;
}

boolean cpf_apagar(CPF **cpf)
{
    if (*cpf != NULL)
    {
        free (*cpf);
        *cpf = NULL;
        return TRUE;
    }
    return FALSE;
}

void cpf_imprimir(const CPF *cpf)
{
    if (cpf != NULL)
    {
        char buffer[15];
        sprintf(buffer, "%03d.%03d.%03d-%02d", cpf->a,cpf->b,cpf->c,cpf->verificador);
        printf("CPF :: %s\n", buffer);
    }
}

boolean cpf_igual(CPF *cpf1, CPF *cpf2)
{
    if(cpf1 != NULL && cpf2 != NULL)
    {
        if((cpf1->a == cpf2->a) && (cpf1->b == cpf2->b) && (cpf1->c == cpf2->c) && (cpf1->verificador == cpf2->verificador))
        {
            return TRUE;
        }
    }

    return FALSE;
}

boolean cpf_maior(CPF *cpf1, CPF *cpf2)
{
    if(cpf1 != NULL && cpf2 != NULL){
        if (!cpf_igual(cpf1,cpf2))
        {
            if (cpf1->a > cpf2->a){
                return TRUE;
            }else if(cpf1->a < cpf2->a){
                return FALSE;
            }

            if (cpf1->b > cpf2->b){
                return TRUE;
            }else if(cpf1->b < cpf2->b){
                return FALSE;
            }

            if (cpf1->c > cpf2->c){
                return TRUE;
            }else if(cpf1->c < cpf2->c){
                return FALSE;
            }

            if (cpf1->verificador > cpf2->verificador){
                return TRUE;
            }else if(cpf1->verificador < cpf2->verificador){
                return FALSE;
            }
        }
    }

    return FALSE;
}

void cpf_imprimir_semformat(const CPF *cpf)
{
    if (cpf != NULL)
    {
        char buffer[15];
        sprintf(buffer, "%03d%03d%03d%02d", cpf->a,cpf->b,cpf->c,cpf->verificador);
        printf("%s\n", buffer);
    }
}