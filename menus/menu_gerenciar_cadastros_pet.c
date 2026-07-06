#include <stdio.h>
#include "menu_principal.h"
#include "menu_atendimento.h"
#include "menu_gerenciar_cadastros.h"
#include "../utils/utilidades.h"

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


extern void MenuPrincipal(void)
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
    printf("\n========================================\n");
    printf("            MENU PET\n");
    printf("========================================\n");
    printf("1 - Cadastrar Pet\n");
    printf("2 - Remover Pet\n");
    printf("3 - Atualizar Pet\n");
    printf("4 - Voltar\n");
}
static void executarOpcaoMenu(char opcao)
{
// SÓ FUNÇÕES NESSE NÍVEL
    switch (opcao)
    {
        case '1':
            CadastrarPet();
            break;

        case '2':
            ExcluirPet();
            break;

        case '3':
            EditarPet();
            break;

        case '4':
            break;

        default:
            printf("\nOpcao invalida.\n");
    }
    
}

