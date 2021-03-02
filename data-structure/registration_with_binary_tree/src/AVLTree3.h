#ifndef AVLTREE3_HEADER
#define AVLTREE3_HEADER

typedef struct _Node
{
  unsigned long key;
  void *value;
  struct _Node *left_child;
  struct _Node *right_child;
  struct _Node *parent;
} Node;

Node *insert_node(Node *node, unsigned long key, void *value);
Node *find_node(Node *node, unsigned long key);
void remove_node(Node *node, unsigned long key);
Node *left_most_node(Node *node);
Node *right_most_node(Node *node);

#endif