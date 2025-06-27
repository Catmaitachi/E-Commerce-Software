#ifndef PRODUTOS_H
#define PRODUTOS_H

#define PRODUTOS "../data/produtos.txt"

// Declarando estrutura de dados para vendedores.

typedef struct {

    int codigo;
    char nome[50];
    int estoque;
    float preco;

} produto;

#endif 