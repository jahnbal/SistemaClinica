#include <stdio.h>
#include "menu_principal.h"
#include "menu_atendimento.h"
#include "menu_gerenciar_cadastros.h"
#include "../utils/utilidades.h"
#include "../structs/pet.h"
#include "../structs/veterinario.h"
#include "../structs/produto.h"

/*

MenuPrincipal()
│
├── imprimirMenuPrincipal()
├── obterOpcao()
└── executarOpcaoMenuPrincipal(opcao)


MenuPrincipal() → controla o fluxo do menu.
imprimirMenuPrincipal() → apenas exibe o menu.
obterOpcao() → captura a opção do usuário.
executarOpcaoMenuPrincipal() → decide qual ação executar.


Para cada função MenuX o padrão é esse. MenuPrincipal está de acordo com o padrão 
{
    char opcao;

    do
    {
        imprimirMenuPrincipal();

        opcao = obterOpcao();

        executarOpcaoMenuPrincipal(opcao);

    } while (opcao != '0');

    return 0;
}
*/ 
static void imprimirMenu(void);
static void executarOpcaoMenu(char opcao);


extern void MenuBuscar(void)
{
    char opcao;

    do {
        imprimirMenu();
        imprimirPrompt();
        opcao = getOpcao();
        executarOpcaoMenu(opcao);
    } while(opcao != '4');
}

static void imprimirMenu(void)
{
    limparTela();
    printf("\n========== BUSCA ==========\n");
    printf("1 - Buscar Pet\n");
    printf("2 - Buscar Veterinario\n");
    printf("3 - Buscar Produto\n");
    printf("4 - Voltar\n");
}
static void executarOpcaoMenu(char opcao)
{
    switch(opcao)
    {
        case '1':
            BuscarPetPorId();
            break;

        case '2':
            BuscarVeterinarioPorId();
            break;

        case '3':
            BuscarProdutoPorId();
            break;

        case '4':
            printf("\nEncErrando sistema...\n");
            break;

        default:
            printf("\nOpcao invalida.");
            pausar();
            break;
    }
}

