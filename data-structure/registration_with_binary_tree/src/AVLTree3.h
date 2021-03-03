#ifndef AVLTREE3_HEADER
#define AVLTREE3_HEADER

typedef struct _Node
{
  unsigned long key;
  void *value;
  struct _Node *left_child;
  struct _Node *right_child;
  struct _Node *parent;
  int height;
} Node;

Node *create_node(unsigned long key, void *value);
Node *insert_node(Node *node, unsigned long key, void *value);
Node *find_node(Node *node, unsigned long key);
void remove_node(Node *node, unsigned long key);
Node *get_left_most_node(Node *node);
Node *get_right_most_node(Node *node);
Node *get_root_node(Node *node);
int get_node_balance(Node *node);

#endif