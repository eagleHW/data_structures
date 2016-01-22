#include <stdlib.h>

#ifndef INTERVAL_H_
#define INTERVAL_H_

typedef struct interval_node{
  struct interval_node* left;
  struct interval_node* right;

  struct interval_list* left_list;
  struct interval_list* right_list;

  int key;

} i_node;

typedef struct interval_list{

  int* interval;
  struct interval_list* next;

} i_list;

i_list* init_list(); 

void destroy_list(i_list*);

i_node* init_node();

void join_list(i_list*,i_list*);
 
i_node* build_interval_tree(int**,int);

i_node* list_build_interval_tree(i_list*,int,i_list*,int);

void overlapping_interval_search(i_node*,int*,i_list*);

// El equivalente en una lista a array[index]

i_list* index_elem(i_list*,int);

/*
  Separa una lista en dos la primera 
   sera del tamaño del parametro entero,se mantiene
   en el apuntador que se le pasa a la funcion
   y la segunda parte sera el apuntador que regresa 
   la funcion.
*/
i_list* disjoin_list(i_list*,int);

/*
  Realiza el algoritmo de ordenacion merge_sort 
  sobre listas.
*/

i_list* merge_sort(i_list*,int);
i_list* merge(i_list*,int,i_list*,int);


/* 
   Transforma a los arreglos en una lista de intervalos 
   la primera con el extremo izquierdo del como primera
   poscision del arreglo donde se guardan los intervalos
   en los nodos de las listas.
*/
i_list* create_l_list(int**,int);

/* 
   Transforma a los arreglos en una lista de intervalos 
   la primera con el extremo derecha del como primera
   poscision del arreglo donde se guardan los intervalos
   en los nodos de las listas.
*/

i_list* create_r_list(int**,int);

/*
  Imprime una lista
*/

void print_list(i_list*,int);
void uz_print_list(i_list*);

/*
  Encuentra la media de los elementos de dos listas
*/

int find_mid(i_list*,int,i_list*,int);

/*
  Elimina el primer elemento de una lista y 
  regresa el resto
 */

i_list* del_first_elem(i_list*);

#endif 
