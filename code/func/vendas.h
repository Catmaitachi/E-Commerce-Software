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

// Baixa no estoque.

void BaixaEstoque ( venda *resultado ) {

    FILE *arquivo = fopen( PRODUTOS , "r" );
    FILE *temp = fopen( "../data/baixa.txt" , "w" );

    system(" cls || clear ");

    if ( arquivo == NULL || temp == NULL ) {

        perror("Erro ao abrir arquivos para alterar.\n\n");

        if(arquivo) fclose(arquivo);
        if(temp) fclose(temp);

        MenuVendas();

    }

    venda v = *resultado , x;

    while ( fscanf( arquivo , "%d,%49[^,],%d,%f\n", &x.fProduto.codigo, x.fProduto.nome, &x.fProduto.estoque, &x.fProduto.preco ) == 4 ) {
        
        if (x.fProduto.codigo == v.fProduto.codigo) {

            fprintf(temp, "%d,%s,%d,%.2f\n", v.fProduto.codigo, v.fProduto.nome, v.fProduto.estoque, v.fProduto.preco);

        } else {

            fprintf(temp, "%d,%s,%d,%.2f\n", x.fProduto.codigo, x.fProduto.nome, x.fProduto.estoque, x.fProduto.preco);
        
        }

    }

    fclose(arquivo);
    fclose(temp);

    remove(PRODUTOS);

    rename("../data/baixa.txt", PRODUTOS);

}

// Atribuir comissão ao vendedor.

void AtribuirComissao ( venda *resultado ) {

    FILE *arquivo = fopen( VENDEDORES , "r" );
    FILE *temp = fopen( "../data/temp.txt" , "w" );

    system(" cls || clear ");

    if ( arquivo == NULL || temp == NULL ) {

        perror("Erro ao abrir arquivos para alterar.\n\n");

        if(arquivo) fclose(arquivo);
        if(temp) fclose(temp);

        MenuVendas();

    }

    venda v = *resultado , x;

    while ( fscanf( arquivo , "%d,%50[^,],%f,%f\n" , &x.fVendedor.numero , x.fVendedor.nome , &x.fVendedor.salario , &x.fVendedor.comissao ) == 4 ) {

        if ( x.fVendedor.numero == v.fVendedor.numero ) {

            fprintf( temp , "%d,%s,%f,%f\n" , v.fVendedor.numero , v.fVendedor.nome , v.fVendedor.salario , v.fVendedor.comissao );

        } else {

            fprintf( temp , "%d,%s,%f,%f\n" , x.fVendedor.numero , x.fVendedor.nome , x.fVendedor.salario , x.fVendedor.comissao );

        }

    }

    fclose(arquivo);
    fclose(temp);

    remove(VENDEDORES);

    rename("../data/temp.txt", VENDEDORES);

}

// Função que retorna o próximo ID disponível.

