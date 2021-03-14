#include <stdio.h>
#include <string.h>
#include <bst.h>
#include <stack.h>
#include <util.h>
#include <registration.h>

int main()
{
  FILE *data_stream = fopen("./data/cadastro2019.csv", "r");
  BST *data = create_bst(NULL);
  Stack *found_registers, *cur_register;
  char cur_line[MAX_LINE_LEN], name[MAX_DATA_LEN];
  int pos, qt_registers_to_show = 100;

  fgets(cur_line, sizeof(cur_line), data_stream);
  pos = ftell(data_stream);

  while (fgets(cur_line, sizeof(cur_line), data_stream))
  {
    bst_insert(data, create_bst_node(pos, extract_register_data(cur_line, NOME)));
    pos = ftell(data_stream);
  }

  printf("Digite um nome para busca: ");
  fgets(name, MAX_DATA_LEN, stdin);
  name[strcspn(name, "\r\n")] = '\0';

  found_registers = find_registers(name, data);

  printf("%lu registro encontrado!\n\n", stack_size(found_registers));

  for (size_t i = 0; i < stack_size(found_registers); i++)
  {
    cur_register = (Stack *)stack_pop(found_registers);

    fseek(data_stream, (long)stack_head(cur_register)->value, SEEK_SET);
    fgets(cur_line, MAX_LINE_LEN, data_stream);

    printf("Nome: %s\n", extract_register_data(cur_line, NOME));
    printf("Org Lotação: %s\n\n", extract_register_data(cur_line, ORG_LOTACAO));

    if (i >= qt_registers_to_show)
    {
      break;
    }
  }

  return 0;
}