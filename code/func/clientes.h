#ifndef CLIENTES_H
#define CLIENTES_H

#define CLIENTES "../data/clientes.txt"

// Declarando estrutura de dados para vendedores.

typedef struct {

    int cep;
    char rua[50];
    char bairro[50];
    char cidade[50];
    char estado[2];

} endereco;

typedef struct {

    int cpf;
    char nome[50];
    char email[50];

    endereco endereco;

} cliente;

#endif 