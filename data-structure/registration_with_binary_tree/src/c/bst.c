#include <stdlib.h>
#include <stdbool.h>
#include <exception.h>
#include <stack.h>
#include <bst.h>

static void throw_null_bst_exception();
static void throw_null_bst_node_exception();

static void append_node(BSTNode *parent_node, BSTNode *child_node);
static BSTNode *get_unbalanced_node(BSTNode *node);
static BSTNode *get_left_most_node(BSTNode *node);
static BSTNode *get_right_most_node(BSTNode *node);
static BSTNode *get_deepthest_node(BSTNode *node);
static int get_node_height(BSTNode *node);
static int get_node_balance(BSTNode *node);
static int get_node_children_quantity(BSTNode *node);
static bool is_balanced_node(BSTNode *node);
static bool is_left_heavy_node(BSTNode *node);
static bool is_right_heavy_node(BSTNode *node);
static void update_node_height(BSTNode *node);
static void balance_node(BST *bst, BSTNode *node);
static void left_rotate_node(BST *bst, BSTNode *node);
static void right_rotate_node(BST *bst, BSTNode *node);

static void throw_null_bst_exception()
{
  throw_null_exception("BST");
}

static void throw_null_bst_node_exception()
{
  throw_null_exception("BSTNode");
}

BST *create_bst(BSTNode *root)
{
  BST *new_bst = malloc(sizeof(BST));
  new_bst->_root = root;

  if (root)
  {
    new_bst->_size = 1;
  }
  return new_bst;
}

BSTNode *create_bst_node(u_long key, void *value)
{
  BSTNode *new_node = malloc(sizeof(BSTNode));
  new_node->_key = key;
  new_node->value = value;
  return new_node;
}

BSTNode *bst_find(BST *bst, u_long key)
{
  if (!bst)
  {
    throw_null_bst_exception();
  }
  BSTNode *cur_node = bst->_root;

  while (key != cur_node->_key)
  {
    if (key < cur_node->_key)
    {
      cur_node = cur_node->_left_child;
      continue;
    }
    cur_node = cur_node->_right_child;
  }
  return cur_node;
}

void bst_insert(BST *bst, BSTNode *node)
{
  if (!bst)
  {
    throw_null_bst_exception();
  }
  else if (!node)
  {
    throw_null_bst_node_exception();
  }
  ++bst->_size;

  if (!bst->_root)
  {
    bst->_root = node;
    return;
  }
  BSTNode *deepthest_node = node;
  append_node(bst->_root, node);

  while (!is_balanced_node(bst->_root))
  {
    balance_node(bst, deepthest_node);
    deepthest_node = get_deepthest_node(deepthest_node);
  }
}

void bst_delete(BST *bst, u_long key)
{
  if (!bst)
  {
    throw_null_bst_exception();
  }
  --bst->_size;

  BSTNode *cur_node, *deepthest_node;
  cur_node = bst_find(bst, key);
  deepthest_node = cur_node->_parent;
  int children_qt;

  while (1)
  {
    children_qt = get_node_children_quantity(cur_node);

    if (children_qt == 0)
    {
      break;
    }
    else if (children_qt == 1)
    {
      BSTNode *child_node = cur_node->_left_child ? cur_node->_left_child : cur_node->_right_child;
      if (child_node->_key < cur_node->_parent->_key)
      {
        cur_node->_parent->_left_child = child_node;
        child_node->_parent = cur_node->_parent;
      }
      else
      {
        cur_node->_parent->_right_child = child_node;
        child_node->_parent = cur_node->_parent;
      }
      break;
    }
    BSTNode *successor = get_left_most_node(cur_node);

    cur_node->_key = successor->_key;
    cur_node->value = successor->value;

    cur_node = successor;
  }

  update_node_height(cur_node->_parent);

  while (!is_balanced_node(bst->_root))
  {
    balance_node(bst, deepthest_node);
    deepthest_node = get_deepthest_node(deepthest_node);
  }

  free(cur_node);
}

Stack *bst_to_stack(BST *bst)
{
  if (!bst)
  {
    throw_null_bst_exception();
  }
  if (!bst->_root)
  {
    throw_exception("Cannot convert empty bst to array.");
  }
  Stack *cur_node_info, *node_stack;
  BSTNode *cur_node, *prev_node;
  size_t cur_stack_length = 0;

  node_stack = create_stack(NULL);
  cur_node = bst->_root;

  while (cur_node)
  {
    cur_node_info = create_stack(create_stack_node((void *)cur_node->_key));
    stack_push(cur_node_info, create_stack_node((void *)cur_node->value));
    stack_push(node_stack, create_stack_node((void *)cur_node_info));

    if (++cur_stack_length >= bst->_size)
    {
      break;
    }
    if (cur_node->_left_child)
    {
      cur_node = cur_node->_left_child;
      continue;
    }
    while (!cur_node->_right_child || cur_node->_right_child == prev_node)
    {
      prev_node = cur_node;
      cur_node = cur_node->_parent;
      if (!cur_node)
      {
        break;
      }
    }
    cur_node = cur_node->_right_child;
  }

  return node_stack;
}

BSTNode *bst_root(BST *bst)
{
  if (!bst)
  {
    throw_null_bst_exception();
  }
  return bst->_root;
}

size_t bst_size(BST *bst)
{
  if (!bst)
  {
    throw_null_bst_exception();
  }
  return bst->_size;
}

