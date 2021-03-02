#include <stdlib.h>
#include <stdio.h>
#include <AVLTree3.h>

Node *insert_node(Node *node, unsigned long key, void *value)
{
  if (node == 0)
  {
    return 0;
  }
  Node *new_node, *cur_node;

  new_node = malloc(sizeof(Node));
  new_node->key = key;
  new_node->value = value;

  cur_node = node;

  while (1)
  {
    if (new_node->key < cur_node->key)
    {
      if (cur_node->left_child == 0)
      {
        cur_node->left_child = new_node;
        new_node->parent = cur_node;
        break;
      }
      cur_node = cur_node->left_child;
    }
    else
    {
      if (cur_node->right_child == 0)
      {
        cur_node->right_child = new_node;
        new_node->parent = cur_node;
        break;
      }
      cur_node = cur_node->right_child;
    }
  }

  return new_node;
}

Node *find_node(Node *node, unsigned long key)
{
  if (node == 0)
  {
    return 0;
  }

  Node *cur_node = node;

  while (key != cur_node->key)
  {
    if (key < cur_node->key)
    {
      if (cur_node->left_child == 0)
      {
        cur_node = 0;
        break;
      }
      cur_node = cur_node->left_child;
    }
    else
    {
      if (cur_node->right_child == 0)
      {
        cur_node = 0;
        break;
      }
      cur_node = cur_node->right_child;
    }
  }

  return cur_node;
}

void remove_node(Node *node, unsigned long key)
{
  if (node == 0)
  {
    return;
  }
  Node *cur_node = find_node(node, key);

  while (1)
  {
    if (cur_node->left_child == 0 && cur_node->right_child == 0)
    {
      if (cur_node->parent->left_child == cur_node)
      {
        cur_node->parent->left_child = 0;
      }
      else
      {
        cur_node->parent->right_child = 0;
      }
      break;
    }
    else if (cur_node->left_child == 0 ^ cur_node->right_child == 0)
    {
      if (cur_node->left_child == 0)
      {
        if (cur_node->parent->left_child == cur_node)
        {
          cur_node->parent->left_child = cur_node->right_child;
          cur_node->right_child->parent = cur_node->parent;
        }
        else
        {
          cur_node->parent->right_child = cur_node->right_child;
          cur_node->right_child->parent = cur_node->parent;
        }
      }
      else
      {
        if (cur_node->parent->left_child == cur_node)
        {
          cur_node->parent->left_child = cur_node->left_child;
          cur_node->left_child->parent = cur_node->parent;
        }
        else
        {
          cur_node->parent->right_child = cur_node->left_child;
          cur_node->left_child->parent = cur_node->parent;
        }
      }
      break;
    }
    else
    {
      Node *successor = left_most_node(cur_node);

      cur_node->key = successor->key;
      cur_node->value = successor->value;

      cur_node = successor;

      free(successor);
    }
  }

  free(cur_node);
}

Node *left_most_node(Node *node)
{
  if (node == 0)
  {
    return 0;
  }
  Node *cur_node = node;

  while (cur_node->left_child != 0)
  {
    cur_node = cur_node->left_child;
  }

  return cur_node;
}

Node *right_most_node(Node *node)
{
  if (node == 0)
  {
    return 0;
  }
  Node *cur_node = node;

  while (cur_node->right_child != 0)
  {
    cur_node = cur_node->right_child;
  }

  return cur_node;
}

int main(int argc, char *argv[])
{
  Node *root = malloc(sizeof(Node));

  for (size_t i = 0; i < 10000; i++)
  {
    insert_node(root, i, 0);
  }

  Node *node = find_node(root, 84);

  printf("key: %lu;pkey: %lu\n", node->key, right_most_node(node)->key);

  return 0;
}