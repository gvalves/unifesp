#include <stdio.h>
#include <stdlib.h>
#include <exception.h>
#include <stack.h>

static void throw_null_stack_exception();
static void throw_null_stack_node_exception();

static void throw_null_stack_exception()
{
  throw_null_exception("Stack");
}

static void throw_null_stack_node_exception()
{
  throw_null_exception("StackNode");
}

Stack *create_stack(StackNode *head)
{
  Stack *new_stack = malloc(sizeof(Stack));
  new_stack->_head = head;
  new_stack->_tail = head;

  if (head)
  {
    new_stack->_size = 1;
  }
  return new_stack;
}

StackNode *create_stack_node(void *value)
{
  StackNode *new_node = malloc(sizeof(StackNode));
  new_node->value = value;
  return new_node;
}

void stack_push(Stack *stack, StackNode *node)
{
  if (!stack)
  {
    throw_null_stack_exception();
  }
  if (!node)
  {
    throw_null_stack_node_exception();
  }
  ++stack->_size;

  if (!stack->_head)
  {
    stack->_head = node;
    stack->_tail = node;
    return;
  }
  StackNode *prev_tail = stack->_tail;
  prev_tail->_next = node;
  node->_prev = prev_tail;
  stack->_tail = node;
}

void *stack_pop(Stack *stack)
{
  if (!stack)
  {
    throw_null_stack_exception();
  }
  if (!stack->_head || !stack->_tail)
  {
    return NULL;
  }
  --stack->_size;

  StackNode *prev_tail = stack->_tail;
  void *value = prev_tail->value;

  if (stack->_head == prev_tail)
  {
    stack->_head = stack->_tail = NULL;
  }
  else
  {
    stack->_tail = prev_tail->_prev;
    stack->_tail->_next = NULL;
  }
  free(prev_tail);

  return value;
}

StackNode *stack_head(Stack *stack)
{
  if (!stack)
  {
    throw_null_stack_exception();
  }
  return stack->_head;
}

StackNode *stack_tail(Stack *stack)
{
  if (!stack)
  {
    throw_null_stack_exception();
  }
  return stack->_tail;
}

size_t stack_size(Stack *stack)
{
  if (!stack)
  {
    throw_null_stack_exception();
  }
  return stack->_size;
}

StackNode *stack_next(StackNode *node)
{
  if (!node)
  {
    throw_null_stack_node_exception();
  }
  return node->_next;
}

StackNode *stack_prev(StackNode *node)
{
  if (!node)
  {
    throw_null_stack_node_exception();
  }
  return node->_prev;
}