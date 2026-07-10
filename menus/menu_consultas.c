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

  // Inicializa a lista uma única vez e carrega os dados do arquivo binário
  if (!lista) {
    InicializarLista(&lista);
    CarregarLista(lista);
  }

  Consulta *consulta = malloc(sizeof(Consulta));
  if (!consulta) {
    printf("Erro ao alocar memoria.\n");
    pausar();
    return;
  }

  Consulta *buscada;
  int removida;
  int conflito = -1;

  switch (opcao) {

  case '1':
    PreencheDadosConsulta(consulta);

    // PreencheDadosConsulta sinaliza falha com id == -1
    // quando Pet ou Veterinário não são encontrados
    if (consulta->id == -1) {
      pausar();
      break;
    }

    conflito = VerificarConflito(lista, *consulta);
    if (conflito == 0) {
      InserirConsulta(lista, *consulta);
      SalvarLista(lista);
      printf("Consulta agendada com sucesso!\n");
    } else {
      printf("Erro: ja existe uma consulta para esse veterinario nessa data e horario.\n");
    }
    pausar();
    break;

  case '2':
    PedeDadosParaBusca(consulta);
    buscada = BuscarConsulta(lista, *consulta);

    if (buscada) {
      buscada->status |= STATUS_FINALIZADA;
      SalvarLista(lista);
      printf("Consulta marcada como finalizada!\n");
    } else {
      printf("Consulta nao encontrada.\n");
    }
    pausar();
    break;

  case '3':
    PedeDadosParaBusca(consulta);
    buscada = BuscarConsulta(lista, *consulta);

    if (buscada) {
      removida = RemoverConsulta(lista, *consulta);
      if (removida == 1) {
        SalvarLista(lista);
        printf("Consulta cancelada com sucesso!\n");
      }
    } else {
      printf("Consulta nao encontrada.\n");
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

  free(consulta);
}