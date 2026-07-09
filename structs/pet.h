#pragma once
/*
Cadastra/Exclui/Edita/Lista/Pesquisa

*/

#define ARQUIVO_PETS "pets.dat"

typedef struct {

  char nome[30];
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
