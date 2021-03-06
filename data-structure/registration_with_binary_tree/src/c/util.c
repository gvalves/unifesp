#include <string.h>
#include <ctype.h>
#include <util.h>

void str_upper(char *str)
{
  for (int i = 0; i < strlen(str); i++)
  {
    str[i] = toupper((unsigned char)str[i]);
  }
}
