#ifndef VENDEDORES_H
#define VENDEDORES_H

#define VENDEDORES "../data/vendedores.txt"

// Declarando estrutura de dados para vendedores.

typedef struct {

    int numero;
    char nome[50];
    float salario;
    float comissao;

} vendedor;

// Função que retorna o próximo ID disponível.

int ProximoVendedor ( void ) {

    FILE *arquivo = fopen( VENDEDORES , "r" );

    if ( arquivo == NULL ) {

        return 1;

    }

    vendedor v;

    int id = 0;

    while ( fscanf( arquivo , "%d,%49[^,],%f,%f\n" , &v.numero , v.nome , &v.salario , &v.comissao ) == 4 ) {

        if ( v.numero > id ) {

            id = v.numero;

        }

    }

    fclose(arquivo);

    return id + 1;

}

// Função para pesquisar vendedor por ID.

int PesquisarVendedor ( int id , vendedor *resultado ) {

    FILE *arquivo = fopen ( VENDEDORES , "r" );

    if ( arquivo == NULL ) {

        return 0;

    }

    vendedor v;

    while ( fscanf( arquivo , "%d,%50[^,],%f,%f\n" , &v.numero , v.nome , &v.salario , &v.comissao ) == 4 ) {

        if ( v.numero == id ) {

            *resultado = v;

            fclose(arquivo);

            return 1;

        }

    }

    fclose(arquivo);

    return 0;

}

// Declarando protótipos de funções.

void CadastrarVendedor ( void );
void ConsultarVendedores ( int redirect );
void AlterarVendedor ( void );
void ExcluirVendedor ( void );

// Menu de Vendedores.

void MenuVendedores ( void ) {

    system(" cls || clear ");

    int input;

    printf("\nVendedores\n\n");

    printf("[1] Cadastrar\n");
    printf("[2] Consultar\n");
    printf("[3] Alterar\n");
    printf("[4] Excluir\n\n");
    printf("[0] Voltar\n\n: ");
    
    scanf("%d", &input);

    switch ( input ) {

        case 0: MenuPrincipal(); break;

        case 1: CadastrarVendedor(); break;
        
        case 2: ConsultarVendedores(1); break;

        case 3: AlterarVendedor(); break;

        case 4: ExcluirVendedor(); break;

        default: MenuVendedores(); break;

    }
    
}

// Função para cadastrar um vendedor.

void CadastrarVendedor ( void ) {

    // Abrindo arquivo.

    FILE *arquivo = fopen( VENDEDORES , "a" );

    system(" cls || clear ");

    if ( arquivo == NULL ) {

        perror("Erro ao abrir arquivo para escrita.");

        system("pause");

        MenuVendedores();

    }

    // Input do usuário.

    vendedor v;

    getchar();

    printf("Nome: ");
    fgets( v.nome , 50 , stdin );
    strtok( v.nome , "\n" );

    printf("\nSalario: ");
    scanf("%f" , &v.salario);

    // Inserindo no arquivo.

    fprintf( arquivo , "%d,%s,%.2f,%f\n" , ProximoVendedor() , v.nome , v.salario , 0 );

    fclose(arquivo);

    // Volta para o menu.

    MenuVendedores();

}

// Função para consultar vendedores cadastrados.

void ConsultarVendedores ( int redirect ) {

    // Abrindo arquivo.

    FILE *arquivo = fopen( VENDEDORES , "r" );

    system(" cls || clear ");

    if ( arquivo == NULL ) {

        printf("Nenhum vendedor cadastrado.\n\n");

        system("pause");

        MenuVendedores();

    }

    // Exibindo dados.

    printf("---------------------------------------------------------------------------------\n");
    printf("NUMERO  | NOME                           | SALARIO           | COMISSAO          \n");
    printf("---------------------------------------------------------------------------------\n");

    vendedor v;

    while ( fscanf( arquivo , "%d,%50[^,],%f,%f\n" , &v.numero , v.nome , &v.salario , &v.comissao ) == 4 ) {

        printf("%-7d | %-30s | R$ %-14.2f | R$ %.2f\n" , v.numero , v.nome , v.salario , v.comissao );

    }

    printf("---------------------------------------------------------------------------------\n\n");

    fclose(arquivo);

    // Volta para o menu.

    if ( redirect != 0 ) { system("pause"); MenuVendedores(); }

}

// Função para alterar um vendedor cadastrado.

