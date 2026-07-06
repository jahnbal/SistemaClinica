/*
Cadastra/Exclui/Edita/Lista/Pesquisa

*/

#define TAM_NOME_PRODUTO 30

typedef struct {
	
	int id;
	char nome[TAM_NOME_PRODUTO];
	float preco;
	int quantidade;
	int ativo; 

} Produto;




void CadastrarProduto(); 

void ExcluirProduto(int id); 

int EditarProduto(int id);

int ListarTodosProdutos(); 

int BuscarProdutoPorId(int id);