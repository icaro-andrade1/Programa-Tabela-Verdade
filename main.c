/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				Programa que Calcula a Tabela de uma linguagem equivalente a linguagem da lógica proposicional
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdio.h>
#include <stdlib.h>
#include "tabelaVerdade.h"

/*---------------------------------------------------------------------------------------------
										Função main
---------------------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{	
	char *formula;
	formula = malloc(100*sizeof(char*));

	if(argc != 2)
	{
		printf("ERRO: faltou uma sentenca como parametro\nUso:\n\t\t%s <string>\nOnde:\n\t\t<string> e uma sentenca a ser analisada.", argv[0]);
		exit(1);
	}	
	
	strcpy(formula, argv[1]);
	criaTabelaVerdade(formula);
	
}