void AlterarVendedor ( void ) {

    // Abrindo arquivos.

    FILE *arquivo = fopen( VENDEDORES , "r" );

    FILE *temp = fopen( "../data/temp.txt" , "w" );

    system(" cls || clear ");

    if ( arquivo == NULL || temp == NULL ) {

        perror("Erro ao abrir arquivos para alterar.\n\n");

        if(arquivo) fclose(arquivo);
        if(temp) fclose(temp);

        MenuVendedores();

    }

    // Input do usuário.

    int numero = 0;

    vendedor v , x , *p = &v;

    printf("Insira o Numero do vendedor: ");
    scanf("%d" , &numero);

    int pesquisar = PesquisarVendedor( numero , p );

    if ( !pesquisar ) {

        printf("\n\nNenhum vendedor com Numero %d encontrado.\n\n" , numero);

        system("pause");

        MenuVendedores();

    }

    printf("-----------------------------------------------------------------------\n");
    printf("NUMERO  | NOME                           | SALARIO           | COMISSAO\n");
    printf("-----------------------------------------------------------------------\n");
    printf("%-7d | %-30s | R$ %-14.2f | R$ %.2f\n" , v.numero , v.nome , v.salario , v.comissao);
    printf("-----------------------------------------------------------------------\n\n");

    int confirmar = 0;

    printf("Deseja alterar esse vendedor?\n\n");
    printf("[0] Nao\n");
    printf("[1] Sim\n\n:");
    scanf("%d" , &confirmar);

    if ( confirmar != 1 ) {

        fclose(arquivo);
        fclose(temp);

        MenuVendedores();

    }

    getchar();

    printf("\nNome: ");
    fgets( v.nome , 50 , stdin );
    strtok( v.nome , "\n" );

    printf("\nSalario: ");
    scanf("%f" , &v.salario);

    printf("\nComissao: ");
    scanf("%f" , &v.comissao);

    // Alterando dados.

    while ( fscanf( arquivo , "%d,%50[^,],%f,%f\n" , &x.numero , x.nome , &x.salario , &x.comissao ) == 4 ) {

        if ( x.numero == v.numero ) {

            fprintf( temp , "%d,%s,%f,%f\n" , v.numero , v.nome , v.salario , v.comissao );

        } else {

            fprintf( temp , "%d,%s,%f,%f\n" , x.numero , x.nome , x.salario , x.comissao );

        }

    }

    fclose(arquivo);
    fclose(temp);

    remove(VENDEDORES);

    rename("../data/temp.txt" , VENDEDORES);

    // Volta para o menu.

    MenuVendedores();

}

// Função para excluir um vendedor cadastrado.

void ExcluirVendedor ( void ) {

    // Abrindo arquivos.

    FILE *arquivo = fopen( VENDEDORES , "r" );

    FILE *temp = fopen( "../data/temp.txt" , "w" );

    system(" cls || clear ");

    if ( arquivo == NULL || temp == NULL ) {

        perror("Erro ao abrir arquivos para excluir.\n\n");

        if(arquivo) fclose(arquivo);
        if(temp) fclose(temp);

        MenuVendedores();

    }

    // Input do usuário.

    int numero = 0 , confirmar = 0;

    vendedor v , x , *p = &v;

    printf("Insira o Numero do vendedor: ");
    scanf("%d" , &numero);

    int pesquisar = PesquisarVendedor( numero , p );

    if ( !pesquisar ) {

        printf("\n\nNenhum vendedor com Numero %d encontrado.\n\n" , numero);

        system("pause");

        MenuVendedores();

    }

    printf("---------------------------------------------------------------------------------\n");
    printf("NUMERO  | NOME                           | SALARIO           | COMISSAO          \n");
    printf("---------------------------------------------------------------------------------\n");
    printf("%-7d | %-30s | R$ %-14.2f | R$ %.2f\n" , v.numero , v.nome , v.salario , v.comissao);
    printf("---------------------------------------------------------------------------------\n\n");

    printf("Deseja excluir esse vendedor?\n\n");
    printf("[0] Nao\n");
    printf("[1] Sim\n\n:");
    scanf("%d" , &confirmar);

    if ( confirmar != 1 ) {

        fclose(arquivo);
        fclose(temp);

        MenuVendedores();

    }

    // Alterando dados.

    int novoID = 1;

    while ( fscanf( arquivo , "%d,%50[^,],%f,%f\n" , &x.numero , x.nome , &x.salario , &x.comissao ) == 4 ) {

        if ( !(x.numero == v.numero) ) {

            fprintf( temp , "%d,%s,%f,%f\n" , novoID , x.nome , x.salario , x.comissao );

            novoID++;

        }

    }

    fclose(arquivo);
    fclose(temp);

    remove(VENDEDORES);

    rename("../data/temp.txt" , VENDEDORES);

    // Volta para o menu.

    MenuVendedores();

}

#endif 