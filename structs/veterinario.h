/*
Cadastra/Exclui/Edita/Lista/Pesquisa

*/
#include <stdio.h>


typedef struct {

	int id;
	char nome[50];

} Veterinario;



void CadastrarVeterinario()
{
    Veterinario v;
    preencherVeterinario(&v);
    salvarVeterinario(&v);
}

int ExcluirVeterinario(int id); 

int EditarVeterinario(int id);

int ListarTodosVeterinarios(); 

int BuscarVeterinarioPorId(int id);