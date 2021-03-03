#include <stdio.h>
#include <AVLTree3.h>

int main(int argc, char *argv[])
{
  Node *root = create_node(0, 0);

  for (size_t i = 1; i <= 1000000; i++)
  {
    insert_node(root, i, 0);
  }

  Node *node = find_node(root, 84);

  printf("key: %lu;pkey: %lu\n", node->key, get_right_most_node(node)->key);

  return 0;
}