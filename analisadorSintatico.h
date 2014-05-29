#ifndef ANALISADOR_SINTATICO_FBF_LOGICA_PROPOSICIONAL_H
#define ANALISADOR_SINTATICO_FBF_LOGICA_PROPOSICIONAL_H

#include<stdio.h>
#include<stdlib.h>

/*---------------------------------------------------------------------------------------------
Entrada: String compostas pela poss�vel f�rmula bem formada de acordo a linguagem 
		 equivalente a linguagem da l�gica proposicional.
Sa�da: o valor inteiro 1 caso a f�rmula esteja bem formada e 0 caso contr�rio.
Objetivo:	Fun��o respons�vel por informar se a f�rmula passada como par�metro � 
			ou n�o bem formada de acordo a uma linguagem equivalente a linguagem da 
			l�gica proposicional, cujas regras de produ��o da gram�tica podem ser 
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
