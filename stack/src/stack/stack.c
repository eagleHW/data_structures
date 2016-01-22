#include <stdlib.h>
#include <stdio.h>

#include "stack/stack.h"

struct stack* init_stack() 
{
  struct stack* primer_elem = (struct stack*) malloc(sizeof(struct stack));
  primer_elem->head = NULL; 
  return primer_elem;
}

void destroy_stack(struct stack* stack)
{
  struct stack_item* mem;
  while(stack->head != NULL){
    mem = stack->head;
    stack->head = mem->tail;
    destroy_item(mem);
  }
  free(stack);
  return;
}

struct stack_item* init_item()
{
  struct stack_item* elemento = (struct stack_item*) malloc(sizeof(struct stack_item));
  elemento->element=' ';
  elemento->tail=NULL;
  return elemento;
}

void destroy_item(struct stack_item* stack_item)
{
  free(stack_item);
  return;
}

void push(char element,struct stack* stack)
{
  struct stack_item* elemento = init_item();
  elemento->element=element;
  elemento->tail=stack->head;
  stack->head=elemento;
  return;
}

char pop(struct stack* stack) 
{
  struct stack_item* elemento = stack->head;
  char c_elemento = elemento->element;
  stack->head=elemento->tail;
  destroy_item(elemento);
  return c_elemento;
}

int empty(struct stack* stack) 
{
  if(stack->head == NULL){
    return 1;
  }
  return 0;
}

void imprime_stack(struct stack* stack)
{
  struct stack_item* mem = stack->head;
  
  while(mem != NULL){
    printf("%c  ",mem->element);
    mem = mem->tail;
  }
  printf("\n");
}
