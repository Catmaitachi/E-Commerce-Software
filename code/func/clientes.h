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

    char cpf[11];
    char nome[50];
    char email[50];

    endereco endereco;

} cliente;


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
