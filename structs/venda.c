#include "produto.h"
#include "venda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Inicializa a entidade Carrinho
void InicializaCarrinho(Carrinho *carrinho) {
  carrinho->cabeca = NULL;
  carrinho->qtd_itens = 0;
  carrinho->total = 0.0f;
}


// malloc para cada novo nó da lista
int AdicionaItemCarrinho(Carrinho *carrinho, Produto *prod, int quantidade) {

  BuscarProdutoPorId(prod->id);
  if (prod == NULL) {
    printf("  ERRO: Produto ID %d nao encontrado ou inativo.\n", prod->id);
    return 0;
  }
  if (prod->quantidade < quantidade) {
    printf("  AVISO: Estoque insuficiente (disponivel: %d unidades).\n",
           prod->quantidade);
    free(prod);
    return 0;
  }

  // Se o produto já está no carrinho, apenas atualiza a quantidade
  ItemCarrinho *atual = carrinho->cabeca;
  while (atual != NULL) {
    if (atual->produto.id == prod->id) {
      atual->produto.quantidade += quantidade;
      atual->total_item = atual->produto.preco * atual->produto.quantidade;

      carrinho->total = CalculaTotalRecursivo(carrinho->cabeca);

      return 1;
    }
    atual = atual->proximo;
  }

  ItemCarrinho *novo = malloc(sizeof(ItemCarrinho));
  if (novo == NULL) {
    printf("  ERRO: Memoria insuficiente para adicionar item.\n");
    return 0;
  }

  novo->produto.id = prod->id;
  strncpy(novo->produto.nome, prod->nome, TAM_NOME_PRODUTO - 1);
  novo->produto.nome[TAM_NOME_PRODUTO - 1] = '\0';
  novo->produto.preco = prod->preco;
  novo->produto.quantidade = quantidade;
  novo->total_item = prod->preco * (float)quantidade;

  // Inserção no início da lista encadeada
  novo->proximo = carrinho->cabeca;
  carrinho->cabeca = novo;
  carrinho->qtd_itens++;
  carrinho->total = CalculaTotalRecursivo(carrinho->cabeca);

  printf("  \"%s\" adicionado ao carrinho.\n", prod->nome);

  return 1;
}


//  usa ItemCarrinho** para reescrever qualquer
int RemoveItemCarrinhoById(Carrinho **carrinho, Produto *prod) {
  if (carrinho == NULL || *carrinho == NULL || prod == NULL)
    return 0;

  ItemCarrinho *atual = (*carrinho)->cabeca;
  ItemCarrinho *anterior = NULL;

  while (atual != NULL) {
    if (atual->produto.id == prod->id) {
      // Ajusta o total do carrinho antes de remover
      (*carrinho)->total -= atual->total_item;
      (*carrinho)->qtd_itens -= atual->produto.quantidade;

      // Reconecta a lista, pulando o nó removido
      if (anterior == NULL) {
        (*carrinho)->cabeca = atual->proximo;
      } else {
        anterior->proximo = atual->proximo;
      }

      free(atual);
      return 1; // sucesso
    }
    anterior = atual;
    atual = atual->proximo;
  }

  return 0; // produto não encontrado no carrinho
}

// Limpa completamete o carrinho
void LimpaCarrinho(Carrinho *carrinho) {
  if (carrinho == NULL)
    return;

  ItemCarrinho *atual = carrinho->cabeca;
  while (atual != NULL) {
    ItemCarrinho *prox = atual->proximo;
    free(atual);
    atual = prox;
  }
  carrinho->cabeca = NULL;
  carrinho->qtd_itens = 0;
  carrinho->total = 0.0f;
}

/* 
   CÁLCULO RECURSIVO DO TOTAL:
    Caso Base: lista vazia → retorna 0.0
    Passo: total_item do nó atual + resultado recursivo para o próximo nó
 */

float CalculaTotalRecursivo(ItemCarrinho *item) {
  if (item == NULL)
    return 0.0f;
  return item->total_item + CalculaTotalRecursivo(item->proximo);
}

// Exibe o produto implementação padrão do tipo FuncExibeProduto
void ExibeProdutoPadrao(Produto *p) {
  printf("  %-5d | %-30s | R$ %-8.2f | Estoque: %d\n", p->id, p->nome, p->preco,
         p->quantidade);
}

// LISTAGEM DE PRODUTOS COM PONTEIRO DE FUNÇÃO
void ListaProdutosVenda(FuncExibeProduto exibe, FILE *arq_produtos) {
  Produto p;
  int total = 0;
  rewind(arq_produtos);

  printf("  %-5s | %-30s | %-11s | %s\n", "ID", "NOME", "PRECO", "ESTOQUE");
  printf("  %s\n", "--------------------------------------------------------");

  while (fread(&p, sizeof(Produto), 1, arq_produtos) == 1) {
    if (p.quantidade > 0) {
      exibe(&p); // chama com ponteiro para função
      total++;
    }
  }
  if ( (total ^ 0) == 0 )
    printf("  (nenhum produto disponivel em estoque)\n");
  printf("\n");
}

