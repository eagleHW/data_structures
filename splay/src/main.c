#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "splay/splay.h"

int main(){
    
  struct splay* new_splay= init_splay();
  struct splay_node* temp;
  
  // l - left
  // r - right
  // R - root

  insert(5,new_splay);
  insert(7,new_splay);
  insert(3,new_splay);
  insert(10,new_splay);
  insert(1,new_splay);
  insert(2,new_splay);
  insert(8,new_splay);
  printf("Árbol después de las inserciones\n\n");
  dfs_debug(new_splay->root);

  printf("\n\n");

  search(1,new_splay);
  printf("Árbol después de una búsqueda donde el elemento existe\n\n");
  dfs_debug(new_splay->root);
  
  printf("\n\n");

  search(11,new_splay);
  printf("Árbol después de una búsqueda donde el elemento NO existe\n\n");
  dfs_debug(new_splay->root);

  printf("\n\n");

  delete(7,new_splay);
  delete(8,new_splay);
  delete(1,new_splay);
  delete(2,new_splay);
  //delete(3,new_splay);
  //delete(10,new_splay);
  //delete(5,new_splay);

  printf("Árbol después de algunas eliminaciones\n\n");
  dfs_debug(new_splay->root);

  printf("\n\n");

  destroy_splay(new_splay);
  printf("El árbol ya ha sido eliminado\n\n");
  

}
