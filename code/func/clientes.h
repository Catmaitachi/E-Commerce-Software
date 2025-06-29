#ifndef CLIENTES_IMPL_H
#define CLIENTES_IMPL_H

#define CLIENTES "../data/clientes.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"

// Função que retorna o próximo ID disponível baseado no maior CPF numericamente (ou pode usar contagem de registros)
int ProximoClienteID() {
    FILE *arquivo = fopen(CLIENTES, "r");
    if (arquivo == NULL) return 1;

    cliente c;
    int id = 0;

    while (fscanf(arquivo, "%11[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,],%49[^,],%2s\n", c.cpf, c.nome, c.email,
                  &c.endereco.cep, c.endereco.rua, c.endereco.bairro, c.endereco.cidade, c.endereco.estado) == 8) {
        id++;
    }

    fclose(arquivo);
    return id + 1;
}

// Função para cadastrar cliente
void CadastrarCliente() {
    FILE *arquivo = fopen(CLIENTES, "a");
    if (!arquivo) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    cliente c;
    getchar();
    printf("CPF: ");
    fgets(c.cpf, 12, stdin); strtok(c.cpf, "\n");

    printf("Nome: ");
    fgets(c.nome, 50, stdin); strtok(c.nome, "\n");

    printf("Email: ");
    fgets(c.email, 50, stdin); strtok(c.email, "\n");

    printf("CEP: "); scanf("%d", &c.endereco.cep); getchar();
    printf("Rua: "); fgets(c.endereco.rua, 50, stdin); strtok(c.endereco.rua, "\n");
    printf("Bairro: "); fgets(c.endereco.bairro, 50, stdin); strtok(c.endereco.bairro, "\n");
    printf("Cidade: "); fgets(c.endereco.cidade, 50, stdin); strtok(c.endereco.cidade, "\n");
    printf("Estado: "); fgets(c.endereco.estado, 3, stdin); strtok(c.endereco.estado, "\n");

    fprintf(arquivo, "%s,%s,%s,%d,%s,%s,%s,%s\n", c.cpf, c.nome, c.email,
            c.endereco.cep, c.endereco.rua, c.endereco.bairro,
            c.endereco.cidade, c.endereco.estado);

    fclose(arquivo);
    printf("\nCliente cadastrado com sucesso!\n");
}

// Função para listar clientes
void ListarClientes() {
    FILE *arquivo = fopen(CLIENTES, "r");
    if (!arquivo) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    cliente c;
    printf("---------------------------------------------------------------------------------------------\n");
    printf("CPF         | Nome                 | Email                | Endereço                     \n");
    printf("---------------------------------------------------------------------------------------------\n");
    while (fscanf(arquivo, "%11[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,],%49[^,],%2s\n", c.cpf, c.nome, c.email,
                  &c.endereco.cep, c.endereco.rua, c.endereco.bairro, c.endereco.cidade, c.endereco.estado) == 8) {
        printf("%-11s | %-20s | %-20s | %s, %s, %s - %s [%d]\n",
               c.cpf, c.nome, c.email,
               c.endereco.rua, c.endereco.bairro, c.endereco.cidade,
               c.endereco.estado, c.endereco.cep);
    }

    printf("---------------------------------------------------------------------------------------------\n\n");
    fclose(arquivo);
}

#endif
