#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bst.h>
#include <util.h>
#include <registration.h>

char *extract_register_data(char *line, int data_type)
{
  char *data = malloc(MAX_DATA_LEN);
  char *linecpy = malloc(MAX_LINE_LEN);
  strcpy(linecpy, line);

  for (int i = 1; i <= data_type; i++)
  {
    if (data_type == i)
    {
      strcpy(data, strsep(&linecpy, "|"));
      return data;
    }
    strsep(&linecpy, "|");
  }
}

Stack *find_registers(char *name, BST *data)
{
  Stack *data_stack, *cur_register, *found_registers;

  data_stack = bst_to_stack(data);
  found_registers = create_stack(NULL);

  str_upper(name);

  do
  {
    cur_register = (Stack *)stack_pop(data_stack);
    if (strstr(stack_tail(cur_register)->value, name))
    {
      stack_push(found_registers, create_stack_node(cur_register));
    }
  } while (stack_head(data_stack));

  free(data_stack);

  return found_registers;
}