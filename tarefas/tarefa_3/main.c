#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Jogo.h"
#include "Catologo.h"

int main (void){
    CATALOGO *catalogo;
    catalogo = catalogo_new();

    //catalogo_add(catalogo, jogo_new("teste", "teste", 2001));
    //jogo_print(catalogo_search_ano(catalogo, 2001));
    //jogo_print(catalogo_search_nome_empresa(catalogo, "teste"));

    char aux_control[ 100 ];
    char nome_empresa[ 100 ];
    int ano = 0;

    while (TRUE)
    {   
        scanf(" %[^(\r|\n)]",aux_control);
        if (strcmp(aux_control,"F")==0) break;

        scanf(" %[^(\r|\n)]",nome_empresa);
        scanf ("%d", &ano);
        catalogo_add(catalogo, jogo_new(aux_control, nome_empresa, ano));
    }

    while (TRUE)
    {   
        scanf(" %[^(\r|\n)]",aux_control);
        if (strcmp(aux_control,"F")==0) break;

        if (strcmp(aux_control, "A") == 0)
        {
            scanf ("%d", &ano);
            catalogo_search_ano(catalogo, ano);
        }

        if (strcmp(aux_control, "E") == 0)
        {
            scanf(" %[^(\r|\n)]",nome_empresa);
            catalogo_search_nome_empresa(catalogo, nome_empresa);
        }
    }

    //catalogo_print(catalogo);
    catalogo_delete(&catalogo);

    return 0;
}