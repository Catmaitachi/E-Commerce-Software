#ifndef VENDAS_H
#define VENDAS_H

#define VENDAS "../data/vendas.txt"

// Declarando estrutura de dados para vendas.

typedef struct {

    int codigo;
    float pTotal;
    
    int quantidade;

    produto fProduto;
    cliente fCliente;
    vendedor fVendedor;

} venda;

// Função que retorna o próximo ID disponível.

int ProximaVenda ( void ) {
    
    FILE *arquivo = fopen( VENDAS , "r" );

    if ( arquivo == NULL ) {

        return 1;

    }

    venda v;

    int id = 0;

    while ( fscanf( arquivo , "%d,%f,%d,%d,%d,%d\n" , &v.codigo , &v.pTotal , &v.quantidade , &v.fProduto.codigo , &v.fCliente.cpf , &v.fVendedor.numero ) == 4 ) {

        if ( v.codigo > id ) {

            id = v.codigo;

        }

    }

    fclose(arquivo);

    return id + 1;

}

// Função para buscar Produto.

int BuscarProduto ( venda *resultado ) {

    FILE *arquivo = fopen ( PRODUTOS , "r" );

    if ( arquivo == NULL ) {

        return 0;

    }

    venda v = *resultado;
    venda x;

    while ( fscanf( arquivo , "%d,%50[^,],%d,%f\n" , &x.fProduto.codigo , x.fProduto.nome , &x.fProduto.estoque , &x.fProduto.preco ) == 4 ) {

        if ( x.fProduto.codigo == v.fProduto.codigo ) {

            fclose(arquivo);

            strcpy( v.fProduto.nome , x.fProduto.nome );
            v.fProduto.estoque = x.fProduto.estoque;
            v.fProduto.preco = x.fProduto.preco;

            *resultado = v;

            return 1;

        }

    }

    v.fProduto.codigo = 0;

    *resultado = v;

    fclose(arquivo);

    return 0;


}

// Função para buscar Cliente.

int BuscarCliente ( venda *resultado ) {

    FILE *arquivo = fopen ( CLIENTES , "r" );

    if ( arquivo == NULL ) {

        return 0;

    }

    venda v = *resultado;
    venda x;

    while ( fscanf( arquivo , "%50[^,],%50[^,],%50[^,],%d,%50[^,],%50[^,],%50[^,],%2[^,]\n" , x.fCliente.cpf , x.fCliente.nome , x.fCliente.email , &x.fCliente.endereco.cep , x.fCliente.endereco.rua , x.fCliente.endereco.bairro , x.fCliente.endereco.cidade , x.fCliente.endereco.estado ) == 8 && v.fCliente.cpf != 0 ) {

        if ( strcmp( x.fCliente.cpf , v.fCliente.cpf ) == 0 ) {

            fclose(arquivo);

            strcpy( v.fCliente.nome , x.fCliente.nome );
            strcpy( v.fCliente.email , x.fCliente.email );
            v.fCliente.endereco.cep = x.fCliente.endereco.cep;
            strcpy( v.fCliente.endereco.rua , x.fCliente.endereco.rua );
            strcpy( v.fCliente.endereco.bairro , x.fCliente.endereco.bairro );
            strcpy( v.fCliente.endereco.cidade , x.fCliente.endereco.cidade );
            strcpy( v.fCliente.endereco.estado , x.fCliente.endereco.estado );
            
            *resultado = v;

            return 1;

        }

    }

    strcpy(v.fCliente.cpf, "");

    *resultado = v;

    fclose(arquivo);

    return 0;


}

// Função para buscar Vendedor.

int BuscarVendedor ( venda *resultado ) {

    FILE *arquivo = fopen ( VENDEDORES , "r" );

    if ( arquivo == NULL ) {

        return 0;

    }

    venda v = *resultado;
    venda x;

    while ( fscanf( arquivo , "%d,%50[^,],%f,%f\n" , &x.fVendedor.numero , x.fVendedor.nome , &x.fVendedor.salario , &x.fVendedor.comissao ) == 4 ) {

        if ( x.fVendedor.numero == v.fVendedor.numero ) {

            fclose(arquivo);

            strcpy( v.fVendedor.nome , x.fVendedor.nome );
            v.fVendedor.salario = x.fVendedor.salario;
            v.fVendedor.comissao = x.fVendedor.comissao;

            *resultado = v;

            return 1;

        }

    }
    
    fclose(arquivo);

    return 0;


}

// Função para pesquisar venda por ID.

