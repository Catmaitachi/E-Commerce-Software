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

// Implementação das funções CRUD

// Cadastrar um novo produto

void CadastrarProduto(void) {
    FILE *arquivo = fopen(PRODUTOS, "a");
    system("cls || clear");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para escrita.");
        system("pause");
        MenuProdutos();
    }
    produto p;
    getchar(); // Limpa buffer
    printf("Nome: ");
    fgets(p.nome, 50, stdin);
    strtok(p.nome, "\n");

    printf("\nQuantidade em estoque: ");
    scanf("%d", &p.estoque);

    printf("\nPreço: ");
    scanf("%f", &p.preco);

    int codigo = ProximoProduto();
    fprintf(arquivo, "%d,%s,%d,%.2f\n", codigo, p.nome, p.estoque, p.preco);
    fclose(arquivo);

    printf("\nProduto cadastrado com sucesso!\n");
    system("pause");
    MenuProdutos();
}

#endif
