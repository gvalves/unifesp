#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <registration.h>

char *strupp(char *str)
{
  char *_strupp = malloc(strlen(str));

  for (int i = 0; i < strlen(str); i++)
  {
    _strupp[i] = toupper((unsigned char)str[i]);
  }

  return _strupp;
}