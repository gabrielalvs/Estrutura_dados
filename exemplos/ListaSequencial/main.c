#include <stdio.h>
#include "Pilha.h"
#include "Util.h"

void testeEmpilhaEDesempilha();
void testeEmpilhaMuitos();
void testeEmpilhaStdin();

int main()
{
    testeEmpilhaStdin();
    return 0;
}

void testeEmpilhaStdin()
{
    PILHA *pilha;
    pilha = pilha_criar();
    ITEM *item = item_ler_std_in();
    pilha_empilhar(pilha, item);
    item = item_ler_std_in();
    pilha_empilhar(pilha, item);
    item_imprimir(pilha_topo(pilha));
    item_imprimir(pilha_desempilhar(pilha));
    boolean_print(pilha_vazia(pilha));
    pilha_apagar(&pilha);
}

void testeEmpilhaEDesempilha()
{
    PILHA *pilha;
    pilha = pilha_criar();
    ITEM *item = item_criar(0, "Exodia", "bla bla", 100, 100);
    pilha_empilhar(pilha, item);
    item_imprimir(pilha_topo(pilha));
    item_imprimir(pilha_desempilhar(pilha));
    boolean_print(pilha_vazia(pilha));
    pilha_apagar(&pilha);
}

void testeEmpilhaMuitos()
{
    PILHA *pilha;
    pilha = pilha_criar();
    ITEM *item = item_criar(0, "Exodia, The Forbidden One", "bla bla", 1000, 1000);
    pilha_empilhar(pilha, item);
    item = item_criar(0, "Blue Eyes White Dragon", "bla bla", 3000, 2500);
    pilha_empilhar(pilha, item);
    item_imprimir(pilha_topo(pilha));
    item_imprimir(pilha_desempilhar(pilha));
    boolean_print(pilha_vazia(pilha));
    pilha_apagar(&pilha);
}
