/*
* Programa: criaind.c
* 
* Lê arquivo CSV baixado do transparencia.gov com dados de servidores públicos e cria arquivo de índice
* 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cadastro.h"

int main()
{

  criaIndice(DADOS, INDICE);
}

void criaIndice(char *nomearq, char *nomeind)
{
  FILE *entra, *sai;
  char linha[MAXLIN];
  char dado[MAXSTR];
  IndiceCadastro cad;

  entra = fopen(nomearq, "r");
  sai = fopen(nomeind, "wb");

  if (!entra || !sai)
  {
    printf("\nErro de abertura de arquivo\n\n");
    return;
  }
  fgets(linha, MAXLIN, entra);
  cad.localiza = ftell(entra);

  while (fgets(linha, MAXLIN, entra))
  {
    extrai(linha, NOME, dado);
    strcpy(cad.nome, dado);
    fwrite(&cad, sizeof(cad), 1, sai);

    cad.localiza = ftell(entra);
  }
}