// EXIBIÇÃO DO CARRINHO
void ExibeCarrinho(Carrinho *carrinho) {
  if (carrinho->qtd_itens == 0) {
    printf("  [carrinho vazio]\n\n");
    return;
  }

  printf("  %-30s | %-5s | %-10s | %s\n", "PRODUTO", "QTD", "UNIT. (R$)",
         "TOTAL (R$)");
  printf("  %s\n",
         "------------------------------------------------------------");

  // Percorre a lista encadeada
  ItemCarrinho *atual = carrinho->cabeca;
  while (atual != NULL) {
    printf("  %-30s | %-5d | %-10.2f | %.2f\n", atual->produto.nome,
           atual->produto.quantidade, atual->produto.preco, atual->total_item);
    atual = atual->proximo;
  }

  printf("  %s\n",
         "------------------------------------------------------------");
  printf("  TOTAL DO CARRINHO: R$ %.2f\n\n", carrinho->total);
}

// NOTA FISCAL
void ImprimirNotaFiscal(Carrinho *carrinho, float valor_pago) {
  float troco = valor_pago - carrinho->total;

  printf("\n  ===========================================================\n");
  printf("  * NOTA FISCAL                            *\n");
  printf("  ===========================================================\n");
  printf("  %-30s | %-5s | %-10s | %s\n", "PRODUTO", "QTD", "UNIT. (R$)", "TOTAL (R$)");
  printf("  ------------------------------------------------------------\n");

  ItemCarrinho *atual = carrinho->cabeca;
  while (atual != NULL) {
    printf("  %-30s | %-5d | %-10.2f | %.2f\n", atual->produto.nome,
           atual->produto.quantidade, atual->produto.preco, atual->total_item);
    atual = atual->proximo;
  }

  printf("  ===========================================================\n");
  printf("  TOTAL DA COMPRA : R$ %.2f\n", carrinho->total);
  printf("  VALOR PAGO      : R$ %.2f\n", valor_pago);
  printf("  TROCO           : R$ %.2f\n", troco);
  printf("  ===========================================================\n");
  printf("  Obrigado! Volte sempre.\n\n");
}

// PERSISTÊNCIA DA VENDA
int SalvaRegistroVenda(RegistroVenda *venda, FILE *arq_vendas) {
  fseek(arq_vendas, 0, SEEK_END);
  if (fwrite(venda, sizeof(RegistroVenda), 1, arq_vendas) != 1) {
    perror("[Erro] não foi possível gravar venda");
    return 0;
  }
  fflush(arq_vendas);
  return 1;
}


void GerarRelatorioVendas(FILE *arq_vendas) {
#define NUM_COLUNAS 4

  // Conta registros
  fseek(arq_vendas, 0, SEEK_END);
  long tam = ftell(arq_vendas);
  int nLinhas = (int)(tam / (long)sizeof(RegistroVenda));

  if (nLinhas == 0) {
    printf("  Nenhuma venda registrada.\n");
    return;
  }

  // Aloca vetor dinâmico de ponteiros (linhas)
  float **matriz = (float **)malloc(nLinhas * sizeof(float *));
  if (matriz == NULL) {
    printf("  ERRO: Memoria insuficiente para o relatorio.\n");
    return;
  }

  // Aloca cada linha (vetor de NUM_COLUNAS floats)
  for (int i = 0; i < nLinhas; i++) {
    matriz[i] = (float *)malloc(NUM_COLUNAS * sizeof(float));
    if (matriz[i] == NULL) {
      // Libera o que já foi alocado antes de sair
      for (int k = 0; k < i; k++)
        free(matriz[k]);
      free(matriz);
      printf("  ERRO: Memoria insuficiente para o relatorio.\n");
      return;
    }
  }

  // Preenche a matriz lendo os registros do arquivo
  RegistroVenda reg;
  rewind(arq_vendas);
  for (int i = 0; i < nLinhas; i++) {
    if (fread(&reg, sizeof(RegistroVenda), 1, arq_vendas) != 1)
      break;
    *(*(matriz+i) + 0) = (float)reg.id_venda;
    *(*(matriz+i) + 1) = (float)reg.qtd_itens; 
    *(*(matriz+i) + 2) = reg.total; 
    *(*(matriz+i) + 3) = reg.troco; 
  }

  // Exibe a tabela
printf("\n");
printf("  ========== RELATORIO DE VENDAS ==========\n");
printf("  %-10s | %-8s | %-10s | %-10s\n",
       "ID VENDA", "ITENS", "TOTAL(R$)", "TROCO(R$)");
printf("  %s\n",
       "-------------------------------------------------------");

for (int i = 0; i < nLinhas; i++) {
    printf("  %-10.0f | %-8.0f | %-10.2f | %-10.2f\n",
           matriz[i][0],   // id_venda
           matriz[i][1],   // qtd_itens
           matriz[i][2],   // total
           matriz[i][3]);  // troco
}

printf("  %s\n",
       "-------------------------------------------------------");
  printf("  Total de vendas: %d\n\n", nLinhas);

  // Libera a matriz dinâmica
  for (int i = 0; i < nLinhas; i++)
    free(matriz[i]);
  free(matriz);

#undef NUM_COLUNAS
}
