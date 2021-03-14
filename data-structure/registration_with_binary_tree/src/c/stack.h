#include <stdlib.h>

#ifndef STACK_HEADER
#define STACK_HEADER 1

typedef struct _StackNode
{
  void *value;
  struct _StackNode *_prev;
  struct _StackNode *_next;
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
StackNode *stack_head(Stack *stack);
StackNode *stack_tail(Stack *stack);
size_t stack_size(Stack *stack);
StackNode *stack_next(StackNode *node);
StackNode *stack_prev(StackNode *node);

#endif
