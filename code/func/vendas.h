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

    while ( fscanf( arquivo , "%d,%f,%d,%d,%d,%d\n" , &v.codigo , v.pTotal , &v.quantidade , &v.fProduto.codigo , &v.fCliente.cpf , &v.fVendedor.numero ) == 4 ) {

        if ( v.codigo > id ) {

            id = v.codigo;

        }

    }

    fclose(arquivo);

    return id + 1;

}

#endif 