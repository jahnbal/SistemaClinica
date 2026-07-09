#ifndef VENDA_H
#define VENDA_H

#include "pet.h"
#include "produto.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITENS_NOTA 50
#define NOME_ARQUIVO_VENDAS "vendas.dat"

typedef void (*FuncExibeProduto)(Produto *produto);

// Cada item do carrinho é um nó da lista encadeada
typedef struct ItemCarrinho {

  Produto produto;

  struct ItemCarrinho *proximo; /* próximo nó da lista encadeada */

  float total_item;

} ItemCarrinho;

// Carrinho de compras: cabeça da lista encadeada + metadados.
typedef struct {
  ItemCarrinho *cabeca; /* [LP2 — Lista Encadeada] cabeça da lista */
  int qtd_itens;
  float total;
} Carrinho;

/*
 * Registro persistente de venda (gravado em vendas.dat).
 * Usa vetores de tamanho fixo para as colunas da nota fiscal.
 */


typedef struct {
  int id_venda;
  int qtd_itens;
  /* arrays paralelos dos itens vendidos */
  int ids_produtos[MAX_ITENS_NOTA];
  int quantidades[MAX_ITENS_NOTA];
  float precos[MAX_ITENS_NOTA];
  float total;
  float valor_pago;
  float troco;
} RegistroVenda;

// Inicializa um carrinho vazio
void InicializaCarrinho(Carrinho *carrinho);

// Adiona um item ao carrinho, alocando dinamicamente um novo nó da lista
// encadeada.
int AdicionaItemCarrinho(Carrinho *carrinho, Produto *prod, int quantidade);

// Remove um item do carrinho pelo ID do produto, liberando o nó da lista
// encadeada.
int RemoveItemCarrinhoById(Carrinho **carrinho, Produto *prod);

// Libera todos os itens do carrinho
void LimpaCarrinho(Carrinho *carrinho);

// Percorre recursivamente a lista encadeada do carrinho e calcula o total da
// compra.
float CalculaTotalRecursivo(ItemCarrinho *item);

// Lista todos os produtos disponíveis para venda, chamando a função de callback
// exibe().
void ListaProdutosVenda(FuncExibeProduto exibe, FILE *arq_produtos);

// Implementação padrão de FuncExibeProduto
void ExibeProdutoPadrao(Produto *prod);

/* Exibe o carrinho formatado na tela */
void ExibeCarrinho(Carrinho *carrinho);

/* ═══════════════════════════════════════════════════════════════════════════
 *  FLUXO PRINCIPAL DE VENDA
 * ═══════════════════════════════════════════════════════════════════════════
 */

/* Imprime a nota fiscal completa no terminal */
void ImprimirNotaFiscal(Carrinho *carrinho, float valor_pago);

/* Grava o RegistroVenda no arquivo vendas.dat. Retorna 1 em sucesso */
int SalvaRegistroVenda(RegistroVenda *venda, FILE *arq_vendas);

/*
 * [LP2 — Matriz Dinâmica]
 * Lê todos os registros de vendas e exibe um relatório em formato de
 * tabela usando uma matriz alocada dinamicamente (linhas × colunas).
 * Colunas: [ID venda | Qtd itens | Total | Troco]
 */
void GerarRelatorioVendas(FILE *arq_vendas);

#endif /* VENDA_H */
