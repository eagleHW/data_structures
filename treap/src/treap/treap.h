#include <stdbool.h> 

#ifndef TREAP_H_
#define TREAP_H_

struct node {
  struct node* left;
  struct node* right;
  struct node* parent;
  char side;
  int priority;
  int key;
};

struct treap {
  struct node* root;
  int size;
};

struct treap* init_treap();//
struct node* init_node(int,int);//

void destroy_treap(struct treap*);//
void destroy_node(struct node*); //

void insert(struct node*,struct treap*); //
void BST_insert(struct treap*, struct node*);//
void correct_priority(struct treap*,struct node*);//

void right_rotation(struct node*);//
void left_rotation(struct node*);//

struct node* delete(int, struct treap*);//

int* order(struct treap*);//

void dfs(struct node*,bool);
void search_dfs(struct node*,int,struct node**);
void array_dfs(struct node*,int*,int*);
#endif TREAP_H_
