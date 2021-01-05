/*
* Programa: cad.c
* 
* Lê arquivo CSV baixado do transparencia.gov com dados de servidores públicos
*  
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "cadastro.h"

int main()
{
  char nome[MAXSTR];
  char *p;

  printf("\nEntre com o nome: ");
  fgets(nome, MAXSTR, stdin);

  for (p = nome; *p != '\n' && *p != '\0'; p++)
    ;
  *p = '\0';

  busca(nome);
}

int busca(char *nome)
{
  FILE *dados, *indice;
  IndiceCadastro registro;
  char nomebusca[MAXSTR], *p;
  char linha[MAXLIN];
  char dado[MAXSTR];

  IndiceCadastro *encontrados;
  IndiceCadastro *espacoExtra;

  int conta = 0;
  int limite = 100;

  encontrados = malloc(limite * sizeof(IndiceCadastro));

  p = nomebusca;
  strcpy(nomebusca, nome);
  while (*p != '\0')
  {
    *p = toupper(*p);
    p++;
  }

  indice = fopen(INDICE, "r");

  while (1)
  {
    fread(&registro, sizeof(registro), 1, indice);
    if (feof(indice))
      break;

    if (strstr(registro.nome, nomebusca))
    {
      strcpy(encontrados[conta].nome, registro.nome);
      encontrados[conta].localiza = registro.localiza;
      conta++;
      if (conta >= limite)
      {
        limite = conta + 100;
        espacoExtra = malloc(limite * sizeof(IndiceCadastro));
        memcpy(espacoExtra, encontrados, conta * sizeof(IndiceCadastro));
        free(encontrados);
        encontrados = espacoExtra;
      }
    }
  }

  //for( int i=0; i<conta; i++)
  //	printf("Nome: %s\n",encontrados[i].nome);

  printf("\n%d registros encontrados!\n", conta);

  fclose(indice);
  dados = fopen(DADOS, "r");

  for (int i = 0; i < conta; i++)
  {
    fseek(dados, encontrados[i].localiza, 0);
    fgets(linha, MAXLIN, dados);

    printf("Nome: %s\n", encontrados[i].nome);
    extrai(linha, DESCRICAO_CARGO, dado);
    printf("Cargo: %s\n", dado);
    extrai(linha, UORG_LOTACAO, dado);
    printf("UORG Lotação: %s\n", dado);
  }

  //	printf("\n%d registro(s) encontrado(s)!\nNome: %s - %ul \n", conta, registro.nome, registro.localiza );

  return conta;
}

/*

int lixo() {


	FILE *fp;
	
	char linha[MAXLIN];
	char dado[MAXLIN], d2[MAXLIN], d3[MAXLIN];
	char nome[MAXLIN];
	char *ptr;
	
	fp = fopen("/data/datasets/ed2020/cad2020.csv", "r");
	
	if( ! fp ) {
		printf("\nErro de abertura de arquivo\n\n");
		return -1;
		}
		
	printf("\nNome para busca: ");
	fgets( nome, MAXLIN, stdin);
	ptr = nome;
	while( *ptr!='\0' &&  *ptr!='\n') {
		ptr++;
		}
	*ptr = '\0';
	printf("Nome: %s\n", nome);
		
	while( fgets( linha, MAXLIN, fp ) ) {
		extrai( linha, 1, dado );
		if( ! strcmp( dado, nome) ) {
			extrai( linha, 4, d2 );	
			extrai( linha, 16, d3 );
			printf("\n%s \n%s\n%s\n", dado, d2,d3);
			}
	}
	
}

*/
