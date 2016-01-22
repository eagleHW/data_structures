#include <stdbool.h>

#ifndef SPLAY_H_
#define SPLAY_H_

struct splay_node{
  int key;
  char side;
  struct splay_node* right;
  struct splay_node* left;
  struct splay_node* parent;

};


struct splay{ 
  struct splay_node* root;
};

struct splay* init_splay();
void destroy_splay(struct splay*); 

/*
  Recorrido DFS sobre el arbol splay 
  que libera la memoria de los nodos
  metodo usado por destroy_splay
*/

void dfs_destroy(struct splay_node*);

/*
  Recorrido DFS sobre el arbol splay 
  que nos muestra informacion sobre
  el arbol.
*/

void dfs_debug(struct splay_node*); 

struct splay_node* init_splay_node();
void destroy_splay_node(struct splay_node*); 

struct splay_node* search(int, struct splay*);
void insert(int,struct splay*);
struct splay_node* delete(int, struct splay*);

struct splay_node* search_new_root(struct splay*);

void  splaying(struct splay_node*,struct splay*);

void  zig_step(struct splay_node*, struct splay*);
void  zig_zig_step(struct splay_node*, struct splay*);
void  zig_zag_step(struct splay_node*, struct splay*);

/*
  Rotacion a la derecha clasica
*/

void right_rotation(struct splay_node*);

/*
  Rotacion a la izquierda clasica
*/

void left_rotation(struct splay_node*);

#endif
