#ifndef VENDEDORES_H
#define VENDEDORES_H

#define LINK "../data/vendedores.txt"

// Declarando estrutura de dados para vendedores.

typedef struct {

    int numero;
    char nome[50];
    float salario;
    int comissao;

} vendedor;

// Função que retorna o próximo ID disponível.

int ProximoID ( void ) {

    FILE *arquivo = fopen( LINK , "r" );

    if ( arquivo == NULL ) {

        return 1;

    }

    vendedor v;

    int id = 0;

    while ( fscanf( arquivo , "%d,%49[^,],%f,%d\n" , &v.numero , v.nome , &v.salario , &v.comissao ) == 4 ) {

        if ( v.numero > id ) {

            id = v.numero;

        }

    }

    fclose(arquivo);

    return id + 1;

}

// Função que retorna o número de itens cadastrados ( baseado na quantidade de linhas ).

int QuantasLinhas ( void ) {

    FILE *arquivo = fopen( LINK , "r" );

    if ( arquivo == NULL ) {

        return 0; 

    }

    char lerTexto;
    int linhas = 0;
    
    while ( ( lerTexto = fgetc(arquivo) ) != EOF ) {

        if ( lerTexto == '\n' ) {

            linhas++;

        }

    }

    return linhas;

}

// Declarando protótipos de funções.

void CadastrarVendedor ( void );
void ConsultarVendedores ( void );
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
        
        case 2: ConsultarVendedores(); break;

        case 3: AlterarVendedor(); break;

        case 4: ExcluirVendedor(); break;

        default: MenuVendedores(); break;

    }
    
}

// Função para cadastrar um vendedor.

void CadastrarVendedor ( void ) {

    // Abrindo arquivo

    FILE *arquivo = fopen( LINK , "a" );

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

    fprintf( arquivo , "%d,%s,%.2f,%d\n" , ProximoID() , v.nome , v.salario , 0 );

    fclose(arquivo);

    // Volta para o menu.

    MenuVendedores();

}

// Função para consultar vendedores cadastrados.

void ConsultarVendedores ( void ) {

    FILE *arquivo = fopen( LINK , "r" );

    system(" cls || clear ");

    if ( arquivo == NULL ) {

        printf("Nenhum vendedor cadastrado.\n\n");

        system("pause");

        MenuVendedores();

    }

    printf("-----------------------------------------------------------------------\n");
    printf("NUMERO  | NOME                           | SALARIO           | COMISSAO\n");
    printf("-----------------------------------------------------------------------\n");

    vendedor v;

    while ( fscanf( arquivo , "%d,%50[^,],%f,%d\n" , &v.numero , v.nome , &v.salario , &v.comissao ) == 4 ) {

        printf("%-7d | %-30s | R$ %-14.2f | %d\n" , v.numero , v.nome , v.salario , v.comissao );

    }

    printf("-----------------------------------------------------------------------\n\n");

    system("pause");

    fclose(arquivo);

    MenuVendedores();

}

// Função para alterar um vendedor cadastrado.

void AlterarVendedor ( void ) {

    FILE *arquivo = fopen( LINK , "r" );

    system(" cls || clear ");

    // a fazer ...

    fclose(arquivo);

}

// Função para excluir um vendedor cadastrado.

void ExcluirVendedor ( void ) {

    FILE *arquivo = fopen( LINK , "r" );

    system(" cls || clear ");

    // a fazer ...

    fclose(arquivo);

}

#endif 