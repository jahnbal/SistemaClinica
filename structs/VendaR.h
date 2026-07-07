#include "produto.h"

typedef struct ItemCarrinho {
  Produto produto;
  struct ItemCarrinho *proximo; /* próximo nó da lista encadeada */
} ItemCarrinho;

void adicionarProduto(No **carrinho, Produto produto);