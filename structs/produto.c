#include "produto.h"
#include "../utils/utilidades.h"
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

static void preencherProduto(Produto *p) {
  printf("---- NOVO PRODUTO ----\n");
  printf("ID: ");
  scanf("%d", &p->id);

  printf("Nome: ");
  scanf("%s", p->nome);

  printf("Preço: ");
  scanf("%f", &p->preco);

  printf("Quantidade: ");
  scanf("%d", &p->quantidade);
}

static int salvarProduto(Produto *p) {
  FILE *arquivo = fopen(ARQUIVO_PRODS, "ab");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  fwrite(p, sizeof(Produto), 1, arquivo);
  fclose(arquivo);
  printf("Produto salvo com sucesso!\n");
  pausar();
  return 1;
}

void CadastrarProduto() {
  Produto p;

  preencherProduto(&p);
  salvarProduto(&p);
  limparBuffer();
}

int ExcluirProduto(int id) {
  FILE *arquivo = fopen(ARQUIVO_PRODS, "rb");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  FILE *temp = fopen("temp_prods.dat", "wb");
  if (temp == NULL) {
    perror("[Erro] Não foi possível criar arquivo temporário.\n");
    pausar();
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
    pausar();
    return 1;
  } else {
    printf("Produto com ID %d não encontrado.\n", id);
    pausar();
    return 0;
  }
}

int EditarProduto(int id) {
  FILE *arquivo = fopen(ARQUIVO_PRODS, "r+b");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  Produto p;
  int encontrado = 0;
  long posicao;

  while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
    if (p.id == id) {
      encontrado = 1;
      posicao = ftell(arquivo) - sizeof(Produto);

      printf("---- EDITAR PRODUTO (ID: %d) ----\n", p.id);
      printf("Nome atual: %s\n", p.nome);
      printf("Preço atual: %.2f\n", p.preco);
      printf("Quantidade atual: %d\n", p.quantidade);

      int opcao;
      do {
        printf("\nO que deseja alterar?\n");
        printf("1 - Nome\n");
        printf("2 - Preço\n");
        printf("3 - Quantidade\n");
        printf("0 - Finalizar edição\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
          printf("Novo nome: ");
          scanf("%s", p.nome);
          break;
        case 2:
          printf("Novo preço: ");
          scanf("%f", &p.preco);
          break;
        case 3:
          printf("Nova quantidade: ");
          scanf("%d", &p.quantidade);
          break;
        case 0:
          printf("Finalizando edição...\n");
          break;
        default:
          printf("Opção inválida!\n");
          break;
        }
      } while (opcao != 0);

      fseek(arquivo, posicao, SEEK_SET);
      fwrite(&p, sizeof(Produto), 1, arquivo);
      break;
    }
  }

  fclose(arquivo);

  if (encontrado) {
    printf("Produto editado com sucesso!\n");
    return 1;
  } else {
    printf("Produto com ID %d não encontrado.\n", id);
    return 0;
  }
}

int ListarProdutos() {
  FILE *arquivo = fopen(ARQUIVO_PRODS, "rb");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  Produto p;
  int contador = 0;

  printf("\n---- LISTA DE PRODUTOS ----\n");

  while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
    contador++;
    printf("\nID: %d\n", p.id);
    printf("Nome: %s\n", p.nome);
    printf("Preço: %.2f\n", p.preco);
    printf("Quantidade: %d\n", p.quantidade);
    printf("---------------------------\n");
  }

  fclose(arquivo);

  if (contador == 0) {
    printf("Nenhum produto cadastrado.\n");
    return 0;
  }

  printf("Total de produtos: %d\n", contador);
  pausar();
  return contador;
}

int BuscarProdutoPorId(int id) {
  FILE *arquivo = fopen(ARQUIVO_PRODS, "rb");
  if (arquivo == NULL) {
    perror("[Erro] Arquivo não pode ser aberto.\n");
    pausar();
    return 0;
  }

  Produto p;
  int encontrado = 0;

  while (fread(&p, sizeof(Produto), 1, arquivo) == 1) {
    if (p.id == id) {
      encontrado = 1;
      printf("\n---- PRODUTO ENCONTRADO ----\n");
      printf("ID: %d\n", p.id);
      printf("Nome: %s\n", p.nome);
      printf("Preço: %.2f\n", p.preco);
      printf("Quantidade: %d\n", p.quantidade);
      printf("-----------------------------\n");
      pausar();
      break;
    }
  }

  fclose(arquivo);

  if (!encontrado) {
    printf("Produto com ID %d não encontrado.\n", id);
    pausar();
    return 0;
  }

  return 1;
}
