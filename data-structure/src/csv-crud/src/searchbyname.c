#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <registration.h>

void searchByName(char *name)
{
  FILE *datafile = fopen(DATA, "r");
  FILE *idxfile = fopen(INDEX, "r");
  int regs_limit = 100;
  int regs_len = 100;
  int regs_qt = 0;
  char regs_found[regs_limit][regs_len];
  char *search = strupp(name);
  char *regs = malloc(sizeof(char) * regs_len);
  char data[MAXDATALEN];

  while (fgets(regs, regs_len, idxfile))
  {
    if (strstr(regs, search))
    {
      if (regs_qt < regs_limit)
      {
        strcpy(regs_found[regs_qt], regs);
      }
      regs_qt++;
    }
  }

  free(search);

  printf("\n%d registros encontrados!\n-\n", regs_qt);

  for (int i = 0; i < (regs_qt > regs_limit ? regs_limit : regs_qt); i++)
  {
    char *pregs_found = regs_found[i];
    fseek(datafile, strtol(strsep(&pregs_found, ";"), NULL, 10), 0);
    fgets(regs, MAXLINELEN, datafile);

    getData(regs, NOME, data);
    printf("Nome: %s\n", data);
    getData(regs, DESCRICAO_CARGO, data);
    printf("Cargo: %s\n", data);
    getData(regs, UORG_LOTACAO, data);
    printf("Uorg Lotação: %s\n\n", data);
  }
}