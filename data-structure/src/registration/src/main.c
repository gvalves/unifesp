#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <registration.h>

int main(int argc, char **argv)
{
  *argv++;
  for (int i = 1; i < argc; i++)
  {
    if (strcmp("--create-index", *argv) == 0)
    {
      createIndex(DATA, INDEX);
    }
    *argv++;
  }

  char name[50];

  printf("Entre com nome para busca: ");

  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = '\0';

  searchByName(name);

  return 0;
}