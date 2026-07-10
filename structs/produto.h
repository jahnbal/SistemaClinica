#pragma once

#define TAM_NOME_PRODUTO 30
#define ARQUIVO_PRODS "produtos.dat"

// Cadastra/Exclui/Edita/Lista/Pesquisa

typedef struct {

  int id;
  char nome[TAM_NOME_PRODUTO];
  float preco;
  int quantidade;

} Produto;

void CadastrarProduto();

int VerificaIdIgualProduto(int id);

int ExcluirProduto(int id);

int EditarProduto(int id);

int ListarProdutos();

int BuscarProdutoPorId(int id);
