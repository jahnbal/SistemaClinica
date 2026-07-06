/*
Cadastra/Exclui/Edita/Lista/Pesquisa

*/

#define TAM_NOME_PRODUTO 30

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
