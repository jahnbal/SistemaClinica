#include "VendaR.h"

void adicionarProduto(No **carrinho, Produto produto)
{
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL)
    {
        printf("Erro de alocacao de memoria.\n");
        return;
    }