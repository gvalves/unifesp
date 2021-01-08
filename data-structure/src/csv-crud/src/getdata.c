#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <registration.h>

void getData(char *line, int dataIndex, char *data)
{
  char *linecpy = malloc(MAXLINELEN);
  strcpy(linecpy, line);

  for (int i = 1; i <= dataIndex; i++)
  {
    char *getted = strsep(&linecpy, ";");

    if (dataIndex == i)
    {
      strcpy(data, getted);
      return;
    }
  }
}