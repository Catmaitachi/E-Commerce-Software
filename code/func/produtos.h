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

// Funcoes do CRUD para manipulacao dos produtos

void CadastrarProduto(void);
void ConsultarProdutos( int redirect );
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
        case 2: ConsultarProdutos( 1 ); break;
        case 3: AlterarProduto(); break;
        case 4: ExcluirProduto(); break;
        default: MenuProdutos(); break;
    }
}

// Funcoes CRUD para obter o proximo codigo

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

// Funcao para pesquisar um produto pelo codigo

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

    printf("\nValor: ");
    scanf("%f", &p.preco);

    int codigo = ProximoProduto();
    fprintf(arquivo, "%d,%s,%d,%.2f\n", codigo, p.nome, p.estoque, p.preco);
    fclose(arquivo);

    printf("\nProduto cadastrado com sucesso!\n");
    system("pause");
    MenuProdutos();
}

// Consultar todos os produtos cadastrados

void ConsultarProdutos( int redirect ) {
    FILE *arquivo = fopen(PRODUTOS, "r");
    system("cls || clear");
    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado.\n\n");
        system("pause");
        MenuProdutos();
    }
    printf("------------------------------------------------------------\n");
    printf("CODIGO | NOME                     | ESTOQUE | PRECO\n");
    printf("------------------------------------------------------------\n");
    produto p;
    while (fscanf(arquivo, "%d,%49[^,],%d,%f\n", &p.codigo, p.nome, &p.estoque, &p.preco) == 4) {
        printf("%-6d | %-24s | %-7d | R$ %.2f\n", p.codigo, p.nome, p.estoque, p.preco);
    }
    printf("------------------------------------------------------------\n\n");

    fclose(arquivo);
    
    if ( redirect != 0 ) { system("pause"); MenuProdutos(); }

}

// Alterar um produto existente

void AlterarProduto(void) {
    FILE *arquivo = fopen(PRODUTOS, "r");
    FILE *temp = fopen("../data/temp.txt", "w");
    system("cls || clear");
    if (arquivo == NULL || temp == NULL) {
        perror("Erro ao abrir arquivos para alterar.");
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        MenuProdutos();
    }

    int codigo = 0;
    produto p, x, *pr = &p;
    printf("Insira o codigo do produto: ");
    scanf("%d", &codigo);

    int encontrado = PesquisarProduto(codigo, pr);
    if (!encontrado) {
        printf("\n\nNenhum produto com codigo %d encontrado.\n\n", codigo);
        system("pause");
        fclose(arquivo);
        fclose(temp);
        MenuProdutos();
    }

    printf("------------------------------------------------------------\n");
    printf("CODIGO | NOME                     | ESTOQUE | PRECO\n");
    printf("------------------------------------------------------------\n");
    printf("%-6d | %-24s | %-7d | R$ %.2f\n", p.codigo, p.nome, p.estoque, p.preco);
    printf("------------------------------------------------------------\n\n");

    int confirmar = 0;
    printf("Deseja alterar esse produto?\n\n");
    printf("[0] Nao\n");
    printf("[1] Sim\n\n:");
    scanf("%d", &confirmar);

    if (confirmar != 1) {
        fclose(arquivo);
        fclose(temp);
        MenuProdutos();
    }

    getchar();
    printf("\nNome: ");
    fgets(p.nome, 50, stdin);
    strtok(p.nome, "\n");
    printf("\nQuantidade em estoque: ");
    scanf("%d", &p.estoque);
    printf("\nPreco: ");
    scanf("%f", &p.preco);

    // Regrava arquivos
    while (fscanf(arquivo, "%d,%49[^,],%d,%f\n", &x.codigo, x.nome, &x.estoque, &x.preco) == 4) {
        if (x.codigo == p.codigo) {
            fprintf(temp, "%d,%s,%d,%.2f\n", p.codigo, p.nome, p.estoque, p.preco);
        } else {
            fprintf(temp, "%d,%s,%d,%.2f\n", x.codigo, x.nome, x.estoque, x.preco);
        }
    }
    fclose(arquivo);
    fclose(temp);
    remove(PRODUTOS);
    rename("../data/temp.txt", PRODUTOS);

    printf("\nProduto alterado com sucesso!\n");
    system("pause");
    MenuProdutos();
}

// Excluir um produto existente

void ExcluirProduto(void) {
    FILE *arquivo = fopen(PRODUTOS, "r");
    FILE *temp = fopen("../data/temp.txt", "w");
    system("cls || clear");
    if (arquivo == NULL || temp == NULL) {
        perror("Erro ao abrir arquivos para excluir.");
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        MenuProdutos();
    }
    int codigo = 0, confirmar = 0;
    produto p, x, *pr = &p;
    printf("Insira o codigo do produto: ");
    scanf("%d", &codigo);

    int encontrado = PesquisarProduto(codigo, pr);
    if (!encontrado) {
        printf("\n\nNenhum produto com codigo %d encontrado.\n\n", codigo);
        system("pause");
        fclose(arquivo);
        fclose(temp);
        MenuProdutos();
    }
    printf("------------------------------------------------------------\n");
    printf("CODIGO | NOME                     | ESTOQUE | PRECO\n");
    printf("------------------------------------------------------------\n");
    printf("%-6d | %-24s | %-7d | R$ %.2f\n", p.codigo, p.nome, p.estoque, p.preco);
    printf("------------------------------------------------------------\n\n");
    printf("Deseja excluir esse produto?\n\n");
    printf("[0] Nao\n");
    printf("[1] Sim\n\n:");
    scanf("%d", &confirmar);

    if (confirmar != 1) {
        fclose(arquivo);
        fclose(temp);
        MenuProdutos();
    }

    int novoID = 1;
    while (fscanf(arquivo, "%d,%49[^,],%d,%f\n", &x.codigo, x.nome, &x.estoque, &x.preco) == 4) {
        if (!(x.codigo == p.codigo)) {
            fprintf(temp, "%d,%s,%d,%.2f\n", novoID, x.nome, x.estoque, x.preco);
            novoID++;
        }
    }
    fclose(arquivo);
    fclose(temp);
    remove(PRODUTOS);
    rename("../data/temp.txt", PRODUTOS);

    printf("\nProduto excluido com sucesso!\n");
    system("pause");
    MenuProdutos();
}

#endif
