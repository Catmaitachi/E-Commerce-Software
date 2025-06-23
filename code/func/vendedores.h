#ifndef VENDEDORES_H
#define VENDEDORES_H

// Declarando protótipos de funções.

void ConsultarVendedores ( void );
void CadastrarVendedor ( void );
void AlterarVendedor ( void );
void ExcluirVendedor ( void );

// Declarando estrutura de dados para vendedores.

typedef struct {

    int numero;
    char nome[50];
    float salario;
    int comissao;

} vendedor;

// Menu de Vendedores.

void MenuVendedores ( void ) {

    system(" cls || clear ");

    int input;

    printf("\nVendedores\n\n");

    printf("[1] Consultar\n");
    printf("[2] Cadastrar\n");
    printf("[3] Alterar\n");
    printf("[4] Excluir\n\n");
    printf("[0] Voltar\n\n: ");
    
    scanf("%d", &input);

    switch ( input ) {

        case 0: MenuPrincipal(); break;

        case 1: ConsultarVendedores(); break;

        case 2: CadastrarVendedor(); break;

        case 3: break;

        case 4: break;

        default: MenuVendedores(); break;

    }
    
}

// Consultar Vendedores.

void ConsultarVendedores ( void ) {

    system(" cls || clear ");



}

// Cadastrar Vendedores.

void CadastrarVendedor ( void ) {

    system(" cls || clear ");

    vendedor novo;

    printf("\nCadastrar Vendedor\n\n");

    novo.numero = 0;
    novo.comissao = 0;

    getchar();

    printf("\nNome: ");
    fgets( novo.nome , 50 , stdin );
    strtok( novo.nome , "\n" );

    printf("\nSalario: ");
    scanf("%f", &novo.salario);

    getchar();

    FILE *arquivo = fopen("../data/vendedores.txt", "a");

    if (arquivo != NULL) {

        fprintf(arquivo, "%d , ", novo.numero);
        fprintf(arquivo, "%s , ", novo.nome);
        fprintf(arquivo, "%.2f , ", novo.salario);
        fprintf(arquivo, "%d\n", novo.comissao);
        fclose(arquivo);

        printf("\nVendedor cadastrado com sucesso!\n\n");

        system("pause");

    } else {

        printf("\nErro ao abrir o arquivo.\n\n");

        system("pause");

    }

    MenuVendedores();

}

#endif 