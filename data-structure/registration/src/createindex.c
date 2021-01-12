#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <registration.h>

void createIndex(char *data_filename, char *idx_filename)
{
  FILE *datafile, *idxfile;
  char line[MAXLINELEN], data[MAXDATALEN];

  char test[MAXLINELEN];

  datafile = fopen(data_filename, "r");
  idxfile = fopen(idx_filename, "w");

  RegistrationIndex index;

  if (!datafile || !idxfile)
  {
    printf("File not found!\n");
    return;
  }

  fgets(line, sizeof(line), datafile);
  long pos = ftell(datafile);

  while (fgets(line, sizeof(line), datafile))
  {
    getData(line, NOME, data);
    strcpy(index.name, data);

    index.pos = pos;
    pos = ftell(datafile);

    char *name = index.name;

    strsep(&name, "\"");

    fprintf(idxfile, "%lu;%s\n", index.pos, strsep(&name, "\""));
  }
}