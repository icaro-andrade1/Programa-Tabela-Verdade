/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
											     	analisadorSintático.c
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "analisadorSintatico.h"


/* Estrutura de pilha utilizada para criar um autômato de pilha do analisador sintático*/
typedef struct Pilha
{	
    char elemento;
    struct Pilha *proximo;
}pilha;


/*-----------------------------------------------------------------------------------------------------------------------------------
													Protótipos das Funções Internas
-------------------------------------------------------------------------------------------------------------------------------------*/

void printPilha(pilha* topo);
void push(pilha** topo, char novoElemento);
char pop(pilha** topo);
void efetuaTransicao(int idTransicao, int* cabecaDeLeitura, pilha** topo);
void printFita(char* cadeia, int posicao);
int formulaBemFormada(char *formula);

/*-----------------------------------------------------------------------------------------------------------------------------------
															Funções
-------------------------------------------------------------------------------------------------------------------------------------*/
void printPilha(pilha* topo)
{

    while(topo != NULL)
	{
        printf("%c ", topo->elemento);    
        topo = topo->proximo;
    }
}

void push(pilha** topo, char novoElemento)
{

    pilha* novo = malloc(sizeof(pilha));    
    novo->proximo = *topo;
    novo->elemento = novoElemento; 
    *topo = novo;  
}

char pop(pilha** topo)
{

    char retorno;
    pilha* lixo;
    
    if(*topo == NULL)
	{
        retorno = '#';
    }
    else
	{
        retorno = (*topo)->elemento;
    
        lixo = *topo;
    
        *topo = (*topo)->proximo;
        
        free(lixo);
    }
    
    return retorno;
}

void efetuaTransicao(int idTransicao, int* cabecaDeLeitura, pilha** topo)
{
    
    switch(idTransicao)
	{
		case 0: push(topo, 'S');
				break;
				
		case 1: pop(topo);
				push(topo, 'T');
				break;
				
		case 2: pop(topo);
				push(topo, 'F');
				break;
				
		case 3: pop(topo);
				push(topo, 'p');
				break;
				
		case 4: pop(topo);
				push(topo, 'q');
				break;
				
		case 5: pop(topo);
				push(topo, 'r');
				break;
				
		case 6: pop(topo);
				push(topo, 's');
				break;
				
		case 7: pop(topo);
				push(topo, 't');
				break;
				
		case 8: pop(topo);
				push(topo, 'u');
				break;
				
		case 9: pop(topo);
				push(topo, 'v');
				break;
				
		case 10:pop(topo);
				push(topo, 'S');
				push(topo, '!');
				break;
				
		case 11:pop(topo);
				push(topo, ')');
				push(topo, 'S');
				push(topo, 'X');
				push(topo, 'S');
				push(topo, '(');
				break;
				
		case 12:pop(topo);
				push(topo, '&');
				break;
				
		case 13:pop(topo);
				push(topo, '|');
				break;
				
		case 14:pop(topo);
				push(topo, ':');
				break;
				
		case 15:pop(topo);
				push(topo, '-');
				break;
				
		case 16:(*cabecaDeLeitura)++;
				pop(topo);
				break;        
	}
}

void printFita(char* cadeia, int posicao)
{    
    int i = 0;
    
    while(cadeia[i] != '\0')
	{
        if(i == posicao)
		{
            printf(".");
        }
        printf("%c", cadeia[i]);        
        i++;
    }
} 

int formulaBemFormada(char *formula)
{

    pilha* topo = NULL;
    int cabecaDeLeitura = 0, flagTransitou = 0, i;
        
    efetuaTransicao(0, &cabecaDeLeitura, &topo);
    while(topo != NULL)
	{
        if(topo->elemento == formula[cabecaDeLeitura])
		{
			flagTransitou = 16;
			efetuaTransicao(16, &cabecaDeLeitura, &topo)
			;
		}else if(topo->elemento == 'S' && formula[cabecaDeLeitura] == '(')
		{
			flagTransitou = 11;
			efetuaTransicao(11, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'S' && formula[cabecaDeLeitura] == '!')
		{
			flagTransitou = 10;
			efetuaTransicao(10, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'S' && formula[cabecaDeLeitura] == 'v')
		{
			flagTransitou = 9;
			efetuaTransicao(9, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'S' && formula[cabecaDeLeitura] == 'u')
		{
			flagTransitou = 8;
			efetuaTransicao(8, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'S' && formula[cabecaDeLeitura] == 't')
		{
			flagTransitou = 7;
			efetuaTransicao(7, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'S' && formula[cabecaDeLeitura] == 's')
		{
			flagTransitou = 6;
			efetuaTransicao(6, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'S' && formula[cabecaDeLeitura] == 'r')
		{
			flagTransitou = 5;
			efetuaTransicao(5, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'S' && formula[cabecaDeLeitura] == 'q')
		{
			flagTransitou = 4;
			efetuaTransicao(4, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'S' && formula[cabecaDeLeitura] == 'p')
		{
			flagTransitou = 3;
			efetuaTransicao(3, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'S' && formula[cabecaDeLeitura] == 'F')
		{
			flagTransitou = 2;
			efetuaTransicao(2, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'S' && formula[cabecaDeLeitura] == 'T')
		{
			flagTransitou = 1;
			efetuaTransicao(1, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'X' && formula[cabecaDeLeitura] == '-')
		{
			flagTransitou = 15;
			efetuaTransicao(15, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'X' && formula[cabecaDeLeitura] == ':')
		{
			flagTransitou = 14;
			efetuaTransicao(14, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'X' && formula[cabecaDeLeitura] == '|')
		{
			flagTransitou = 13;
			efetuaTransicao(13, &cabecaDeLeitura, &topo);
		}else if(topo->elemento == 'X' && formula[cabecaDeLeitura] == '&'){
			flagTransitou = 12;
			efetuaTransicao(12, &cabecaDeLeitura, &topo);
		}

        if(flagTransitou == 0)
		{
            break;
        }
        else
		{
            flagTransitou = 0;
        }

	}
        
    if(topo == NULL && formula[cabecaDeLeitura] == '\0')
	{
        return 1;
    }
    else
	{
        printf("\nEntrada:::::::: %s", formula);
        printf("\nColuna de erro: ");
        for(i = 0; i < cabecaDeLeitura; i++)
		{
            printf(" ");
        }
        printf("*");
        printf("\nLook Ahead::::: %c", formula[cabecaDeLeitura]);
        if(topo == NULL)
		{
        printf("\nTopo da pilha:: \0");
        }
        else
		{
            printf("\nTopo da pilha:: %c", topo->elemento);
        }
        printf("\nPilha:::::::::: ");
        printPilha(topo);                                    
    }
    
    return 0;
}

