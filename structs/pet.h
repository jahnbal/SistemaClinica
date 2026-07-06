/*
Cadastra/Exclui/Edita/Lista/Pesquisa

*/

typedef struct {

  char nome[30];
  int id;
  int idade;
  float peso;
  int id_Cliente; // relação de ownership com o cliente

} Pet;

void CadastrarPet();

int ExcluirPet(int id);

int EditarPet(int id);

int ListarPets();

int BuscarPetPorId(int id);
