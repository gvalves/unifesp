#include <stdlib.h>
#include <stdio.h>
#include <AVLTree3.h>

Node *append_node(Node *node, Node *child_node);
Node *get_unbalanced_node(Node *node);
void node_left_rotation(Node *node);
void node_right_rotation(Node *node);

Node *create_node(unsigned long key, void *value)
{
  Node *new_node;

  new_node = malloc(sizeof(Node));
  new_node->key = key;
  new_node->value = value;
  new_node->height = 0;

  return new_node;
}

Node *append_node(Node *node, Node *child_node)
{
  if (node == 0 || child_node == 0)
  {
    return 0;
  }
  Node *cur_node = node;

  while (1)
  {
    cur_node->height += 1;
    if (child_node->key < cur_node->key)
    {
      if (cur_node->left_child == 0)
      {
        cur_node->left_child = child_node;
        child_node->parent = cur_node;
        break;
      }
      cur_node = cur_node->left_child;
    }
    else
    {
      if (cur_node->right_child == 0)
      {
        cur_node->right_child = child_node;
        child_node->parent = cur_node;
        break;
      }
      cur_node = cur_node->right_child;
    }
  }

  return child_node;
}

Node *insert_node(Node *node, unsigned long key, void *value)
{
  if (node == 0)
  {
    return 0;
  }
  Node *new_node, *root_node;

  new_node = create_node(key, value);
  root_node = get_root_node(node);

  append_node(node, new_node);

  if (!(abs(get_node_balance(root_node)) <= 1))
  {
    Node *unbalanced_node = get_unbalanced_node(new_node->parent);

    if (get_node_balance(unbalanced_node) < 0)
    {

      if (unbalanced_node->right_child == 0)
      {
        node_right_rotation(unbalanced_node);
      }
      else
      {
        node_left_rotation(unbalanced_node->right_child);
        node_right_rotation(unbalanced_node);
      }
    }
    else
    {
      if (unbalanced_node->left_child == 0)
      {
        node_left_rotation(unbalanced_node);
      }
      else
      {
        node_right_rotation(unbalanced_node->left_child);
        node_left_rotation(unbalanced_node);
      }
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
  Node *cur_node, *ancestor;
  cur_node = find_node(node, key);

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

      ancestor = cur_node->parent;

      while (ancestor != 0)
      {
        ancestor->height -= 1;
        ancestor = ancestor->parent;
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

      ancestor = cur_node->parent;

      while (ancestor != 0)
      {
        ancestor->height -= 1;
        ancestor = ancestor->parent;
      }

      break;
    }
    else
    {
      Node *successor = get_left_most_node(cur_node);

      cur_node->key = successor->key;
      cur_node->value = successor->value;

      cur_node = successor;

      free(successor);
    }
  }

  free(cur_node);
}

Node *get_left_most_node(Node *node)
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

Node *get_right_most_node(Node *node)
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

Node *get_root_node(Node *node)
{
  if (node == 0)
  {
    return 0;
  }
  Node *root_node = node;

  while (root_node->parent != 0)
  {
    root_node = root_node->parent;
  }

  return root_node;
}

int get_node_balance(Node *node)
{
  if (node == 0)
  {
    return 0;
  }
  int l_height, r_height;

  l_height = node->left_child != 0 ? node->left_child->height : -1;
  r_height = node->right_child != 0 ? node->right_child->height : -1;

  return l_height - r_height;
}

Node *get_unbalanced_node(Node *node)
{
  if (node == 0)
  {
    return 0;
  }
  Node *cur_node = node;

  while (abs(get_node_balance(cur_node)) <= 1)
  {
    cur_node = cur_node->parent;
    if (cur_node == 0)
    {
      break;
    }
  }

  return cur_node;
}

void node_left_rotation(Node *node)
{
  if (node == 0 || node->right_child == 0)
  {
    return;
  }
  Node *child_node, *parent_node;
  child_node = node->right_child;
  parent_node = node->parent;

  if (child_node->left_child != 0)
  {
    append_node(node, child_node->left_child);
  }
  child_node->left_child = node;
  child_node->parent = parent_node;

  node->parent = child_node;

  if (parent_node->left_child == node)
  {
    parent_node->left_child = child_node;
  }
  else
  {
    parent_node->right_child = child_node;
  }

  if (child_node->height == 0)
  {
    child_node->height += 1;
  }
  node->height += node->height == 1 ? -1 : -2;
}

void node_right_rotation(Node *node)
{
  if (node == 0 || node->left_child == 0)
  {
    return;
  }
  Node *child_node, *parent_node;
  child_node = node->left_child;
  parent_node = node->parent;

  if (child_node->right_child != 0)
  {
    append_node(node, child_node->right_child);
  }
  child_node->right_child = node;
  child_node->parent = parent_node;

  node->parent = child_node;

  if (parent_node->left_child == node)
  {
    parent_node->left_child = child_node;
  }
  else
  {
    parent_node->right_child = child_node;
  }

  if (child_node->height == 0)
  {
    child_node->height += 1;
  }
  node->height += node->height == 1 ? -1 : -2;
}