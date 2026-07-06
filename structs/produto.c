#include "produto.h"
#include <stdio.h>

/*
Cadastra/Exclui/Edita/Lista/Pesquisa



typedef struct {
	
	int id;
	char nome[TAM_NOME_PRODUTO];
	float preco;
	int quantidade;
	int ativo; //1 ativo, 0 inativo
// Descrição tirei pq n é usada
// Agente ta literalmente só cadastradando e alterando
}
*/
#define ARQUIVO_PRODS "produtos.dat"




static void preencherProduto(Produto *p)
{
    printf("---- NOVO PRODUTO ----\n");
    printf("ID: ");
    scanf("%d", &p->id);

    printf("Nome: ");
    scanf("%s", p->nome);

    printf("Preço: ");
    scanf("%f", &p->preco);

    printf("Quantidade: ");
    scanf("%d", &p->quantidade);

    p->ativo = 1;
}



static int salvarProduto(Produto *p)
{
    FILE *arquivo = fopen(ARQUIVO_PRODS, "ab");
    if (arquivo == NULL) {
        perror("[Erro] Arquivo não pode ser aberto.\n");
        return 0;
    }

    fwrite(p, sizeof(Produto), 1, arquivo);
    fclose(arquivo);
    printf("Produto salvo com sucesso!\n");
    return 1;
}

void CadastrarProduto()
{
    Produto p;

    preencherProduto(&p);
    salvarProduto(&p);
} 

int ExcluirProduto(int id) {
  FILE *arquivo = fopen(ARQUIVO_PRODS, "rb");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    return 0;
  }

  FILE *temp = fopen("temp_prods.dat", "wb");
  if (temp == NULL) {
    perror("[Erro] Não foi possível criar arquivo temporário.\n");
    fclose(arquivo);
    return 0;
  }

  Produto p;
  int encontrado = 0;

  while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
    if (p.id == id) {
      encontrado =
          1; // não copia esse pet para o temp (ou seja, ele é "excluído")
      continue;
    }
    fwrite(&p, sizeof(Produto), 1, temp);
  }

  fclose(arquivo);
  fclose(temp);

  remove(ARQUIVO_PRODS); // apaga o arquivo original
  rename("temp_prods.dat",
         ARQUIVO_PRODS); // renomeia o temporário para o nome original

  if (encontrado) {
    printf("Produto removido com sucesso!\n");
    return 1;
  } else {
    printf("Produto com ID %d não encontrado.\n", id);
    return 0;
  }
}

int EditarProduto(int id);

int ListarTodosProdutos(); 

int BuscarProdutoPorId(int id);