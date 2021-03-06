#include <stdio.h>
#include <stdlib.h>
#include <exception.h>

void throw_exception(char *msg)
{
  printf("%s\n", msg);
  exit(EXIT_FAILURE);
}

void throw_null_exception(char *s_name)
{
  printf("Struct %s cannot be null.\n", s_name);
  exit(EXIT_FAILURE);
}