int PesquisarVenda ( int id , venda *resultado ) {

    FILE *arquivo = fopen ( VENDAS , "r" );

    if ( arquivo == NULL ) {

        return 0;

    }

    venda v;

    while ( fscanf( arquivo , "%d,%f,%d,%d,%d,%d\n" , &v.codigo , &v.pTotal , &v.quantidade , &v.fProduto.codigo , &v.fCliente.cpf , &v.fVendedor.numero ) == 6 ) {

        if ( v.codigo == id ) {

            fclose(arquivo);

            *resultado = v;

            int produtoOK = BuscarProduto( resultado );
            int clienteOK = BuscarCliente( resultado );
            int vendedorOK = BuscarVendedor( resultado );

            return 1;

        }

    }

    fclose(arquivo);

    return 0;

}

// Declarando protótipos de funções.

void CadastrarVenda ( void );
// void ConsultarVenda ( void );
// void AlterarVenda ( void );
// void ExcluirVenda( void );

// Menu de Vendedores.

void MenuVendas ( void ) {

    system(" cls || clear ");

    int input;

    printf("\nVendas\n\n");

    printf("[1] Cadastrar\n");
    printf("[2] Consultar\n");
    printf("[3] Alterar\n");
    printf("[4] Excluir\n\n");
    printf("[0] Voltar\n\n: ");
    
    scanf("%d", &input);

    switch ( input ) {

        case 0: MenuPrincipal(); break;

        case 1: CadastrarVenda(); break;
        
        //case 2: ConsultarVendas(); break;

        //case 3: AlterarVenda(); break;

        //case 4: ExcluirVenda(); break;

        default: MenuVendas(); break;

    }
    
}

// Função para cadastrar uma venda.

void CadastrarVenda ( void ) {

    // Abrindo arquivo.

    FILE *arquivo = fopen( VENDAS , "a" );

    system(" cls || clear ");

    if ( arquivo == NULL ) {

        perror("Erro ao abrir arquivo para escrita.");

        system("pause");

        MenuVendas();

    }

    // Input do usuário.

    venda v , *p = &v;

    // Recebendo Produto

    do {

        system(" cls || clear ");

        printf("Insira o codigo do produto ou digite 0 para listar: ");
        scanf("%d" , &v.fProduto.codigo);

        if ( v.fProduto.codigo == 0 ) {

            ConsultarProdutos( v.fProduto.codigo );

            printf("Insira o codigo do produto: ");
            scanf("%d" , &v.fProduto.codigo);
        
        }
    
        BuscarProduto( p );

    } while ( v.fProduto.codigo == 0 );

    printf("Insira a quantidade vendida: ");
    scanf("%d" , &v.quantidade);

    v.pTotal = v.fProduto.preco * v.quantidade;

    // Recebendo Cliente

    do { 

        system(" cls || clear ");

        int input;

        printf("Deseja inserir os dados de um comprador?\n\n");

        printf("[1] Sim\n");
        printf("[2] Nao\n\n: ");

        scanf("%d" , &input);

        if ( input == 1 ) {

            system(" cls || clear ");

            printf("O cliente ja possui cadastro?\n\n");
            
            printf("[1] Sim\n");
            printf("[2] Nao\n\n: ");

            scanf("%d" , &input);

            if ( input == 1 ) {

                system(" cls || clear ");

                getchar();

                printf("Insira o CPF do cliente: ");
                fgets( v.fCliente.cpf , 11 , stdin );
                strtok( v.fCliente.cpf , "\n" );

                BuscarCliente( p );

            } else CadastrarCliente( 0 ); strcpy(v.fCliente.cpf, "");
            
        } else strcpy(v.fCliente.cpf, "none");

    } while ( strcmp( v.fCliente.cpf , "" ) == 0 );

    // Recebendo Vendedor

    do {

        system(" cls || clear ");

        printf("Insira o numero do vendedor ou digite 0 para listar: ");
        scanf("%d" , &v.fVendedor.numero);

        if ( v.fVendedor.numero == 0 ) {

            ConsultarVendedores( v.fVendedor.numero );

            printf("Insira o numero do vendedor: ");
            scanf("%d" , &v.fVendedor.numero);
        
        }
    
        BuscarVendedor( p );

    } while ( v.fVendedor.numero == 0 );

    // Inserindo no arquivo.

    fprintf( arquivo , "%d,%f,%d,%d,%s,%d\n" , ProximaVenda() , v.pTotal , v.quantidade , v.fProduto.codigo , v.fCliente.cpf , v.fVendedor.numero );

    fclose(arquivo);

    // Volta para o menu.

    MenuVendas();

}

#endif 