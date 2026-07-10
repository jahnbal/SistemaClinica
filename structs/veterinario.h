#pragma once

#include <stdio.h>

// Cadastra/Exclui/Edita/Lista/Pesquisa

typedef struct {

  int id;
  char nome[50];

} Veterinario;

void CadastrarVeterinario();

int VerificaIdIgualVeterinario(int id);

int ExcluirVeterinario(int id);

int EditarVeterinario(int id);

int ListarVeterinarios();

int BuscarVeterinarioPorId(int id);

int VerificaIdIgualVeterinario(int id);
