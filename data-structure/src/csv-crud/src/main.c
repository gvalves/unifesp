#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <registration.h>

int main()
{
  if (0)
  {
    createIndex(DATA, INDEX);
    return 0;
  }

  char name[50];

  printf("Entre com nome para busca: ");

  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = '\0';

  searchByName(name);

  return 0;
}