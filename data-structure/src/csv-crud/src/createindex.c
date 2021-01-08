#include <stdio.h>
#include <stdlib.h>
#include <registration.h>

void createIndex(char *dataFilename, char *indexFilename)
{
  FILE *dataFile, *indexFile;
  char line[MAXLINELEN], data[MAXDATALEN];

  dataFile = fopen(dataFilename, "r");
  indexFile = fopen(indexFilename, "wb");

  RegistrationIndex index;

  if (!dataFile || !indexFile)
  {
    printf("File not found!");
    return;
  }

  fseek(dataFile, 0, SEEK_END);
  int endpos = ftell(dataFile);

  fseek(dataFile, 0, SEEK_SET);
  fgets(line, sizeof(line), dataFile);

  index.pos = ftell(dataFile);

  for (unsigned long pos = ftell(dataFile); pos < endpos; pos = ftell(dataFile))
  {
    printf("%lu\n", pos);
    index.pos = pos;
    fgets(line, sizeof(line), dataFile);
  }
}