#ifndef CLIENTES_H
#define CLIENTES_H

#define CLIENTES "../data/clientes.txt"

// Declarando estrutura de dados para vendedores.

typedef struct {

    int cep;
    char rua[50];
    char bairro[50];
    char cidade[50];
    char estado[3];

} endereco;

typedef struct {

    char cpf[12];
    char nome[50];
    char email[50];

    endereco endereco;

} cliente;

// Função para pesquisar vendedor por CPF.

int PesquisarCliente ( char cpf[12] , cliente *resultado ) {

    FILE *arquivo = fopen ( CLIENTES , "r" );

    if ( arquivo == NULL ) {

        return 0;

    }

    cliente c;

    while ( fscanf(arquivo, "%11[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,],%49[^,],%2[^,]\n", c.cpf, c.nome, c.email, &c.endereco.cep, c.endereco.rua, c.endereco.bairro, c.endereco.cidade, c.endereco.estado) == 8 ) {

        if ( strcmp( c.cpf , cpf ) == 0 ) {

            *resultado = c;

            fclose(arquivo);

            return 1;

        }

    }

    fclose(arquivo);

    return 0;

}

void CadastrarCliente ( int redirect );
void ConsultarClientes ( void );
void AlterarCliente ( void );
void ExcluirCliente ( void );

// Menu de Clientes.

void MenuClientes ( void ) {

    system(" cls || clear ");

    int input;

    printf("\nClientes\n\n");

    printf("[1] Cadastrar\n");
    printf("[2] Consultar\n");
    printf("[3] Alterar\n");
    printf("[4] Excluir\n\n");
    printf("[0] Voltar\n\n: ");
    
    scanf("%d", &input);

    switch ( input ) {

        case 0: MenuPrincipal(); break;

        case 1: CadastrarCliente(1); break;
        
        case 2: ConsultarClientes(); break;

        case 3: AlterarCliente(); break;

        case 4: ExcluirCliente(); break;

        default: MenuClientes(); break;

    }
    
}

// Função para cadastrar um cliente.

void CadastrarCliente ( int redirect ) {

    // Abrindo arquivo.

    FILE *arquivo = fopen( CLIENTES , "a" );

    system(" cls || clear ");

    if ( arquivo == NULL ) {

        perror("Erro ao abrir arquivo para escrita.");

        system("pause");

        MenuVendedores();

    }

    // Input do usuário.

    cliente c;

    getchar();

    printf("CPF: ");
    fgets( c.cpf , 13 , stdin );
    strtok( c.cpf , "\n" );

    printf("\nNome: ");
    fgets( c.nome , 50 , stdin );
    strtok( c.nome , "\n" );

    printf("\nEmail: ");
    fgets( c.email , 50 , stdin );
    strtok( c.email , "\n" );

    printf("\nCEP: ");
    scanf("%d" , &c.endereco.cep);

    getchar();

    printf("\nRua: ");
    fgets( c.endereco.rua , 50 , stdin );
    strtok( c.endereco.rua , "\n" );

    printf("\nBairro: ");
    fgets( c.endereco.bairro , 50 , stdin );
    strtok( c.endereco.bairro , "\n" );

    printf("\nCidade: ");
    fgets( c.endereco.cidade , 50 , stdin );
    strtok( c.endereco.cidade , "\n" );

    printf("\nEstado: ");
    fgets( c.endereco.estado , 4 , stdin );
    strtok( c.endereco.estado , "\n" );

    // Inserindo no arquivo.

    fprintf( arquivo , "%s,%s,%s,%d,%s,%s,%s,%s\n" , c.cpf , c.nome , c.email , c.endereco.cep , c.endereco.rua , c.endereco.bairro , c.endereco.cidade , c.endereco.estado );

    fclose(arquivo);

    // Volta para o menu.

    if ( redirect != 0 ) { MenuClientes(); }

}

// Função para consultar clientes cadastrados.

void ConsultarClientes ( void ) {

    // Abrindo arquivo.

    FILE *arquivo = fopen( CLIENTES , "r" );

    system(" cls || clear ");

    if ( arquivo == NULL ) {

        printf("Nenhum cliente cadastrado.\n\n");

        system("pause");

        MenuClientes();

    }

    // Exibindo dados.

    printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("CPF         | NOME                           | E-MAIL                         | CEP      | Endereco\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");

    cliente c;

    while ( fscanf( arquivo , "%11[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,],%49[^,],%2[^,]\n" , c.cpf , c.nome , c.email , &c.endereco.cep , c.endereco.rua , c.endereco.bairro , c.endereco.cidade , c.endereco.estado ) == 8 ) {

        printf("%-11s | %-30s | %-30s | %-8d | %s, %s - %s , %s\n" , c.cpf , c.nome , c.email , c.endereco.cep , c.endereco.rua , c.endereco.bairro , c.endereco.cidade , c.endereco.estado );

    }

    printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

    fclose(arquivo);

    // Volta para o menu.

    system("pause"); 
    
    MenuClientes();

}

// Função para alterar um vendedor cadastrado.

