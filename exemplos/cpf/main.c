#include <stdio.h>
#include <stdlib.h> // malloc

// Nossa estrutura básica para armazenar o CPF
typedef struct _CPF{
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int verificador;
} CPF;

unsigned int conta_get_cpf_a(CPF* cpf)
{
    if (cpf != NULL)
    {
       return cpf->a;
    }

    return 0;
}

unsigned int conta_get_cpf_b(CPF* cpf)
{
    if (cpf != NULL)
    {
       return cpf->b;
    }

    return 0;
}

unsigned int conta_get_cpf_c(CPF* cpf)
{
    if (cpf != NULL)
    {
       return cpf->c;
    }

    return 0;
}

unsigned int conta_get_cpf_verificador(CPF* cpf)
{
    if (cpf != NULL)
    {
       return cpf->verificador;
    }

    return 0;
}

void getCPFCompleto(char* buffer, CPF* cpf) {
        sprintf(buffer, "%03d.%03d.%03d-%02d", conta_get_cpf_a(cpf),conta_get_cpf_b(cpf),conta_get_cpf_c(cpf),conta_get_cpf_verificador(cpf));
}

void populateCPF(CPF* cpf, char* cpfString) {
        sscanf(cpfString, "%03u.%03u.%03u-%02u", &cpf->a, &cpf->b, &cpf->c, &cpf->verificador);
}

int main() {
    CPF *mCPF = (CPF*) malloc(sizeof(CPF));
    char* cpfCompleto;

    // Alocamos 15 caso o valor retornado possuir formatação
    cpfCompleto = (char*) malloc(15*sizeof(char));

    populateCPF(mCPF, "083.152.288-02");

    getCPFCompleto(cpfCompleto, mCPF);
    printf("O número do CPF completo é: %s \n", cpfCompleto);


    // Vamos liberar a memoria do buffer
    free(cpfCompleto);

    return 0;
};