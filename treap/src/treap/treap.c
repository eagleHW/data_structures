#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "treap/treap.h"


struct treap* init_treap(){
  struct treap* new_treap = (struct treap*) malloc(sizeof(struct treap));
  new_treap->root = NULL;
  new_treap->size = 0;
  return new_treap;
}

struct node* init_node(int p_key,int p_priority){
  struct node* new_node = (struct node*) malloc(sizeof(struct node));
  new_node->parent = NULL;
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->key = p_key;
  new_node->priority = p_priority;
  return new_node;
}

void destroy_treap(struct treap* p_treap){
  dfs(p_treap->root,true);
}

void destroy_node(struct node* p_node){
  free(p_node);
}

void insert(struct node* p_node , struct treap* p_treap){
  BST_insert(p_treap,p_node);  
  correct_priority(p_treap,p_node);
  (p_treap->size)++;
}

struct node* delete(int key,struct treap* p_treap){
  
  struct node* e_node = NULL;
  bool flag = true;
  search_dfs(p_treap->root,key,&e_node);

  if(e_node == NULL){
    return NULL;
  }

  while(flag){   
    if(e_node->left == NULL && e_node->right == NULL){
      if(p_treap->size == 1){
	p_treap->root = NULL;
	break;
      }
      if(e_node == e_node->parent->right){
	e_node->parent->right = NULL;
      }else{
	e_node->parent->left = NULL;
      }
      e_node->parent = NULL;
      p_treap->size = p_treap->size--; 
      destroy_node(e_node); 
      flag = false;
    }else{   
      if(e_node->right == NULL){
	right_rotation(e_node);
      }else{
	if(e_node->left == NULL){
	  left_rotation(e_node);
	}else{
	  if(e_node->left->priority > e_node->right->priority){
	    right_rotation(e_node);
	  }else{	    
	    left_rotation(e_node);
	  }
	}
      }
      if(e_node == p_treap->root){
	p_treap->root = e_node->parent;
      }
    } 
  }
  return e_node; 
}

int* order(struct treap* p_treap){
  if(p_treap == NULL){
    return NULL;
  }
  int* array = (int*) malloc((sizeof(int))*(p_treap->size));  
  int contador = 0;
  array_dfs(p_treap->root,array,&contador);
  return array;
}


// Metodos Auxiliares 



/*

  Metodo que hace la insercion de un nodo como la 
  de un arbol binario de busqueda al treap.

*/

void BST_insert(struct treap* p_treap,struct node* p_node){
  struct node* temporal = p_treap->root;
  bool flag = true;

  if(p_node == NULL || p_treap == NULL){
    return;
  }
  
  if(p_treap->root == NULL){
    p_treap->root = p_node;
    p_node->side ='r';
  }else{
  
    while(flag){
      if(p_node->key <= temporal->key){
	if(temporal->left == NULL){
	  temporal->left = p_node;
	  p_node->parent = temporal;
	  p_node->side = 'i';
	  flag = false;
	}else{
	  temporal = temporal->left;
	}
      }else{
	if(temporal->right == NULL){
	  temporal->right = p_node;
	  p_node->parent = temporal;
	  p_node->side = 'd';
	  flag=false;
	}else{
	  temporal = temporal->right;
	} 
      }
    }   
  
  }
}

/*

  Metodo que corrije la propiedad de de prioridad
  del treap al colocar correctamente un nodo
  recien insertado.


 */
void correct_priority(struct treap* p_treap,struct node* p_node){
 
  while((p_node->parent != NULL) && (p_node->priority > (p_node->parent)->priority)){
    if(p_node == (p_node->parent)->right){
      left_rotation(p_node->parent);
    }else{
      right_rotation(p_node->parent);
    }
  }
  if(p_node->parent == NULL){
    p_treap->root = p_node;
  }
}

/*

  Rotacion a la derecha.

*/

void right_rotation(struct node* p_node){
  struct node* temporal = NULL;
  if(p_node == NULL){
    return;
  }
  if(p_node->left != NULL){
    temporal = (p_node->left)->right;
    (p_node->left)->right = p_node;
    if(p_node->parent != NULL){
      if((p_node->parent)->right == p_node){
	(p_node->parent)->right = p_node->left;
	p_node->left->side='d';
      }else{
	(p_node->parent)->left = p_node->left;
	p_node->left->side='i';
      }
    }else{p_node->left->side = 'r';}
    (p_node->left)->parent=p_node->parent;
    p_node->parent=p_node->left;
    p_node->left=temporal;
    p_node->side = 'd';
    if(temporal != NULL){
      temporal->parent=p_node;
      temporal->side='i';
    }
  }
}


/*

  Rotacion a la izquierda.

*/

void left_rotation(struct node* p_node){
  struct node* temporal = NULL;
  if(p_node == NULL){
    return;
  }
  if(p_node -> right != NULL){
    temporal = (p_node->right)->left;
    (p_node->right)->left = p_node;
    if(p_node->parent != NULL){
      if((p_node->parent)->right == p_node){
	(p_node->parent)->right = p_node->right;
	p_node->right->side='d';
      }else{
	(p_node->parent)->left = p_node->right;
	p_node->right->side='i';
      }
    }
    else{(p_node->right)->side = 'r';}
    (p_node->right)->parent = p_node->parent;
    p_node->parent=p_node->right;
    p_node->right= temporal;
    p_node->side = 'i';
    if(temporal != NULL){
      temporal->parent=p_node;
      temporal->side='d';
    }
  }
}


/*

  Metodo que realiza un recorrido DFS a partir de un nodo

  bool = false Modo lector/debbuger [ Da toda la informacion del arbol ]
  bool = true Modo destructor [ Libera la memoria ]

*/

void dfs(struct node* p_node,bool flag){
  if(p_node == NULL){
    return;
  }
  if(p_node->left != NULL){
    dfs(p_node->left,flag);
  }
  if(!flag){
    if(p_node->parent != NULL){
      printf("key = %d  priority = %d  parent = %d  side = %c \n",
	     p_node->key,p_node->priority,p_node->parent->key,p_node->side);
    }else{
      printf("key = %d  priority = %d  I am root \n",p_node->key,p_node->priority);
    }
  }
  if(p_node->right != NULL){
    dfs(p_node->right,flag);
  }  
  if(flag){
    destroy_node(p_node);
  }    
}

/*

  Busca un nodo dentro de un arbol por medio 
  de un recorrido DFS.

*/

void search_dfs(struct node* p_node,int l_key,struct node** resultado){
  if(p_node == NULL){
    *resultado = NULL;
    return;
  }

 if(p_node->left != NULL){
    search_dfs(p_node->left,l_key,resultado);
  }

  if(p_node->key == l_key){
    *resultado = p_node;
    return;
  }
  
  if(p_node->right != NULL){
    search_dfs(p_node->right,l_key,resultado);
  }  
}

/*

Pasa todos los nodos de un arbol a un arreglo.
contador siempre debe ser 0 al ser llamada la funcion
y el arreglo debe ser del tamaño del numero de nodos
del arbol.

*/

void array_dfs(struct node* p_node,int* array,int* contador){
  if(p_node == NULL){
    return;
  }

 if(p_node->left != NULL){
    array_dfs(p_node->left,array,contador);
  }
  
  array[*contador] = p_node->key;
  *contador = *contador + 1;
  
  if(p_node->right != NULL){
    array_dfs(p_node->right,array,contador);
  }  
}


void print_array(int* array,int size){
  int contador = 0;
    while(contador < size){
      printf("%d ",array[contador]);
      contador++;
    }
    printf("\n");
}

