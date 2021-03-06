#include <stdlib.h>
#include <stack.h>

#ifndef BST_HEADER
#define BST_HEADER 1

typedef struct _BSTNode
{
  u_long key;
  void *value;
  struct _BSTNode *left_child;
  struct _BSTNode *right_child;
  struct _BSTNode *parent;
  int height;
} BSTNode;

typedef struct _BST
{
  BSTNode *root;
  struct _BSTPrivate
  {
    size_t _size;
  } _private;
} BST;

BST *create_bst(BSTNode *root);
BSTNode *create_bst_node(u_long key, void *value);
BSTNode *bst_find(BST *bst, u_long key);
void bst_insert(BST *bst, BSTNode *node);
void bst_delete(BST *bst, u_long key);
Stack *bst_to_stack(BST *bst);
size_t bst_size(BST *bst);
// BST *bst_preorder(BST *bst);
// BST *bst_inorder(BST *bst);
// BST *bst_postorder(BST *bst);

#endif