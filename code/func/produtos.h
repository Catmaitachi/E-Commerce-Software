#ifndef PRODUTOS_H
#define PRODUTOS_H

#define PRODUTOS "../data/produtos.txt"

// Declarando estrutura de dados para vendedores.

typedef struct {

    int codigo;
    char nome[50];
    int estoque;
    float preco;

} produto;

// Funções do CRUD para manipulação dos produtos

void CadastrarProduto(void);
void ConsultarProdutos(void);
void AlterarProduto(void);
void ExcluirProduto(void);
int ProximoProduto(void);
int PesquisarProduto(int codigo, produto *res);

// Menu de produtos

void MenuProdutos(void) {
    system("cls || clear");

    int input;

    printf("\nProdutos\n\n");
    printf("[1] Cadastrar\n");
    printf("[2] Consultar\n");
    printf("[3] Alterar\n");
    printf("[4] Excluir\n\n");
    printf("[0] Voltar\n\n: ");

    scanf("%d", &input);

    switch (input) {
        case 0: MenuPrincipal(); break;
        case 1: CadastrarProduto(); break;
        case 2: ConsultarProdutos(); break;
        case 3: AlterarProduto(); break;
        case 4: ExcluirProduto(); break;
        default: MenuProdutos(); break;
    }
}
#endif
