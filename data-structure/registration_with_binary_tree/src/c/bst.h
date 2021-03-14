#include <stdlib.h>
#include <stack.h>

#ifndef BST_HEADER
#define BST_HEADER 1

typedef struct _BSTNode
{
  u_long _key;
  void *value;
  struct _BSTNode *_left_child;
  struct _BSTNode *_right_child;
  struct _BSTNode *_parent;
  int _height;
} BSTNode;

typedef struct _BST
{
  BSTNode *_root;
  size_t _size;
} BST;

BST *create_bst(BSTNode *root);
BSTNode *create_bst_node(u_long key, void *value);
BSTNode *bst_find(BST *bst, u_long key);
void bst_insert(BST *bst, BSTNode *node);
void bst_delete(BST *bst, u_long key);
Stack *bst_to_stack(BST *bst);
BSTNode *bst_root(BST *bst);
size_t bst_size(BST *bst);
u_long bst_node_key(BSTNode *node);
BSTNode *bst_node_left_child(BSTNode *node);
BSTNode *bst_node_right_child(BSTNode *node);
BSTNode *bst_node_parent(BSTNode *node);
int bst_node_height(BSTNode *node);
// BST *bst_preorder(BST *bst);
// BST *bst_inorder(BST *bst);
// BST *bst_postorder(BST *bst);

#endif