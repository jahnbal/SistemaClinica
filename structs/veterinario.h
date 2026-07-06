/*
Cadastra/Exclui/Edita/Lista/Pesquisa

*/
#include <stdio.h>


typedef struct {

	int id;
	char nome[50];

} Veterinario;



void CadastrarVeterinario();

int ExcluirVeterinario(int id); 

int EditarVeterinario(int id);

int ListarVeterinarios(); 

int BuscarVeterinarioPorId(int id);