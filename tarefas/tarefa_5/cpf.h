#ifndef CPF_H
#define CPF_H

#define ERRO (-32000)
#define TRUE 1
#define FALSE 0
typedef int boolean;

typedef struct cpf_st CPF;

CPF *cpf_criar(const char *cpfString);
boolean cpf_apagar(CPF **cpf);
void cpf_imprimir(const CPF *cpf);
boolean cpf_maior(CPF *cpf1, CPF *cpf2);
boolean cpf_igual(CPF *cpf1, CPF *cpf2);
void cpf_imprimir_semformat(const CPF *cpf);
#endif //CPF_H
