#pragma once

#include "pet.h"
#include "veterinario.h"

#define ARQUIVO_CONSULTAS "consultas.dat"

// Status da consulta
typedef enum { AGENDADA, EM_ATENDIMENTO, FINALIZADA, CANCELADA } StatusConsulta;

// Estrutura principal de uma consulta
typedef struct {
  int id;                  //  Id de cada consulta gerado em sequência
  Pet animal;              // pet em atendimento
  Veterinario veterinario; // veterinário responsável
  float valor;             // valor cobrado pela consulta
  char data[11];           // formato DD/MM/AAAA
  int horario;             // hora inteira, ex: 9 = 09h00, 14 = 14h00
  StatusConsulta status;   // estado atual da consulta
} Consulta;

// Nó da lista encadeada

typedef struct NoConsulta {
  Consulta dados;
  struct NoConsulta *proximo;
} NoConsulta;

// Cabeça da lista encadeada
typedef struct {
  NoConsulta *inicio;
  int tamanho;
} ListaConsulta;


void PedeDadosParaBusca(Consulta *consulta);
void PreencheDadosConsulta(Consulta *consulta);
void InicializarLista(ListaConsulta **lista);
int VerificarConflito(ListaConsulta *lista, Consulta consulta);
int InserirConsulta(ListaConsulta *lista, Consulta consulta);
int RemoverConsulta(ListaConsulta *lista, Consulta consulta);
Consulta *BuscarConsulta(ListaConsulta *lista, Consulta consulta);
void ListarConsultas(ListaConsulta *lista);
void SalvarLista(ListaConsulta *lista);
void CarregarLista(ListaConsulta* lista);