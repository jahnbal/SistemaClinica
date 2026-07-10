#pragma once

#define ARQUIVO_PETS "pets.dat"
#define TAM_NOME_PET 30

// Cadastra/Exclui/Edita/Lista/Pesquisa

typedef struct {
  char nome[TAM_NOME_PET];
  int id;
  int idade;
  float peso;
  int id_Cliente; // relação de ownership com o cliente
} Pet;

void CadastrarPet();

int VerificaIdIgualPet(int id);

int ExcluirPet(int id);

int EditarPet(int id);

int ListarPets();

int BuscarPetPorId(int id);
