#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBinaria.h"
#include "conta.h"
#include "cpf.h"


char *readLine();

int main() {
    ARVORE_BINARIA *arvore_binaria = arvore_binaria_criar();

    int control;
    scanf("%d\n", &control);
    int i = 0;


    while(i < control) {
        CONTA *conta = conta_criar(readLine());
        abb_inserir(arvore_binaria, conta);
        i++;
    }

    char aux_control;
    //arvore_binaria_imprimir(arvore_binaria);
    scanf("%c\n", &aux_control);
    
    if(aux_control == 'I'){
        CONTA * conta = conta_criar(readLine());
        abb_inserir(arvore_binaria, conta);
        arvore_binaria_pre_ordem(arvore_binaria);
    }else if(aux_control == 'B') {
        CONTA * conta  = abb_busca(arvore_binaria, cpf_criar(readLine()));
        if (conta==NULL)
        {
            printf("Pessoa nao encontrada.\n");
        }
        conta_imprimir(conta);
    }else if(aux_control == 'R'){
        CONTA * conta  = abb_busca(arvore_binaria, cpf_criar(readLine()));
        if (conta==NULL)
        {
            printf("Pessoa nao encontrada.\n");
        }
        conta_imprimir(conta);
        arvore_binaria_remover(arvore_binaria, conta_get_cpf(conta));
        arvore_binaria_pre_ordem(arvore_binaria);
    }

    printf("\n");
    //arvore_binaria_imprimir(arvore_binaria);
    ab_apagar_arvore(&arvore_binaria);
}

char *readLine() {
    char *string = NULL;
    char currentInput;
    int index = 0;
    do {
        currentInput = (char) getchar();
        string = (char *) realloc(string, sizeof(char) * (index + 1));
        string[index] = currentInput;
        index++;
        if(currentInput == '\r')
        {
            currentInput = (char)getchar();
        }
    } while((currentInput != '\n') && (currentInput != EOF));
    string[index - 1] = '\0';
    return string;
}