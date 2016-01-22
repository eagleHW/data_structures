#ifndef STACK_H_
#define STACK_H_

struct stack_item {
  char element;
  struct stack_item* tail;
};

struct stack {
  struct stack_item* head;
};

struct stack* init_stack(void);
void destroy_stack(struct stack*);

struct stack_item* init_item(void);
void destroy_item(struct stack_item*);

void push(char,struct stack*);
char pop(struct stack*);

int empty(struct stack*);

void imprime_stack(struct stack* stack);

#endif STACK_H_
