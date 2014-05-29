#ifndef ANALISADOR_SINTATICO_FBF_LOGICA_PROPOSICIONAL_H
#define ANALISADOR_SINTATICO_FBF_LOGICA_PROPOSICIONAL_H

#include<stdio.h>
#include<stdlib.h>

/*---------------------------------------------------------------------------------------------
Entrada: String compostas pela possível fórmula bem formada de acordo a linguagem 
		 equivalente a linguagem da lógica proposicional.
Saída: o valor inteiro 1 caso a fórmula esteja bem formada e 0 caso contrário.
Objetivo:	Função responsável por informar se a fórmula passada como parâmetro é 
			ou não bem formada de acordo a uma linguagem equivalente a linguagem da 
			lógica proposicional, cujas regras de produção da gramática podem ser 
			vista abaixo:
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
int formulaBemFormada(char *formula);
    
#endif
