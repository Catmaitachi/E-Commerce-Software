#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "munit/munit.h"

// Protótipos das funções principais para teste.
void MenuProdutos(void);
void MenuClientes(void);
void MenuVendas(void);

// Funções auxiliares para setup e teardown.
static void prepararAmbiente(void) {
    system("mkdir -p ../data");
    FILE *arquivo;

    arquivo = fopen("../data/produtos.txt", "w");
    fclose(arquivo);

    arquivo = fopen("../data/clientes.txt", "w");
    fclose(arquivo);

    arquivo = fopen("../data/vendas.txt", "w");
    fclose(arquivo);
}

static void limparAmbiente(void) {
    system("rm -rf ../data");
}

// Teste de cadastro de produto.
static MunitResult testarCadastroProduto(const MunitParameter params[], void* user_data) {
    prepararAmbiente();

    FILE *entrada = freopen("input.txt", "w", stdin);
    fprintf(entrada, "1\n1\nProduto Teste\n50\n10.00\n0\n");
    fclose(entrada);
    freopen("input.txt", "r", stdin);

    MenuProdutos();

    FILE *arquivo = fopen("../data/produtos.txt", "r");
    munit_assert_not_null(arquivo);

    char buffer[100];
    fgets(buffer, sizeof(buffer), arquivo);
    fclose(arquivo);

    munit_assert_not_null(strstr(buffer, "Produto Teste"));
    munit_assert_not_null(strstr(buffer, "50"));
    munit_assert_not_null(strstr(buffer, "10.00"));

    limparAmbiente();
    return MUNIT_OK;
}

// Teste de cadastro de cliente.
static MunitResult testarCadastroCliente(const MunitParameter params[], void* user_data) {
    prepararAmbiente();

    FILE *entrada = freopen("input.txt", "w", stdin);
    fprintf(entrada, "1\n1\n12345678900\nCliente Teste\ncliente@email.com\n12345\nRua Teste\nBairro Teste\nCidade Teste\nST\n0\n");
    fclose(entrada);
    freopen("input.txt", "r", stdin);

    MenuClientes();

    FILE *arquivo = fopen("../data/clientes.txt", "r");
    munit_assert_not_null(arquivo);

    char buffer[200];
    fgets(buffer, sizeof(buffer), arquivo);
    fclose(arquivo);

    munit_assert_not_null(strstr(buffer, "Cliente Teste"));
    munit_assert_not_null(strstr(buffer, "12345678900"));
    munit_assert_not_null(strstr(buffer, "Rua Teste"));

    limparAmbiente();
    return MUNIT_OK;
}

// Teste de cadastro de venda.
static MunitResult testarCadastroVenda(const MunitParameter params[], void* user_data) {
    prepararAmbiente();

    FILE *produtos = fopen("../data/produtos.txt", "w");
    fprintf(produtos, "1,Produto Teste,50,10.00\n");
    fclose(produtos);

    FILE *entrada = freopen("input.txt", "w", stdin);
    fprintf(entrada, "1\n1\n1\n10\n0\n0\n1\n1\n");
    fclose(entrada);
    freopen("input.txt", "r", stdin);

    MenuVendas();

    FILE *arquivo = fopen("../data/vendas.txt", "r");
    munit_assert_not_null(arquivo);

    char buffer[200];
    fgets(buffer, sizeof(buffer), arquivo);
    fclose(arquivo);

    munit_assert_not_null(strstr(buffer, "Produto Teste"));
    munit_assert_not_null(strstr(buffer, "10"));
    munit_assert_not_null(strstr(buffer, "100.00"));

    limparAmbiente();
    return MUNIT_OK;
}

// Configuração dos testes.
static MunitTest tests[] = {
    {
        "/cadastro-produto",
        testarCadastroProduto,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/cadastro-cliente",
        testarCadastroCliente,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/cadastro-venda",
        testarCadastroVenda,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

// Configuração da suíte.
static const MunitSuite suite = {
    "/sistema-tests",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

// Função principal.
int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
