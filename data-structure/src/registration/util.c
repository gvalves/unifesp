/*
* Arquivo: util.c
* 
* Funções utilizadas pelo sistema de pesquisa de cadastro
* 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cadastro.h"

void extrai(char *lin, int elem, char *d)
{

  char linha[MAXLIN], *p, *q;
  int i = 0;

  strcpy(linha, lin);
  p = linha;

  while (*p != '\0')
  {
    if (elem - 1 == i)
    {
      if (*p == '"')
        p++;
      q = p;
      while (*q != '"')
        q++;
      *q = '\0';
      strcpy(d, p);
      return;
    }

    if (*p == ';')
    {
      i++;
    }
    p++;
  }
}
