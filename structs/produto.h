#pragma once
/*
Cadastra/Exclui/Edita/Lista/Pesquisa

*/

#define TAM_NOME_PRODUTO 30
#define ARQUIVO_PRODS "produtos.dat"

typedef struct {

  int id;
  char nome[TAM_NOME_PRODUTO];
  float preco;
  int quantidade;

} Produto;

void CadastrarProduto();

int ExcluirProduto(int id);

int EditarProduto(int id);

int ListarProdutos();

int BuscarProdutoPorId(int id);
