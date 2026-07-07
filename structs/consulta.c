#include "consulta.h"
#include "pet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Consulta *MarcarConsulta(Consulta *nova) {

  printf("Dados para o Agendamento:\n");

  printf("Nome do animal: ");
  scanf("%s", nova->animal.nome);

  printf("\n valor: ");
  scanf("%f", &nova->valor);

  printf("\nData: ");
  scanf("%s", nova->data);

  printf("\nHorario: ");
  scanf("%d", &(nova->horario));

  printf("Consulta marcada com sucesso!\n");
  return nova;
}

void InicializarLista(ListaConsulta *lista) {
  lista->inicio = NULL;
  lista->tamanho = 0;
}

int InserirConsulta(ListaConsulta *lista, Consulta consulta) {

  NoConsulta *novo = (NoConsulta *)malloc(sizeof(NoConsulta));
  if (novo == NULL) {
    printf("Erro ao alocar memoria para o novo no.\n");
    return 0;
  }

  novo->dados = consulta;
  novo->proximo = lista->inicio;
  lista->inicio = novo;
  lista->tamanho++;

  return 1;
}

int RemoverConsulta(ListaConsulta *lista, Consulta consulta) {
  NoConsulta *atual = lista->inicio;
  NoConsulta *anterior = NULL;

  while (atual != NULL) {
    int mesmaData = (strcmp(atual->dados.data, consulta.data) == 0);
    int mesmoHorario = (atual->dados.horario == consulta.horario);

    /* Mesmo criterio usado em VerificarConflito; ajuste o campo
       de identificacao do veterinario se necessario */
    int mesmoVeterinario =
        (atual->dados.veterinario.id == consulta.veterinario.id);

    if (mesmaData && mesmoHorario && mesmoVeterinario) {
      if (anterior == NULL) {
        lista->inicio = atual->proximo;
      } else {
        anterior->proximo = atual->proximo;
      }

      free(atual);
      lista->tamanho--;
      return 1;
    }

    anterior = atual;
    atual = atual->proximo;
  }

  printf("Consulta nao encontrada.\n");
  return 0;
}
int VerificarConflito(ListaConsulta *lista, Consulta consulta) {
  NoConsulta *atual = lista->inicio;

  while (atual != NULL) {
    int mesmaData = (strcmp(atual->dados.data, consulta.data) == 0);
    int mesmoHorario = (atual->dados.horario == consulta.horario);

    /* Ajuste esta comparacao para o campo que identifica o veterinario
       na sua struct Funcionario, ex: .id, .cpf, .nome, etc. */
    int mesmoVeterinario =
        (atual->dados.veterinario.id == consulta.veterinario.id);

    if (mesmaData && mesmoHorario && mesmoVeterinario) {
      return 1; /* conflito encontrado */
    }

    atual = atual->proximo;
  }

  return 0;
}

Consulta *BuscarConsulta(ListaConsulta *lista, Consulta consulta) {
  NoConsulta *atual = lista->inicio;

  while (atual != NULL) {
    int mesmaData = (strcmp(atual->dados.data, consulta.data) == 0);
    int mesmoHorario = (atual->dados.horario == consulta.horario);

    /* Mesmo criterio usado em VerificarConflito e RemoverConsulta */
    int mesmoVeterinario =
        (atual->dados.veterinario.id == consulta.veterinario.id);

    if (mesmaData && mesmoHorario && mesmoVeterinario) {
      return &(atual->dados);
    }

    atual = atual->proximo;
  }

  return NULL; /* nao encontrada */
}

void LiberarLista(ListaConsulta *lista) {
  NoConsulta *atual = lista->inicio;
  NoConsulta *proximo;

  while (atual != NULL) {
    proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }

  lista->inicio = NULL;
  lista->tamanho = 0;
}
