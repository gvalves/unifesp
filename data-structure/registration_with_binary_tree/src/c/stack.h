#include <stdlib.h>

#ifndef STACK_HEADER
#define STACK_HEADER 1

typedef struct _StackNode
{
  void *value;
  struct _StackNode *prev;
  struct _StackNode *next;
} StackNode;

typedef struct _Stack
{
  StackNode *_head;
  StackNode *_tail;
  size_t _size;
} Stack;

Stack *create_stack(StackNode *head);
StackNode *create_stack_node(void *value);
void stack_push(Stack *stack, StackNode *node);
void *stack_pop(Stack *stack);
size_t stack_size(Stack *stack);

#endif
