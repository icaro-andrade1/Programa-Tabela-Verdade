#include "tabelaVerdade.h"

int montandoArvoreAux(char *arvore, char *formula, int raiz, int posF)
{
	int pos;
	pos = raiz*5+1;

	if(formula[posF]=='\0')
		return posF;
	
	if(formula[posF]=='(')
	{
		arvore[pos] = '(';
		arvore[pos+1] = 'S';
		arvore[pos+2] = 'X';
		arvore[pos+3] = 'S';
		arvore[pos+4] = ')';
		
		posF = montandoArvoreAux(arvore, formula, pos+1, posF+1);
			
		if(formula[posF]==')')
			posF++;
		arvore[(pos+2)*5+1] = formula[posF];
		
		posF = montandoArvoreAux(arvore, formula, pos+3, posF+1);

		return posF+1;
	}	
	else if((formula[posF]>='a'&&formula[posF]<='z')||(formula[posF]=='T')||(formula[posF]=='F'))
	{
		arvore[pos] = formula[posF];
		return posF+1;
	}
	else if(formula[posF]=='!')
	{	
		arvore[pos] = '!';
		arvore[pos+1] = 'S';
		posF = montandoArvoreAux(arvore, formula, pos+1, posF+1);
		return posF;
	}
	else if(formula[posF]==')')
		return posF+1;
		
}


void montandoArvore(char *arvore, char *formula)
{
	int y;
 
	montandoArvoreAux(arvore, formula, 0, 0);

}

char operacao(char op, char v1, char v2)
{
	if(op=='&')//Tabela e
	{
		if(v1=='T'&&v2=='T')
		{
			return 'T';
		}
		else 
		{
			return 'F';
		}
	}

	if(op=='|')//Tabela ou
	{
		if(v1=='F'&&v2=='F')
		{
			return 'F';
		}
		else 
		{
			return 'T';
		}
	}

	if(op=='-')//Tabela implicação
	{
		if(v1=='T'&&v2=='F')
		{
			return 'F';
		}
		else 
		{
			return 'T';
		}
	}

	if(op==':')//Tabela bimplicação
	{
		if((v1=='T'&&v2=='T')||(v1=='F'&&v2=='F'))
		{
			return 'T';
		}
		else 
		{
			return 'F';
		}
	}

}

//Retorna o indice do valor na tabela
int indiceTabela(char **tabVerdade, int c, char valor)
{
	int cont;
	
	for(cont=0;cont<c;cont++)
	{
		if(tabVerdade[0][cont]==valor)
			return cont;
	}
	return -1;
}

char criandoColunaTabela(char **tabVerdade, int *c, int l, char op, char v1, char v2)
{
	int cont;
	static char nomeCol=51;
	int i1, i2;
	char indice;

	indice = nomeCol;
	tabVerdade[0][(*c)]=nomeCol;

	
	if(op=='!')
	{

		printf("\n\tOperacao %c: %c %c", nomeCol, op, v1);

		if(v1=='T')
		{
			for(cont=1;cont<l;cont++)
			{		
				tabVerdade[cont][(*c)]='F';		
			}
		}
		else if(v1=='F')
		{
			for(cont=1;cont<l;cont++)
			{		
				tabVerdade[cont][(*c)]='T';		
			}
		}	
		else
		{
			i1 = indiceTabela(tabVerdade, *c, v1);
			for(cont=1;cont<l;cont++)
			{		
				if(tabVerdade[cont][i1]=='T')
				{
					tabVerdade[cont][(*c)]='F';
				}
				else
				{
					tabVerdade[cont][(*c)]= 'T';
				}
			}
		}
	}
	else
	{	
		printf("\n\tOperacao %c: %c %c %c", nomeCol, v1, op, v2);
		
		if((v1=='T'||v1=='F')&&(v2=='T'||v2=='F'))
		{
			for(cont=1;cont<l;cont++)
			{		
				tabVerdade[cont][(*c)]=operacao(op, v1, v2);
			}
		}
		else if(v1=='T'||v1=='F')
		{
			i2 = indiceTabela(tabVerdade, *c, v2);
			for(cont=1;cont<l;cont++)
			{		
				tabVerdade[cont][(*c)]=operacao(op, v1, tabVerdade[cont][i2]);
			}
		}
		else if(v2=='T'||v2=='F')
		{
			i1 = indiceTabela(tabVerdade, *c, v1);
			for(cont=1;cont<l;cont++)
			{		
				tabVerdade[cont][(*c)]=operacao(op, tabVerdade[cont][i1], v2);
			}
		}
		else
		{
			i1 = indiceTabela(tabVerdade, *c, v1);
			i2 = indiceTabela(tabVerdade, *c, v2);
		
		
			for(cont=1;cont<l;cont++)
			{		
				tabVerdade[cont][(*c)]=operacao(op, tabVerdade[cont][i1], tabVerdade[cont][i2]);
			}
		}
	}
	nomeCol++;
	(*c)++;
	return indice;
}

