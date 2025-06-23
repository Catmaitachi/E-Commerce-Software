#ifndef VENDEDORES_H
#define VENDEDORES_H

typedef struct {

    int numero;
    char nome[50];
    float salario;
    int comissao;

} vendedor;

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

        case 1: break;

        case 2: break;

        case 3: break;

        case 4: break;

        default: MenuVendedores(); break;

    }
    
}

#endif 