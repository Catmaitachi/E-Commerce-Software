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

// Função para pesquisar vendedor por CPF.

int PesquisarCliente ( char cpf[11] , cliente *resultado ) {

    FILE *arquivo = fopen ( CLIENTES , "r" );

    if ( arquivo == NULL ) {

        return 0;

    }

    cliente c;

    while ( fscanf(arquivo, "%11[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,],%49[^,],%2s\n", c.cpf, c.nome, c.email, &c.endereco.cep, c.endereco.rua, c.endereco.bairro, c.endereco.cidade, c.endereco.estado) == 8 ) {

        if ( strcmp( c.cpf , cpf ) == 0 ) {

            *resultado = c;

            fclose(arquivo);

            return 1;

        }

    }

    fclose(arquivo);

    return 0;

}


void CadastrarCliente( int redirect );
void ListarClientes();
void AlterarCliente();
void ExcluirCliente();

void MenuClientes(void) {
    system("cls || clear");
    int input;

    printf("\nClientes\n\n");
    printf("[1] Cadastrar\n");
    printf("[2] Consultar\n");
    printf("[3] Alterar\n");
    printf("[4] Excluir\n\n");
    printf("[0] Voltar\n\n: ");
    scanf("%d", &input);

    switch (input) {
        case 0: MenuPrincipal(); break;
        case 1: CadastrarCliente( 1); break;
        case 2: ListarClientes(); break;
        case 3: AlterarCliente(); break;
        case 4: ExcluirCliente(); break;
        default: MenuClientes(); break;
    }
}

void CadastrarCliente( int redirect ) {
    FILE *arquivo = fopen(CLIENTES, "a");
    if (!arquivo) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    cliente c;
    getchar();
    printf("CPF: ");
    fgets(c.cpf, 12, stdin); strtok(c.cpf, "\n");

    getchar();
    printf("Nome: ");
    fgets(c.nome, 50, stdin); strtok(c.nome, "\n");

    getchar();
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

    if ( redirect != 0 ) system("pause"); MenuClientes();
    
}

void ListarClientes() {
    FILE *arquivo = fopen(CLIENTES, "r");
    if (!arquivo) {
        printf("Nenhum cliente cadastrado.\n");
        system("pause");
        MenuClientes();
    }

    cliente c;
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("CPF         | Nome                 | Email                | Rua, Bairro, Cidade - UF [CEP]\n");
    printf("-----------------------------------------------------------------------------------------------------\n");
    while (fscanf(arquivo, "%11[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,],%49[^,],%2s\n", c.cpf, c.nome, c.email,
                  &c.endereco.cep, c.endereco.rua, c.endereco.bairro, c.endereco.cidade, c.endereco.estado) == 8) {
        printf("%-11s | %-20s | %-20s | %s, %s, %s - %s [%d]\n",
               c.cpf, c.nome, c.email,
               c.endereco.rua, c.endereco.bairro, c.endereco.cidade,
               c.endereco.estado, c.endereco.cep);
    }

    printf("-----------------------------------------------------------------------------------------------------\n\n");
    fclose(arquivo);
    system("pause");
    MenuClientes();
}

void AlterarCliente() {
    FILE *arquivo = fopen(CLIENTES, "r");
    FILE *temp = fopen("../data/temp.txt", "w");
    if (!arquivo || !temp) {
        perror("Erro ao abrir arquivos para alterar");
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        MenuClientes();
    }

    cliente p, x;
    char cpf[12];
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    if (!PesquisarCliente(cpf, &p)) {
        printf("Cliente não encontrado.\n");
        system("pause");
        fclose(arquivo);
        fclose(temp);
        MenuClientes();
    }

    printf("Nome atual: %s\n", p.nome);
    getchar();
    printf("Novo nome: ");
    fgets(p.nome, 50, stdin); strtok(p.nome, "\n");

    printf("Novo email: ");
    fgets(p.email, 50, stdin); strtok(p.email, "\n");

    printf("Novo CEP: "); scanf("%d", &p.endereco.cep); getchar();
    printf("Nova rua: "); fgets(p.endereco.rua, 50, stdin); strtok(p.endereco.rua, "\n");
    printf("Novo bairro: "); fgets(p.endereco.bairro, 50, stdin); strtok(p.endereco.bairro, "\n");
    printf("Nova cidade: "); fgets(p.endereco.cidade, 50, stdin); strtok(p.endereco.cidade, "\n");
    printf("Novo estado: "); fgets(p.endereco.estado, 3, stdin); strtok(p.endereco.estado, "\n");

    while (fscanf(arquivo, "%11[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,],%49[^,],%2s\n", x.cpf, x.nome, x.email,
                  &x.endereco.cep, x.endereco.rua, x.endereco.bairro, x.endereco.cidade, x.endereco.estado) == 8) {
        if (strcmp(x.cpf, p.cpf) == 0) {
            fprintf(temp, "%s,%s,%s,%d,%s,%s,%s,%s\n", p.cpf, p.nome, p.email,
                    p.endereco.cep, p.endereco.rua, p.endereco.bairro,
                    p.endereco.cidade, p.endereco.estado);
        } else {
            fprintf(temp, "%s,%s,%s,%d,%s,%s,%s,%s\n", x.cpf, x.nome, x.email,
                    x.endereco.cep, x.endereco.rua, x.endereco.bairro,
                    x.endereco.cidade, x.endereco.estado);
        }
    }

    fclose(arquivo);
    fclose(temp);
    remove(CLIENTES);
    rename("../data/temp.txt", CLIENTES);

    printf("Cliente alterado com sucesso!\n");
    system("pause");
    MenuClientes();
}

void ExcluirCliente() {
    FILE *arquivo = fopen(CLIENTES, "r");
    FILE *temp = fopen("../data/temp.txt", "w");
    if (!arquivo || !temp) {
        perror("Erro ao abrir arquivos para excluir");
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        MenuClientes();
    }

    cliente p, x;
    char cpf[12];
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    if (!PesquisarCliente(cpf, &p)) {
        printf("Cliente não encontrado.\n");
        system("pause");
        fclose(arquivo);
        fclose(temp);
        MenuClientes();
    }

    while (fscanf(arquivo, "%11[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,],%49[^,],%2s\n", x.cpf, x.nome, x.email,
                  &x.endereco.cep, x.endereco.rua, x.endereco.bairro, x.endereco.cidade, x.endereco.estado) == 8) {
        if (strcmp(x.cpf, cpf) != 0) {
            fprintf(temp, "%s,%s,%s,%d,%s,%s,%s,%s\n", x.cpf, x.nome, x.email,
                    x.endereco.cep, x.endereco.rua, x.endereco.bairro,
                    x.endereco.cidade, x.endereco.estado);
        }
    }

    fclose(arquivo);
    fclose(temp);
    remove(CLIENTES);
    rename("../data/temp.txt", CLIENTES);

    printf("Cliente excluído com sucesso!\n");
    system("pause");
    MenuClientes();
}

#endif