char criaTabelaVerdadeAux(char **tabelaVerdade,int  *c,int l, char *arvore,int pos)
{
	char indice1, indice2, op;
	int posAux;

	if(arvore[pos]=='('||arvore[pos]==')'||arvore[pos]==' ')
	{
		return criaTabelaVerdadeAux(tabelaVerdade, c, l, arvore,pos+1);
	}
	else if(arvore[pos]=='S')
	{
		posAux = pos*5+1;
		indice1 = criaTabelaVerdadeAux(tabelaVerdade, c, l, arvore,posAux);
		pos++;
		op = arvore[pos*5+1];
		posAux = (pos +1)*5+1;
		indice2 = criaTabelaVerdadeAux(tabelaVerdade, c, l, arvore,posAux);
		
		//agora cria a coluna na tabela...
		indice2 = criandoColunaTabela(tabelaVerdade, c, l, op, indice1, indice2);
		
		return indice2;

	}
	else if(arvore[pos]=='p'||arvore[pos]=='q')
	{
		return arvore[pos];
		
	}
	else if(arvore[pos]=='&'||arvore[pos]==':'||arvore[pos]=='-'||arvore[pos]=='|')
	{
		pos++;
		return arvore[pos];
	}
	else if(arvore[pos]=='!')
	{	
		posAux = (pos +1)*5+1;
		indice1 = criaTabelaVerdadeAux(tabelaVerdade, c, l, arvore, posAux);
		return criandoColunaTabela(tabelaVerdade, c, l, '!', indice1, indice2);
	}

}


void valorVerdadeSentenca(char **tabVerdade, int c, int l)
{
	int cont;
	int falsos=0;

		printf("\n");

	for(cont=0;cont<l;cont++)	
	{
		if(tabVerdade[cont][c-1]=='F')
		{
			falsos++;
		}
	}

	if(falsos==(l-1))
	{
		printf("\n\tA sentenca e uma Contradicao!");
	}
	else if(falsos==0)
	{
		printf("\n\tA sentenca e uma Tautologia!");
	}
	else
	{
		printf("\n\tA sentenca e uma Contingencia!");	
	}

	printf("\n\n");
}

int contemLetraNoVetor(char letras[],int qtdLetras, char letra)
{
	int cont;
	
	for(cont=0;cont<qtdLetras;cont++)
	{
		if(letras[cont]==letra)
		{
			return 1;
		}
	}

	return 0;
}

char **instanciandoTabelaVerdade(char **tabelaVerdade, int *c, int *l, char *formula)
{
	int cont;
	char letras[QTD_MAX_LETRAS_EXISTENTES_FORMULA];	
	int qtdLetras=0;
	int tamTabVerdade=1;
	int i,j;
	int oxilacao;
	int flag;

	for(cont=0;formula[cont]!='\0';cont++)
	{
		if((formula[cont]>='a'&&formula[cont]<='z'))
		{
			if(contemLetraNoVetor(letras, qtdLetras, formula[cont])==0)
			{
				letras[qtdLetras++] = formula[cont];
			}
		}
	}


	for(cont=0;cont<qtdLetras;cont++)
	{
		tamTabVerdade *=2;
	}
	tamTabVerdade++; // mais um devido ao cabeçalho

	//após obter o tamanho da tabela instancia
	tabelaVerdade = (char**) malloc(tamTabVerdade*sizeof(char*));
	for(cont=0;cont<tamTabVerdade;cont++)
	{
		tabelaVerdade[cont] = malloc(20*sizeof(char*));
	}

	(*c) = qtdLetras;
	(*l) = tamTabVerdade;
	
	//então preenche o cabeçalho da tabela com as letras

	for(j=0;j<*c;j++)
	{
		tabelaVerdade[0][j]=letras[j];
	}
	
	//e por fim preenche a linhas com os valores verdade
	oxilacao = tamTabVerdade-1;
	for(i=0;i<*c;i++)
	{
		flag=1;
		cont=1;		
		oxilacao /=2;

		for(j=1;j<*l;j++)
		{
			if(cont>oxilacao)
			{
				cont=1;
				flag *= -1;
			}
			
			if(j==0)
			{
				tabelaVerdade[j][i]=letras[i];
			}
			else
			{
				if(flag==1)
				{
					tabelaVerdade[j][i]='T';
				}
				else
				{
					tabelaVerdade[j][i]='F';
				}
			}
			cont++;
		}

	}

	return tabelaVerdade;
	
}

void criaTabelaVerdade(char *formula)
{
	char **tabelaVerdade;	
	int c;	
	int l;
	int pos=1;
	int cont;
	char *arvore;
	int i,j;

	if(formulaBemFormada(formula)==0)
	{
		exit(1);
	}
	
	tabelaVerdade = instanciandoTabelaVerdade(tabelaVerdade, &c, &l, formula);

	arvore = malloc(TAM_ARVORE*sizeof(char*));

	montandoArvore(arvore, formula);
	criaTabelaVerdadeAux(tabelaVerdade, &c,l, arvore, pos);


	printf("\n\n\t\tTabela Verdade\n");
	for(i=0;i<l;i++)
	{
		printf("\n\t");
		for(j=0;j<c;j++)
		{	
			printf(" %c ", tabelaVerdade[i][j]);
		}
		if(i==0)
		{
			
			printf("\n\t");
			for(j=0;j<c;j++)
			{
				printf("---");
			}
		}
		

	}

	valorVerdadeSentenca(tabelaVerdade, c, l);
	printf("\n");
	
}

