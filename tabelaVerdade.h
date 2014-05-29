#ifndef CRIA_TABELA_VERDADE_H
#define CRIA_TABELA_VERDADE_H

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "analisadorSintatico.h"

#define QTD_MAX_LETRAS_EXISTENTES_FORMULA 20
#define TAM_ARVORE 10000

/*---------------------------------------------------------------------------------------------
Entrada: String compostas pela possível fórmula bem formada de acordo a linguagem 
		 equivalente a linguagem da lógica proposicional.
Saída: Exibi a tabela verdade se a fórmula estiver bem formada, informando a valor semântico;
Objetivo:	Função responsável por criar a tabela verdade referente a fórmula  bem formada de
			acordo a uma linguagem equivalente a linguagem da lógica proposicional, cujas 
			regras de produção da gramática podem ser vista abaixo:
				1.	S -> (SXS)
				2.	S -> !S
				3.	S -> p
				4.	S -> q
				5.	S -> r
				6.	S -> i
				7.	S -> T
				8.	S -> F
				9.	X -> |
				10.	X -> &
				11.	X -> -
				12.	X -> :
---------------------------------------------------------------------------------------------*/
void criaTabelaVerdade(char *formula);
    
#endif