void AlterarCliente ( void ) {

    // Abrindo arquivos.

    FILE *arquivo = fopen( CLIENTES , "r" );

    FILE *temp = fopen( "../data/temp.txt" , "w" );

    system(" cls || clear ");

    if ( arquivo == NULL || temp == NULL ) {

        perror("Erro ao abrir arquivos para alterar.\n\n");

        if(arquivo) fclose(arquivo);
        if(temp) fclose(temp);

        MenuClientes();

    }

    // Input do usuário.

    char cpf[12];

    cliente c , x , *p = &c;

    getchar();

    printf("Insira o CPF do cliente: ");
    fgets( cpf , 13 , stdin );
    strtok( cpf , "\n" );

    int pesquisar = PesquisarCliente( cpf , p );

    if ( !pesquisar ) {

        printf("\n\nNenhum cliente com CPF %s encontrado.\n\n" , cpf);

        system("pause");

        MenuClientes();

    }

    printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("CPF         | NOME                           | E-MAIL                         | CEP      | Endereco\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-11s | %-30s | %-30s | %-8d | %s, %s - %s , %s\n" , c.cpf , c.nome , c.email , c.endereco.cep , c.endereco.rua , c.endereco.bairro , c.endereco.cidade , c.endereco.estado );
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

    int confirmar = 0;

    printf("Deseja alterar esse cliente?\n\n");
    printf("[0] Nao\n");
    printf("[1] Sim\n\n:");
    scanf("%d" , &confirmar);

    if ( confirmar != 1 ) {

        fclose(arquivo);
        fclose(temp);

        MenuClientes();

    }

    getchar();

    printf("\nNome: ");
    fgets( c.nome , 50 , stdin );
    strtok( c.nome , "\n" );

    printf("\nEmail: ");
    fgets( c.email , 50 , stdin );
    strtok( c.email , "\n" );

    printf("\nCEP: ");
    scanf("%d" , &c.endereco.cep);

    getchar();

    printf("\nRua: ");
    fgets( c.endereco.rua , 50 , stdin );
    strtok( c.endereco.rua , "\n" );

    printf("\nBairro: ");
    fgets( c.endereco.bairro , 50 , stdin );
    strtok( c.endereco.bairro , "\n" );

    printf("\nCidade: ");
    fgets( c.endereco.cidade , 50 , stdin );
    strtok( c.endereco.cidade , "\n" );

    printf("\nEstado: ");
    fgets( c.endereco.estado , 4 , stdin );
    strtok( c.endereco.estado , "\n" );

    // Alterando dados.

    while ( fscanf( arquivo , "%11[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,],%49[^,],%2[^,]\n" , x.cpf , x.nome , x.email , &x.endereco.cep , x.endereco.rua , x.endereco.bairro , x.endereco.cidade , x.endereco.estado ) == 8 ) {

        if ( strcmp( x.cpf , c.cpf ) == 0 ) {

            fprintf( temp , "%s,%s,%s,%d,%s,%s,%s,%s\n" , c.cpf , c.nome , c.email , c.endereco.cep , c.endereco.rua , c.endereco.bairro , c.endereco.cidade , c.endereco.estado );

        } else {

            fprintf( temp , "%s,%s,%s,%d,%s,%s,%s,%s\n" , x.cpf , x.nome , x.email , x.endereco.cep , x.endereco.rua , x.endereco.bairro , x.endereco.cidade , x.endereco.estado );

        }

    }

    fclose(arquivo);
    fclose(temp);

    remove(CLIENTES);

    rename("../data/temp.txt" , CLIENTES);

    // Volta para o menu.

    MenuClientes();

}

// Função para excluir um vendedor cadastrado.

void ExcluirCliente ( void ) {

    // Abrindo arquivos.

    FILE *arquivo = fopen( CLIENTES , "r" );

    FILE *temp = fopen( "../data/temp.txt" , "w" );

    system(" cls || clear ");

    if ( arquivo == NULL || temp == NULL ) {

        perror("Erro ao abrir arquivos para excluir.\n\n");

        if(arquivo) fclose(arquivo);
        if(temp) fclose(temp);

        MenuClientes();

    }

    // Input do usuário.

    char cpf[12];
    int confirmar = 0;

    cliente c , x , *p = &c;

    getchar();

    printf("Insira o CPF do cliente: ");
    fgets( cpf , 13 , stdin );
    strtok( cpf , "\n" );

    int pesquisar = PesquisarCliente( cpf , p );

    if ( !pesquisar ) {

        printf("\n\nNenhum cliente com CPF %s encontrado.\n\n" , cpf);

        system("pause");

        MenuClientes();

    }

    printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("CPF         | NOME                           | E-MAIL                         | CEP      | Endereco\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-11s | %-30s | %-30s | %-8d | %s, %s - %s , %s\n" , c.cpf , c.nome , c.email , c.endereco.cep , c.endereco.rua , c.endereco.bairro , c.endereco.cidade , c.endereco.estado );
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

    printf("Deseja excluir esse cliente?\n\n");
    printf("[0] Nao\n");
    printf("[1] Sim\n\n:");
    scanf("%d" , &confirmar);

    if ( confirmar != 1 ) {

        fclose(arquivo);
        fclose(temp);

        MenuClientes();

    }

    // Alterando dados.

    while ( fscanf( arquivo , "%11[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,],%49[^,],%2[^,]\n" , x.cpf , x.nome , x.email , &x.endereco.cep , x.endereco.rua , x.endereco.bairro , x.endereco.cidade , x.endereco.estado ) == 8 ) {

        if ( strcmp(x.cpf , c.cpf) != 0 ) {

            fprintf( temp , "%s,%s,%s,%d,%s,%s,%s,%s\n" , x.cpf , x.nome , x.email , x.endereco.cep , x.endereco.rua , x.endereco.bairro , x.endereco.cidade , x.endereco.estado );

        }

    }

    fclose(arquivo);
    fclose(temp);

    remove(CLIENTES);

    rename("../data/temp.txt" , CLIENTES);

    // Volta para o menu.

    MenuClientes();

}

#endif
