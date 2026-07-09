#include "../structs/consulta.h"
#include "../utils/utilidades.h"
#include "menu_buscar.h"
#include "menu_gerenciar_cadastros.h"
#include "menu_principal.h"
#include "menu_realizar_atendimento.h"
#include <stdio.h>
#include <stdlib.h>

static void imprimirMenu(void);
static void executarOpcaoMenu(char opcao);

extern void MenuConsultas(void) {
  char opcao;

  do {
    imprimirMenu();
    imprimirPrompt();
    opcao = getOpcao();
    executarOpcaoMenu(opcao);

  } while (opcao != '5');
}

static void imprimirMenu(void) {
  limparTela();
  printf("\n=============================\n");
  printf("          CONSULTAS\n");
  printf("=============================\n");
  printf("1 - Agendar Consulta\n");
  printf("2 - Marcar como Realizada\n");
  printf("3 - Cancelar Consulta\n");
  printf("4 - Listar Consultas\n");
  printf("5 - Voltar\n");
}
static void executarOpcaoMenu(char opcao) {

  static ListaConsulta *lista = NULL;

  if (!lista) {
    lista = InicializarLista();
  }

  Consulta *consulta = malloc(sizeof(Consulta));
  Consulta *buscada;
  int removida;
  int conflito = -1;

  switch (opcao) {
  case '1':
    PreencheDadosConsulta(consulta);
    conflito = VerificarConflito(lista, *consulta);

    if (conflito == 0) {
      InserirConsulta(lista, *consulta);
      printf("Consulta Marcada!\n");

    } else {
      printf("Erro, consulta indisponivel por conflito\n");
    }
    pausar();
    break;

  case '2':

    PedeDadosParaBusca(consulta);

    buscada = BuscarConsulta(lista, *consulta);

    if (buscada) {

      printf("Consulta finalizada!\n");
    } else {
      printf("Consulta não encontrada\n");
    }
    pausar();
    break;

  case '3':

    PedeDadosParaBusca(consulta);

    buscada = BuscarConsulta(lista, *consulta);
    if (buscada) {
      removida = RemoverConsulta(lista, *consulta);

      if (removida == 1) {
        printf("Consulta Removida com suceso!\n");
      }
    } else {
      printf("Consulta não encontrada\n");
    }
    pausar();
    break;

  case '4':
    ListarConsultas(lista);
    break;

  case '5':
    break;

  default:
    printf("\nOpcao invalida.");
    pausar();
    break;
  }
}
