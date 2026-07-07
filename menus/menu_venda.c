#include <stdio.h>
#include <stdlib.h>
#include "menu_principal.h"
#include "../utils/utilidades.h"
#include "../structs/produto.h"
#include "../structs/venda.h"

static void imprimirMenu(void);
static void executarOpcao(char opcao, Carrinho *carrinho, FILE *arq_produtos, FILE *arq_vendas, int *venda_concluida);

// Função auxiliar para buscar produto e retorná-lo alocado dinamicamente
static Produto* buscarProdutoVenda(FILE *arq, int id) {
    Produto *p = (Produto *)malloc(sizeof(Produto));
    if (!p) return NULL;
    
    rewind(arq);
    while (fread(p, sizeof(Produto), 1, arq) == 1) {
        if (p->id == id) {
            return p;
        }
    }
    free(p);
    return NULL;
}

extern void MenuVenda(void)
{
    char opcao;
    int venda_concluida = 0;

    FILE *arq_produtos = fopen(ARQUIVO_PRODS, "rb+");
    if (arq_produtos == NULL) {
        printf("  ERRO: Nao foi possivel abrir '%s'.\n", ARQUIVO_PRODS);
        printf("  Verifique se existem produtos cadastrados.\n");
        pausar();
        return;
    }

    FILE *arq_vendas = fopen(NOME_ARQUIVO_VENDAS, "ab+");
    if (arq_vendas == NULL) {
        arq_vendas = fopen(NOME_ARQUIVO_VENDAS, "wb+");
    }

    Carrinho carrinho;
    InicializaCarrinho(&carrinho); 

    do {
        limparTela();
        printf("  --- PRODUTOS DISPONIVEIS ---\n");
        ListaProdutosVenda(ExibeProdutoPadrao, arq_produtos); 

        printf("  --- CARRINHO ATUAL ---\n");
        ExibeCarrinho(&carrinho); 

        imprimirMenu();
        imprimirPrompt();
        opcao = getOpcao();
        executarOpcao(opcao, &carrinho, arq_produtos, arq_vendas, &venda_concluida);
    } while(!venda_concluida && opcao != '5');

    LimpaCarrinho(&carrinho);
    fclose(arq_produtos);
    if (arq_vendas) fclose(arq_vendas);
}

static void imprimirMenu(void)
{
    printf("\n=============================\n");
    printf("        MENU DE VENDA\n");
    printf("=============================\n");
    printf("1 - Adicionar Produto ao Carrinho\n");
    printf("2 - Remover Produto do Carrinho\n");
    printf("3 - Finalizar Compra\n");
    printf("4 - Gerar Relatorio de Vendas\n");
    printf("5 - Voltar\n");
}

static void opcao_adicionar(Carrinho *carrinho, FILE *arq_produtos) {
    printf("\n  ID do produto: ");
    int id = lerInteiro(); 
    if (id <= 0) {
        printf("  ID invalido.\n");
        pausar();
        return;
    }

    Produto *p = buscarProdutoVenda(arq_produtos, id);
    if (p == NULL) {
        printf("  ERRO: Produto ID %d nao encontrado.\n", id);
        pausar();
        return;
    }

    printf("  Quantidade   : ");
    int qtd = lerInteiro();
    if (qtd <= 0) {
        printf("  Quantidade deve ser maior que zero.\n");
        free(p);
    } else {
        int sucesso = AdicionaItemCarrinho(carrinho, p, qtd);
        if (sucesso) {
            free(p); // Libera o nó original após a cópia para a lista encadeada
        }
    }
    pausar();
}

static void opcao_remover(Carrinho *carrinho) {
    printf("\n  ID do produto a remover: ");
    int id = lerInteiro();
    Produto p_temp;
    p_temp.id = id;

    Carrinho *ptr_carrinho = carrinho;
    if (RemoveItemCarrinhoById(&ptr_carrinho, &p_temp)) {
        printf("  Produto removido do carrinho com sucesso!\n");
    } else {
        printf("  Produto nao encontrado no carrinho.\n");
    }
    pausar();
}

static void opcao_finalizar(Carrinho *carrinho, FILE *arq_produtos, FILE *arq_vendas, int *venda_concluida) {
    if (carrinho->qtd_itens == 0) {
        printf("  Carrinho vazio. Nao e possivel finalizar a compra.\n");
        pausar();
        return;
    }

    printf("  Total da compra: R$ %.2f\n", carrinho->total);
    printf("  Valor pago pelo cliente: R$ ");
    float valor_pago = lerFloat();

    if (valor_pago < carrinho->total) {
        printf("  Valor insuficiente!\n");
        pausar();
        return;
    }

    RegistroVenda reg;
    fseek(arq_vendas, 0, SEEK_END);
    reg.id_venda = (ftell(arq_vendas) / sizeof(RegistroVenda)) + 1;
    reg.qtd_itens = carrinho->qtd_itens;
    reg.total = carrinho->total;
    reg.valor_pago = valor_pago;
    reg.troco = valor_pago - carrinho->total;

    ItemCarrinho *atual = carrinho->cabeca;
    int index = 0;
    while (atual != NULL && index < MAX_ITENS_NOTA) {
        reg.ids_produtos[index] = atual->produto.id;
        reg.quantidades[index] = atual->produto.quantidade;
        reg.precos[index] = atual->produto.preco;

        // Atualizar estoque no arquivo produtos.dat
        Produto p_file;
        rewind(arq_produtos);
        long pos = 0;
        while (fread(&p_file, sizeof(Produto), 1, arq_produtos) == 1) {
            if (p_file.id == atual->produto.id) {
                p_file.quantidade -= atual->produto.quantidade;
                fseek(arq_produtos, pos, SEEK_SET);
                fwrite(&p_file, sizeof(Produto), 1, arq_produtos);
                break;
            }
            pos = ftell(arq_produtos);
        }

        atual = atual->proximo;
        index++;
    }

    // Assinatura atualizada (requer alteração no venda.h e venda.c explicada abaixo)
    ImprimirNotaFiscal(carrinho, valor_pago);
    SalvaRegistroVenda(&reg, arq_vendas);

    *venda_concluida = 1;
    printf("  Compra finalizada com sucesso!\n");
    pausar();
}

static void executarOpcao(char opcao, Carrinho *carrinho, FILE *arq_produtos, FILE *arq_vendas, int *venda_concluida)
{
    switch(opcao)
    {
        case '1':
            opcao_adicionar(carrinho, arq_produtos);
            break;
        case '2':
            opcao_remover(carrinho);
            break;
        case '3':
            opcao_finalizar(carrinho, arq_produtos, arq_vendas, venda_concluida);
            break;
        case '4':
            GerarRelatorioVendas(arq_vendas);
            pausar();
            break;
        case '5':
            break;
        default:
            printf("Opcao invalida.\n");
            pausar();
            break;
    }
}