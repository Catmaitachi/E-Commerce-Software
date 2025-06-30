#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarando protótipos de funções.

void MenuProdutos ( void );
void MenuVendedores ( void );
void MenuClientes ( void );
void MenuVendas ( void );

// Menu Principal do Sistema.

void MenuPrincipal ( void ) {

    system(" cls || clear ");

    int input;

    printf("\nMenu Principal\n\n");

    printf("[1] Produtos\n");
    printf("[2] Vendedores\n");
    printf("[3] Clientes\n");
    printf("[4] Vendas\n\n");
    printf("[0] Sair\n\n: ");

    scanf("%d", &input);

    switch ( input ) {

        case 0: break;

        case 1: MenuProdutos(); break;

        case 2: MenuVendedores(); break;

        case 3: MenuClientes(); break;

        case 4: MenuVendas(); break;

        default: MenuPrincipal(); break;
        
    }
    
}

// Incluindo funções à partir de arquivos de cabeçalho.

#include "./func/produtos.h"
#include "./func/vendedores.h"
#include "./func/clientes.h"
#include "./func/vendas.h"

// Programa Principal.

int main ( void ) {

    MenuPrincipal();

    return 0;
}