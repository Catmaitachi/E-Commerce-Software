# Documentação do Projeto

Este arquivo registra detalhes das sprints realizadas durante o desenvolvimento, além de documentar as funções utilizadas no programa.

## Registro de Desenvolvimento

### Divisão inicial do software ( Backlog ):

Eis a sequencia na qual foi planejado a implementação das funcionalidades.

| Funcionalidade            | Sequência de Desenvolvimento   |
|-------------------------- |-------------------------------|
| Menu Principal            | Artefato Inicial              |
| CRUD de Produtos          | Artefato Primário             |
| CRUD de Vendedores        | Artefato Primário             |
| CRUD de Clientes          | Artefato Primário             |
| CRUD de Vendas            | Artefato Secundário           |
| Gerador de Nota Fiscal    | Artefato Terciário            |

### Registro da Sprint 1

#### Kanban ao final da Sprint 1 

![Kanban - Sprint 1](<imgs/kanban 1.png>)

[Vídeo da Sprint Review 1](https://drive.google.com/file/d/1pBFGt84QIfaL8YDWjHtNCMNnhU8DvCaJ/view?usp=drive_link)

### Registro da Sprint 2

#### Kanban ao final da Sprint 2

![Kanban - Sprint 2](<imgs/kanban 2.png>)

### Apresentação do Sistema

[Vídeo de Apresentação](https://drive.google.com/file/d/1hissIKjDEEL72symZdrjl6PCwni1idTl/view?usp=drive_link)


## Documentação das Funcionalidades

### Menu Principal

```c
void MenuPrincipal( void) {

    /*

    A função exibe o menu principal do programa e direciona o usuário para o submenu correspondente
    com base na entrada fornecida. Opções disponíveis:

    Entrada 0 - Encerra o programa.
    Entrada 1 - Direciona para o Menu de Produtos.
    Entrada 2 - Direciona para o Menu de Vendedores.
    Entrada 3 - Direciona para o Menu de Clientes.
    Entrada 4 - Direciona para o Menu de Vendas.
    Outra Entrada - Repete o menu principal.
    
    */

}
```

### Funções de CRUD ( Produtos, Vendedores e Clientes )

```c
void Menu ( void ) {

    /*

    A função apresenta um menu padrão para Produtos, Vendedores e Clientes. Com base na entrada do usuário,
    direciona para as funções correspondentes:

    Entrada 0 - Retorna ao Menu Principal.
    Entrada 1 - Direciona para a função de Cadastro.
    Entrada 2 - Direciona para a função de Consulta.
    Entrada 3 - Direciona para a função de Edição.
    Entrada 4 - Direciona para a função de Exclusão.
    Outra Entrada - Repete o menu atual.
    
    */

}

int ProximoID ( void ) {

    /*

    A função identifica o próximo ID disponível para uso em Produtos, Vendedores e Vendas. Abre o arquivo correspondente,
    localiza o maior ID registrado e retorna esse valor incrementado em 1.
    
    */

}

int Pesquisar ( int id, struct *resultado ) {

    /*

    A função pesquisa um registro pelo ID fornecido. Abre o arquivo correspondente, busca o ID desejado e, se encontrado,
    carrega os dados na estrutura apontada por resultado. Retorna 1 se o registro for encontrado, ou 0 caso contrário.
    
    */

}

void Cadastrar ( void ) {

    /*

    A função registra um novo item ( Produto, Vendedor ou Cliente ) no sistema. Solicita ao usuário as informações necessárias,
    grava os dados no arquivo correspondente e retorna ao menu após a conclusão.
    
    */

}

void Consultar ( void ) {

    /*

    A função exibe todos os registros de um arquivo específico. Lê os dados do arquivo e apresenta uma tabela com
    as informações coletadas. Retorna ao menu após a consulta.
    
    */

}

void Alterar ( void ) {

    /*

    A função permite modificar os dados de um registro existente. Solicita ao usuário o ID do registro, exibe os
    dados atuais e solicita confirmação. Após a confirmação, atualiza os dados no arquivo correspondente.
    
    */

}

void Excluir ( void ) {

    /*

    A função remove um registro do sistema. Solicita ao usuário o ID do registro, exibe os dados e solicita confirmação.
    Após a confirmação, o registro é removido do arquivo.
    
    */

}
```

### Funções de CRUD ( Vendas )

```c
void BaixaEstoque ( venda *resultado ) {

    /*

    A função atualiza o estoque de produtos após uma venda. Abre os arquivos de produtos e um temporário para regravar
    os dados. O estoque do produto vendido é reduzido com base na quantidade vendida. Após a atualização, o arquivo
    original é substituído pelo temporário.
    
    */

}

void AtribuirComissao ( venda *resultado ) {

    /*

    A função calcula e atribui a comissão de um vendedor com base em uma venda. Abre os arquivos de vendedores
    e um temporário para regravar os dados. A comissão é calculada como 3% do valor total da venda e adicionada
    ao total do vendedor. Após a atualização, o arquivo original é substituído pelo temporário.
    
    */

}

int ProximaVenda ( void ) {

    /*

    A função determina o próximo código de venda disponível. Lê o arquivo de vendas e identifica o maior código
    existente, retornando o próximo número. Caso não existam registros, retorna 1.
    
    */

}

int PesquisarVenda ( int id, venda *resultado ) {

    /*

    A função pesquisa uma venda pelo código. Abre o arquivo de vendas, localiza o registro correspondente ao ID
    fornecido e carrega os dados da venda na estrutura apontada por resultado. Retorna 1 se a venda for encontrada,
    ou 0 caso contrário.
    
    */

}

void CadastrarVenda ( void ) {

    /*

    A função registra uma nova venda no sistema. Solicita do usuário as informações do produto, cliente e vendedor.
    Calcula o valor total da venda e atualiza os dados correspondentes. Escreve as informações da venda no arquivo
    e atualiza o estoque e a comissão.
    
    */

}

void ConsultarVendas ( int redirect ) {

    /*

    A função exibe todas as vendas registradas. Lê os dados do arquivo de vendas e apresenta os detalhes de cada
    registro, incluindo informações do produto, cliente e vendedor. Retorna ao menu caso solicitado.
    
    */

}

void AlterarVenda ( void ) {

    /*

    A função permite modificar os dados de uma venda existente. Localiza a venda pelo código, exibe os dados atuais
    e solicita confirmação do usuário. Após a confirmação, atualiza os dados da venda no arquivo e ajusta as alterações
    relacionadas ao estoque e à comissão.
    
    */

}

void ExcluirVenda ( void ) {

    /*

    A função remove uma venda do sistema. Localiza a venda pelo código, exibe os dados e solicita confirmação do usuário.
    Após a confirmação, a venda é removida do arquivo, e os dados restantes são regravados.
    
    */

}

void GerarNotaFiscal ( void ) {

    /*

    A função gera uma nota fiscal para uma venda específica. Localiza a venda pelo código e coleta os dados do produto,
    cliente e vendedor. Cria um arquivo de texto no formato de nota fiscal contendo todas as informações da venda.
    
    */

}
```

## Testes

### Casos de teste do software

| Entradas                   | Classes Válidas                                                                           | Resultado Esperado                                                                           | Classes Inválidas                                                                | Resultado Esperado                                                   |                                                         |
| -------------------------- | ----------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------- | -------------------------------------------------------------------- | ------------------------------------------------------- |
| Exibir Menu Principal      | -                                                                                         | Menu Principal exibido com opções claras.                                                    | Entrada inválida (letras, símbolos)                                              | O menu é exibido novamente e solicita nova entrada.                  |                                                         |
| Cadastrar um Produto       | Nome: Teste, Estoque: 100, Preço: 50.00                                                   | Produto cadastrado com sucesso e exibido na próxima consulta.                                | Nome vazio ou caracteres inválidos, Estoque negativo, Preço negativo ou inválido | Mensagem de erro e solicitação para corrigir a entrada.              |                                                         |
| Alterar Produto Existente  | Código: 1, Nome: Novo, Estoque: 50, Preço: 60.00                                          | Produto com código 1 atualizado com os novos dados.                                          | Código inexistente, Nome vazio, Estoque ou Preço inválidos                       | Mensagem de erro informando os problemas e solicitando nova entrada. |                                                         |
| Consultar Produtos         | -                                                                                         | Lista completa de produtos cadastrados.                                                      | Arquivo de produtos ausente ou corrompido                                        | Mensagem indicando erro e retorno ao menu principal.                 |                                                         |
| Cadastrar um Vendedor      | Nome: João, Salário: 2000.00                                                              | Vendedor cadastrado com sucesso e exibido na próxima consulta.                               | Nome vazio, Salário negativo ou inválido                                         | Mensagem de erro e solicitação para corrigir a entrada.              |                                                         |
| Alterar Vendedor Existente | Código: 1, Nome: Maria, Salário: 3000.00                                                  | Vendedor com código 1 atualizado com os novos dados.                                         | Código inexistente, Nome vazio, Salário inválido                                 | Mensagem de erro informando os problemas e solicitando nova entrada. |                                                         |
| Consultar Vendedores       | -                                                                                         | Lista completa de vendedores cadastrados.                                                    | Arquivo de vendedores ausente ou corrompido                                      | Mensagem indicando erro e retorno ao menu principal.                 |                                                         |
| Cadastrar um Cliente       | CPF: 12345678900, Nome: Ana, Email: [ana@email.com](mailto\:ana@email.com)                                                       | Cliente cadastrado com sucesso e exibido na próxima consulta.                    | CPF inválido, Nome vazio, Email em formato incorreto                 | Mensagem de erro e solicitação para corrigir a entrada. |
| Alterar Cliente Existente  | CPF: 12345678900, Nome: Pedro, Email: [pedro@email.com](mailto\:pedro@email.com)          | Cliente com CPF 12345678900 atualizado com os novos dados.                                   | CPF inexistente, Nome vazio, Email inválido                                      | Mensagem de erro informando os problemas e solicitando nova entrada. |                                                         |
| Consultar Clientes         | -                                                                                         | Lista completa de clientes cadastrados.                                                      | Arquivo de clientes ausente ou corrompido                                        | Mensagem indicando erro e retorno ao menu principal.                 |                                                         |
| Registrar Nova Venda       | Código Produto: 1, CPF Cliente: 12345678900, Código Vendedor: 1, Quantidade: 10           | Venda registrada, estoque do produto atualizado, e comissão do vendedor calculada.           | Estoque insuficiente, Produto/Cliente/Vendedor inexistente ou inválido           | Mensagem de erro informando o problema e cancelamento da venda.      |                                                         |
| Alterar Venda              | Código: 1, Código Produto: 2, CPF Cliente: 98765432100, Código Vendedor: 2, Quantidade: 5 | Venda alterada com novos dados, ajustes aplicados ao estoque e à comissão.                   | Código inexistente, Produto/Cliente/Vendedor inválido ou quantidade inválida     | Mensagem de erro informando os problemas e solicitando nova entrada. |                                                         |
| Consultar Vendas           | -                                                                                         | Lista completa de vendas registradas, incluindo detalhes de produtos, clientes e vendedores. | Arquivo de vendas ausente ou corrompido                                          | Mensagem indicando erro e retorno ao menu principal.                 |                                                         |
| Excluir Venda              | Código: 1                                                                                 | Venda removida do sistema, informações relacionadas ajustadas.                               | Código inexistente ou inválido                                                   | Mensagem de erro informando código inválido e retorno ao menu.       |                                                         |
| Gerar Nota Fiscal          | Código Venda: 1                                                                           | Arquivo de nota fiscal gerado com informações completas da venda.                            | Código inexistente ou inválido                                                   | Mensagem de erro informando código inválido e retorno ao menu.       |                                                         |
