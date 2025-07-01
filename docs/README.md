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

#### Vídeo da Sprint Review 1

<video controls src="https://drive.google.com/file/d/1pBFGt84QIfaL8YDWjHtNCMNnhU8DvCaJ/view?usp=drive_link" title="Sprint Review 1"></video>

## Documentação das Funcionalidades

### Menu Principal

```c
void MenuPrincipal ( void ) {

    /*

    A Função gera um menu que recebe uma entrada do usuário e retorna o menu de alguma das outras funções.

    Entrada 0 - Encerra o programa.
    Entrada 1 - Direciona para MenuProdutos();
    Entrada 2 - Direciona para MenuVendedores();
    Entrada 3 - Direciona para MenuClientes();
    Entrada 4 - Direciona para MenuVendas();
    Outra Entrada - Repete função MenuPrincipal();

    */

}
```

### Funções de CRUD ( Produtos , Vendedores e Clientes )

```c
void Menu ( void ) {

    /*
    
    Existe uma função de menu padronizada para Prdutos, Vendedores e Clientes. Em ambas há uma entrada do usuário que retorna para alguma das funções de CRUD ou retorna pro Menu Principal.

    Entrada 0 - Retorna ao MenuPrincipal();
    Entrada 1 - Direciona para a função de Cadastro.
    Entrada 2 - Direciona para a função de Consulta.
    Entrada 3 - Direciona para a função de Edição.
    Entrada 4 - Direciona para a função de Exclusão.
    Outra Entrada - Repete a função de Menu.
    
    */

}

int ProximoID ( void ) {

    /*
    
    Para vendedores, produtos e vendas essa função abre o arquivo txt com a base de dados, busca o maior ID dos dados registrados e retorna esse valor mais um.
    
    */

}

int Pesquisar ( int id , struct *resultado ) {

    /*
    
    A função de pesquisa, abre um arquivo referente a base de dados usada, busca por um id igual ao passado por parâmetro, e caso encontre um resultado válido, ela retorna o restante das informações para o conteúdo apontado pelo ponteiro. Para confirmar se a pesquisa foi bem sucedida, ela retorna um, caso contrário ela retorna zero. 
    
    */

}

void Cadastrar ( void ) {

    /*
    
    A função abre um arquivo txt para escrita, na sequencia pede uma entrada ao usuário onde ele irá inserir os dados do Produto, Vendedor ou Cliente. Os dados recebidos são escritos no arquivo de texto e por fim a função retorna o Menu.
    
    */

}

void Consultar ( void ) {

    /*
    
    A função abre um arquivo txt para leitura, na sequencia ela gera um cabeçalho de tabela e procura pelos dados presentes no txt e adiciona-os em uma variável, depois essa variável é usada para emprimir os dados coletados em sequencia, gerando assim uma tabela completa. Após a tabela gerado, a função aguarda um input qualquer do usuário para retornar ao Menu.
    
    */

}

void Alterar ( void ) {

    /*
    
    A função abre um arquivo txt com os dados e um arquivo txt temporário, na sequencia ela pede ao usuário que entre com o código, número ou cpf referente aos dados procurados, essa informação é usada por outra função ( Pesquisar ), para obter o restantes dos dados. Caso a pesquisa falhe, é mostrado uma mensagem de erro e retorna ao Menu, caso a pesquisa seja bem sucedida, retorna uma tabela com os dados buscados e abre um campo de confirmação.

    Entrada 0 - Retorna ao Menu.
    Entrada 1 - Aciona um recadastro dos dados.

    Ao final do preenchimento dos dados, as novas informações junto ao resto da base de dados é inserida no arquivo txt temporário, o arquivo original é excluido e o temporário recebe o nome do original.
    
    */

}

void Excluir ( void ) {

    /*
    
    A função abre um arquivo txt com os dados e um arquivo txt temporário, na sequencia ela pede ao usuário que entre com o código, número ou cpf referente aos dados procurados, essa informação é usada por outra função ( Pesquisar ), para obter o restantes dos dados. Caso a pesquisa falhe, é mostrado uma mensagem de erro e retorna ao Menu, caso a pesquisa seja bem sucedida, retorna uma tabela com os dados buscados e abre um campo de confirmação.

    Entrada 0 - Retorna ao Menu.
    Entrada 1 - Confirma a exclusão dos dados.

    As informações da base de dados são escritas no arquivo txt temporário, pulando os dados selecionados para exclusão, ao final o arquivo original é apagado e o arquivo temporário é renomeado substituindo o original.
    
    */

}
```

### Função de CRUD ( Vendas )

```c
void BaixaEstoque ( venda *resultado ) {



}
```

