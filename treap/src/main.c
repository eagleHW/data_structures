#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "treap/treap.h"

int main()
{
  struct treap* new_treap = init_treap();
  struct node* node_1 = init_node(15,4);
  struct node* node_2 = init_node(5,6);
  struct node* node_3 = init_node(2,2);
  struct node* node_4 = init_node(23,7);
  struct node* node_5 = init_node(4,3);
  struct node* node_6 = init_node(8,10);
  struct node* node_7 = init_node(56,9);
   insert(node_1,new_treap);
   insert(node_2,new_treap);
   insert(node_3,new_treap);
   insert(node_4,new_treap);
   insert(node_5,new_treap);
   insert(node_6,new_treap);
   insert(node_7,new_treap);


   //Util para ver que el arbol esta correctamente construido
   //side i = izquierda d = derecha
   /*   
   printf("Modo debuger\n");
   dfs(new_treap->root,false);  
   printf("Fin modo debuger\n");
   */

   print_array(order(new_treap),new_treap->size);

   delete(4,new_treap);

   print_array(order(new_treap),new_treap->size);

   return EXIT_FAILURE;
}