u_long bst_node_key(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  return node->_key;
}

BSTNode *bst_node_left_child(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  return node->_left_child;
}

BSTNode *bst_node_right_child(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  return node->_right_child;
}

BSTNode *bst_node_parent(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  return node->_parent;
}

int bst_node_height(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  return node->_height;
}

// Private functions

static void append_node(BSTNode *parent_node, BSTNode *child_node)
{
  if (!parent_node || !child_node)
  {
    throw_null_bst_node_exception();
  }
  BSTNode *cur_node = parent_node;

  while (1)
  {
    ++cur_node->_height;
    if (child_node->_key < cur_node->_key)
    {
      if (cur_node->_left_child)
      {
        cur_node = cur_node->_left_child;
        continue;
      }
      cur_node->_left_child = child_node;
      child_node->_parent = cur_node;
      break;
    }
    else
    {
      if (cur_node->_right_child)
      {
        cur_node = cur_node->_right_child;
        continue;
      }
      cur_node->_right_child = child_node;
      child_node->_parent = cur_node;
      break;
    }
  }
}

static BSTNode *get_unbalanced_node(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  BSTNode *cur_node = node;

  while (is_balanced_node(cur_node))
  {
    cur_node = cur_node->_parent;
    if (!cur_node)
    {
      break;
    }
  }

  return cur_node;
}

static BSTNode *get_left_most_node(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  BSTNode *cur_node = node;

  while (cur_node->_left_child)
  {
    cur_node = cur_node->_left_child;
  }

  return cur_node;
}

static BSTNode *get_right_most_node(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  BSTNode *cur_node = node;

  while (cur_node->_right_child)
  {
    cur_node = cur_node->_right_child;
  }

  return cur_node;
}

static BSTNode *get_deepthest_node(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  BSTNode *cur_node = node;
  int l_height, r_height;

  while (cur_node->_height != 0)
  {
    l_height = get_node_height(cur_node->_left_child);
    r_height = get_node_height(cur_node->_right_child);
    cur_node = l_height > r_height ? cur_node->_left_child : cur_node->_right_child;
  }

  return cur_node;
}

static int get_node_height(BSTNode *node)
{
  return node ? node->_height : -1;
}

static int get_node_balance(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  return get_node_height(node->_left_child) - get_node_height(node->_right_child);
}

static int get_node_children_quantity(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  int qt = 0;
  if (node->_left_child)
  {
    qt += 1;
  }
  if (node->_right_child)
  {
    qt += 1;
  }
  return qt;
}

static bool is_balanced_node(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  return abs(get_node_balance(node)) <= 1;
}

static bool is_left_heavy_node(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  return get_node_balance(node) > 0;
}

static bool is_right_heavy_node(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  return get_node_balance(node) < 0;
}

static void update_node_height(BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  BSTNode *cur_node = node;
  int l_height, r_height;

  while (cur_node)
  {
    l_height = get_node_height(cur_node->_left_child);
    r_height = get_node_height(cur_node->_right_child);
    cur_node->_height = (l_height > r_height ? l_height : r_height) + 1;
    cur_node = cur_node->_parent;
  }
}

static void balance_node(BST *bst, BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  BSTNode *unbalanced_node = get_unbalanced_node(node);

  if (!unbalanced_node)
  {
    return;
  }

  if (is_left_heavy_node(unbalanced_node))
  {
    if (unbalanced_node->_left_child->_right_child)
    {
      left_rotate_node(bst, unbalanced_node->_left_child);
      right_rotate_node(bst, unbalanced_node);
      return;
    }
    right_rotate_node(bst, unbalanced_node);
  }
  else
  {
    if (unbalanced_node->_right_child->_left_child)
    {
      right_rotate_node(bst, unbalanced_node->_right_child);
      left_rotate_node(bst, unbalanced_node);
      return;
    }
    left_rotate_node(bst, unbalanced_node);
  }
}

static void left_rotate_node(BST *bst, BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  BSTNode *parent_node, *child_node;
  parent_node = node->_parent;
  child_node = node->_right_child;
  node->_right_child = NULL;

  child_node->_parent = parent_node;
  node->_parent = child_node;

  if (parent_node)
  {
    if (child_node->_key < parent_node->_key)
    {
      parent_node->_left_child = child_node;
    }
    else
    {
      parent_node->_right_child = child_node;
    }
  }

  if (child_node->_left_child)
  {
    append_node(node, child_node->_left_child);
  }
  child_node->_left_child = node;

  if (node == bst->_root)
  {
    bst->_root = child_node;
  }

  update_node_height(node);
}

static void right_rotate_node(BST *bst, BSTNode *node)
{
  if (!node)
  {
    throw_null_bst_node_exception();
  }
  BSTNode *parent_node, *child_node;
  parent_node = node->_parent;
  child_node = node->_left_child;
  node->_left_child = NULL;

  child_node->_parent = parent_node;
  node->_parent = child_node;

  if (parent_node)
  {
    if (child_node->_key < parent_node->_key)
    {
      parent_node->_left_child = child_node;
    }
    else
    {
      parent_node->_right_child = child_node;
    }
  }

  if (child_node->_right_child)
  {
    append_node(node, child_node->_right_child);
  }
  child_node->_right_child = node;

  if (node == bst->_root)
  {
    bst->_root = child_node;
  }

  update_node_height(node);
}