int ProximaVenda ( void ) {
    
    FILE *arquivo = fopen( VENDAS , "r" );

    if ( arquivo == NULL ) {

        return 1;

    }

    venda v;

    int id = 0;

    while ( fscanf( arquivo , "%d,%f,%d,%d,%11[^,],%d\n" , &v.codigo , &v.pTotal , &v.quantidade , &v.fProduto.codigo , v.fCliente.cpf , &v.fVendedor.numero ) == 6 ) {

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

    while ( fscanf( arquivo , "%11[^,],%50[^,],%50[^,],%d,%50[^,],%50[^,],%50[^,],%2[^,]\n" , x.fCliente.cpf , x.fCliente.nome , x.fCliente.email , &x.fCliente.endereco.cep , x.fCliente.endereco.rua , x.fCliente.endereco.bairro , x.fCliente.endereco.cidade , x.fCliente.endereco.estado ) == 8 ) {

        if ( strcmp( x.fCliente.cpf , v.fCliente.cpf ) == 0 ) {

            strcpy( v.fCliente.nome , x.fCliente.nome );
            strcpy( v.fCliente.email , x.fCliente.email );
            v.fCliente.endereco.cep = x.fCliente.endereco.cep;
            strcpy( v.fCliente.endereco.rua , x.fCliente.endereco.rua );
            strcpy( v.fCliente.endereco.bairro , x.fCliente.endereco.bairro );
            strcpy( v.fCliente.endereco.cidade , x.fCliente.endereco.cidade );
            strcpy( v.fCliente.endereco.estado , x.fCliente.endereco.estado );
            
            *resultado = v;

            fclose(arquivo);

            return 1;

        }

    }

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

    while ( fscanf( arquivo , "%d,%f,%d,%d,%11[^,],%d\n" , &v.codigo , &v.pTotal , &v.quantidade , &v.fProduto.codigo , v.fCliente.cpf , &v.fVendedor.numero ) == 6 ) {

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
void ConsultarVendas ( int redirect );
void AlterarVenda ( void );
void ExcluirVenda ( void );
void GerarNotaFiscal ( void );

// Menu de Vendedores.

void MenuVendas ( void ) {

    system(" cls || clear ");

    int input;

    printf("\nVendas\n\n");

    printf("[1] Cadastrar\n");
    printf("[2] Consultar\n");
    printf("[3] Alterar\n");
    printf("[4] Excluir\n\n");
    printf("[5] Emitir Nota Fiscal\n\n");
    printf("[0] Voltar\n\n: ");
    
    scanf("%d", &input);

    switch ( input ) {

        case 0: MenuPrincipal(); break;

        case 1: CadastrarVenda(); break;
        
        case 2: ConsultarVendas(1); break;

        case 3: AlterarVenda(); break;

        case 4: ExcluirVenda(); break;

        case 5: GerarNotaFiscal(); break;

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

    if ( v.quantidade > v.fProduto.estoque ) {

        system(" cls || clear ");

        printf("VENDA ABORTADA!\n\n");
        printf("%s\n\n" , v.fProduto.nome);
        printf("Quantidade Selecionada: %d\n" , v.quantidade);
        printf("Quantidade em Estoque: %d\n\n" , v.fProduto.estoque);
        
        system("pause");

        MenuVendas();

    }

    v.fProduto.estoque -= v.quantidade;

    v.pTotal = v.fProduto.preco * v.quantidade;

    BaixaEstoque( p );

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
                fgets( v.fCliente.cpf , 13 , stdin );
                strtok( v.fCliente.cpf , "\n" );

                BuscarCliente( p );

            } else { strcpy(v.fCliente.cpf, ""); CadastrarCliente( 0 ); }
            
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

    v.fVendedor.comissao += v.pTotal * 0.03;

    AtribuirComissao( p );

    // Inserindo no arquivo.

    fprintf( arquivo , "%d,%f,%d,%d,%s,%d\n" , ProximaVenda() , v.pTotal , v.quantidade , v.fProduto.codigo , v.fCliente.cpf , v.fVendedor.numero );

    fclose(arquivo);

    // Volta para o menu.

    MenuVendas();

}

// Função para consultar vendas cadastrados.

void ConsultarVendas ( int redirect ) {

    // Abrindo arquivo.

    FILE *arquivo = fopen( VENDAS , "r" );

    system(" cls || clear ");

    if ( arquivo == NULL ) {

        printf("Nenhum venda registrada.\n\n");

        system("pause");

        MenuVendas();

    }

    // Exibindo dados.

    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("CODIGO | PRODUTO              | QUANTIDADE | VALOR           | CLIENTE                   | VENDEDOR\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    venda v , *p = &v;

    while ( fscanf( arquivo , "%d,%f,%d,%d,%50[^,],%d\n" , &v.codigo , &v.pTotal , &v.quantidade , &v.fProduto.codigo , v.fCliente.cpf , &v.fVendedor.numero ) == 6 ) {

        BuscarProduto( p );
        BuscarCliente( p );
        BuscarVendedor( p );

        if ( strcmp( v.fCliente.cpf , "none" ) == 0 ) strcpy( v.fCliente.nome , "Indefinido" );

        printf("%-6d | %-20s | %-10d | R$ %-12.2f | %-25s | %s\n" , v.codigo , v.fProduto.nome , v.quantidade , v.pTotal , v.fCliente.nome , v.fVendedor.nome );

    }

    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    fclose(arquivo);

    // Volta para o menu.

    if ( redirect != 0 ) { system("pause"); MenuVendas(); }

}

// Função para alterar uma venda cadastrado.

void AlterarVenda ( void ) {

    // Abrindo arquivos.

    FILE *arquivo = fopen( VENDAS , "r" );

    FILE *temp = fopen( "../data/temp.txt" , "w" );

    system(" cls || clear ");

    if ( arquivo == NULL || temp == NULL ) {

        perror("Erro ao abrir arquivos para alterar.\n\n");

        if(arquivo) fclose(arquivo);
        if(temp) fclose(temp);

        MenuVendedores();

    }

    // Input do usuário.

    int codigo = 0;

    venda v , x , *p = &v;

    printf("Insira o Codigo da venda: ");
    scanf("%d" , &codigo);

    int pesquisar = PesquisarVenda( codigo , p );

    if ( !pesquisar ) {

        printf("\n\nNenhuma venda com codigo %d encontrado.\n\n" , codigo);

        system("pause");

        MenuVendas();

    }

    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("CODIGO | PRODUTO              | QUANTIDADE | VALOR           | CLIENTE                   | VENDEDOR\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-6d | %-20s | %-10d | R$ %-12.2f | %-25s | %s\n" , v.codigo , v.fProduto.nome , v.quantidade , v.pTotal , v.fCliente.nome , v.fVendedor.nome );
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    int confirmar = 0;

    printf("Deseja alterar essa venda?\n\n");
    printf("[0] Nao\n");
    printf("[1] Sim\n\n:");
    scanf("%d" , &confirmar);

    if ( confirmar != 1 ) {

        fclose(arquivo);
        fclose(temp);

        MenuVendas();

    }

    int pCodigo = 0;
    
    printf("\nCodigo do Produto: ");
    scanf("%d" , &pCodigo);
    
    int quantidade = 0;

    printf("\nQuantidade: ");
    scanf("%d" , &quantidade);
    
    getchar();
    
    printf("\nCPF do Cliente: ");
    fgets( v.fCliente.cpf , 13 , stdin );
    strtok( v.fCliente.cpf , "\n" );
    
    printf("\nNumero do Vendedor: ");
    scanf("%d" , &v.fVendedor.numero);

    // Alterando dados.

    while ( fscanf( arquivo , "%d,%f,%d,%d,%11[^,],%d\n" , &x.codigo , &x.pTotal , &x.quantidade , &x.fProduto.codigo , x.fCliente.cpf , &x.fVendedor.numero ) == 6 ) {

        if ( x.codigo == v.codigo ) {

            if ( quantidade - x.quantidade > v.fProduto.estoque && pCodigo == v.fProduto.codigo ) {

                system(" cls || clear ");

                printf("Quantidade do produto maior que o estoque!\n\n");

                system("pause");

                MenuVendas();

            } else if ( pCodigo == v.fProduto.codigo  ) {

                BuscarProduto( p );

                v.pTotal = quantidade * v.fProduto.preco;

                v.fProduto.estoque -= ( quantidade - x.quantidade );

                BaixaEstoque( p );

            } else {

                BuscarProduto( p );

                v.fProduto.estoque += v.quantidade;

                BaixaEstoque( p );

                v.fProduto.codigo = pCodigo;

                BuscarProduto( p );

                if ( quantidade - x.quantidade > v.fProduto.estoque ) {

                    system(" cls || clear ");

                    printf("Quantidade do produto maior que o estoque!\n\n");

                    system("pause");

                    MenuVendas();

                }

                v.pTotal = quantidade * v.fProduto.preco;

                v.fProduto.estoque -= quantidade;

                BaixaEstoque( p );

            }

            fprintf( temp , "%d,%f,%d,%d,%s,%d\n" , v.codigo , v.pTotal , quantidade , v.fProduto.codigo , v.fCliente.cpf , v.fVendedor.numero );

        } else {

            fprintf( temp , "%d,%f,%d,%d,%s,%d\n" , x.codigo , x.pTotal , x.quantidade , x.fProduto.codigo , x.fCliente.cpf , x.fVendedor.numero );

        }

    }

    fclose(arquivo);
    fclose(temp);

    remove(VENDAS);

    rename("../data/temp.txt" , VENDAS);

    // Volta para o menu.

    MenuVendas();

}

// Função para exluir uma venda cadastrado.

void ExcluirVenda ( void ) {

    // Abrindo arquivos.

    FILE *arquivo = fopen( VENDAS , "r" );

    FILE *temp = fopen( "../data/temp.txt" , "w" );

    system(" cls || clear ");

    if ( arquivo == NULL || temp == NULL ) {

        perror("Erro ao abrir arquivos para alterar.\n\n");

        if(arquivo) fclose(arquivo);
        if(temp) fclose(temp);

        MenuVendedores();

    }

    // Input do usuário.

    int codigo = 0;

    venda v , x , *p = &v;

    printf("Insira o Codigo da venda: ");
    scanf("%d" , &codigo);

    int pesquisar = PesquisarVenda( codigo , p );

    if ( !pesquisar ) {

        printf("\n\nNenhuma venda com codigo %d encontrado.\n\n" , codigo);

        system("pause");

        MenuVendas();

    }

    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("CODIGO | PRODUTO              | QUANTIDADE | VALOR           | CLIENTE                   | VENDEDOR\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-6d | %-20s | %-10d | R$ %-12.2f | %-25s | %s\n" , v.codigo , v.fProduto.nome , v.quantidade , v.pTotal , v.fCliente.nome , v.fVendedor.nome );
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    int confirmar = 0;

    printf("Deseja excluir essa venda?\n\n");
    printf("[0] Nao\n");
    printf("[1] Sim\n\n:");
    scanf("%d" , &confirmar);

    if ( confirmar != 1 ) {

        fclose(arquivo);
        fclose(temp);

        MenuVendas();

    }
    
    // Alterando dados.

    int novoID = 1;

    BuscarProduto( p );

    v.fProduto.estoque += v.quantidade;

    BaixaEstoque( p );

    while ( fscanf( arquivo , "%d,%f,%d,%d,%50[^,],%d\n" , &x.codigo , &x.pTotal , &x.quantidade , &x.fProduto.codigo , x.fCliente.cpf , &x.fVendedor.numero ) == 6 ) {

        if ( !( x.codigo == v.codigo ) ) {

            fprintf( temp , "%d,%f,%d,%d,%s,%d\n" , novoID , x.pTotal , x.quantidade , x.fProduto.codigo , x.fCliente.cpf , x.fVendedor.numero );

            novoID++;

        }

    }

    fclose(arquivo);
    fclose(temp);

    remove(VENDAS);

    rename("../data/temp.txt" , VENDAS);

    // Volta para o menu.

    MenuVendas();

}

// Gerar nota fiscal.

void GerarNotaFiscal ( void ) {

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

    printf("Insira o codigo da venda ou digite 0 para listar: ");
    scanf("%d" , &v.codigo);

    if ( v.codigo == 0 ) {

        ConsultarVendas( v.codigo );

        printf("Insira o codigo da venda: ");
        scanf("%d" , &v.codigo);

    }

    int pesquisar = PesquisarVenda( v.codigo , p );

    if ( !pesquisar ) {

        printf("\n\nNenhuma venda com codigo %d encontrado.\n\n" , v.codigo);

        system("pause");

        MenuVendas();

    }

    BuscarProduto( p );
    BuscarCliente( p );
    BuscarVendedor( p );

    char id[12];
    char file[100];

    snprintf( id , sizeof(id) , "%d" , v.codigo );
    
    snprintf( file , sizeof(file) , "../data/notas_fiscais/%s.txt" , id );
    
    FILE *nota = fopen( file , "w" );

    if ( nota == NULL ) {

        perror("Erro ao abrir arquivo para escrita.");

        system("pause");

        MenuVendas();

    }

    fprintf(nota, "\tNOTA FISCAL\n\n");

    fprintf(nota, "\tCÓDIGO DA VENDA: %d\n\n", v.codigo);
    fprintf(nota, "\tPRODUTO: [ Código: %d | Nome: %s | Preço: R$ %.2f ]\n\n", v.fProduto.codigo , v.fProduto.nome , v.fProduto.preco);
    fprintf(nota, "\tQuantidade vendida: %d\n", v.quantidade);
    fprintf(nota, "\tValor total da compra: R$ %.2f\n\n", v.pTotal);
    
    if ( strcmp( v.fCliente.cpf , "none" ) != 0  ) {
        
        fprintf(nota, "\tCLIENTE\n\n");
        fprintf(nota, "\tCPF: %s\n", v.fCliente.cpf);
        fprintf(nota, "\tNome: %s\n", v.fCliente.nome);
        fprintf(nota, "\tEmail: %s\n", v.fCliente.email);
        fprintf(nota, "\tEndereço: %s, %s - %s, %s [ CEP: %d ]\n\n",
            v.fCliente.endereco.rua,
            v.fCliente.endereco.bairro,
            v.fCliente.endereco.cidade,
            v.fCliente.endereco.estado,
            v.fCliente.endereco.cep);
    
    }

    fprintf(nota, "\tVENDEDOR\n\n");
    fprintf(nota, "\tNome: %s\n", v.fVendedor.nome);
    fprintf(nota, "\tNúmero: %d\n", v.fVendedor.numero);
    fprintf(nota, "\tComissão: R$ %.2f\n", v.pTotal * 0.03);

    fclose(nota);

    printf("\nNota Fiscal gerada com sucesso em '%s'\n\n" , file);

    system("pause");

    MenuVendas();

}

#endif 