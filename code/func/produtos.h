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

// Funções CRUD para obter o próximo código

int ProximoProduto(void) {
    FILE *arquivo = fopen(PRODUTOS, "r");
    if (arquivo == NULL) {
        return 1;
    }
    produto p;
    int id = 0;
    while (fscanf(arquivo, "%d,%49[^,],%d,%f\n", &p.codigo, p.nome, &p.estoque, &p.preco) == 4) {
        if (p.codigo > id) {
            id = p.codigo;
        }
    }
    fclose(arquivo);
    return id + 1;
}

// Função para pesquisar um produto pelo código

int PesquisarProduto(int codigo, produto *res) {
    FILE *arquivo = fopen(PRODUTOS, "r");
    if (arquivo == NULL) {
        return 0;
    }
    produto p;
    while (fscanf(arquivo, "%d,%49[^,],%d,%f\n", &p.codigo, p.nome, &p.estoque, &p.preco) == 4) {
        if (p.codigo == codigo) {
            *res = p;
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

#endif
