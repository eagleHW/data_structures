#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "splay/splay.h"

struct splay* init_splay(){
  struct splay* new_splay = (struct splay*) malloc(sizeof(struct splay));
  return new_splay;
}

void destroy_splay(struct splay* p_splay){
  if(p_splay != NULL){
    dfs_destroy(p_splay->root);
  }
  p_splay->root = NULL;
  free(p_splay);
}


struct splay_node* init_splay_node(){
  struct splay_node* new_splay_node= (struct splay_node*) malloc(sizeof(struct splay_node));
  new_splay_node->key = 0;
  new_splay_node->side = 'u'; //undefined
  new_splay_node->left = NULL;
  new_splay_node->right = NULL;
  new_splay_node->parent = NULL;

  return new_splay_node;
}

void destroy_splay_node(struct splay_node* p_splay_node){
  p_splay_node->right = NULL;
  p_splay_node->left = NULL;
  p_splay_node->parent = NULL;
  free(p_splay_node);
}

struct splay_node* search(int p_key,struct splay* p_splay){

  struct splay_node* pr_temp = NULL;
  struct splay_node* temp = p_splay->root;
 
  while(p_key != temp->key){   
      
    if(p_key > temp->key){
      temp->parent = pr_temp;
      pr_temp = temp;
      if(temp->right == NULL){
	splaying(temp,p_splay);
	return NULL;
      }
      temp = temp->right;
    }else{
      temp->parent = pr_temp;
      pr_temp = temp;      
      if(temp->left == NULL){
	splaying(temp,p_splay);
	return NULL;
      }
      temp = temp->left;
    }
  }  
  temp->parent = pr_temp;
  splaying(temp,p_splay);
  return temp;

}

void insert(int p_key,struct splay* p_splay){

  struct splay_node* pr_temp = NULL;
  struct splay_node* temp = p_splay->root;

  if(temp == NULL){
    p_splay->root = init_splay_node();
    p_splay->root->key = p_key;  
    p_splay->root->side = 'R'; //Root
    return;
 }

  while(temp != NULL){

    if(p_key > temp->key){
      temp->parent = pr_temp;
      pr_temp = temp;
      
      if(temp->right == NULL){
	temp->right = init_splay_node();
	temp->right->key = p_key;
	temp->right->side = 'r'; //right
	temp->right->parent = temp;
	splaying(temp->right,p_splay);
	break;
      }

      temp = temp->right;
    }else{
      temp->parent = pr_temp;
      pr_temp = temp;
   
      if(temp->left == NULL){
	temp->left = init_splay_node();
	temp->left->key = p_key;
	temp->left->side = 'l'; //left
	temp->left->parent = temp;  
	splaying(temp->left,p_splay);
	break;
      }
      temp = temp->left;
    }

  }
}

struct splay_node* delete(int p_key,struct splay* p_splay){
  
  struct splay_node* temp = search(p_key,p_splay);
  struct splay_node* new_root = search_new_root(p_splay);
  
  if(temp == NULL){
    return NULL;
  }else{
    if(new_root == NULL){
      p_splay->root = NULL; 
      destroy_splay_node(temp);
      return temp;                            
    }
  }

   if(new_root->key > temp->key){
     if(new_root->right == NULL){
       if(new_root->parent->side == 'R'){
	 new_root->parent->right = NULL;
       }else{
	 new_root->parent->left = NULL;
       }
     }else{
       if(new_root->parent->side == 'R'){
	 new_root->parent->right = new_root->right;
	 new_root->right->parent = NULL;
	 new_root->right = NULL;
       }else{
	 new_root->parent->left = new_root->right;
	 new_root->right->side = 'l';
	 new_root->right->parent = NULL;
	 new_root->right = NULL;
       }
     }
   }else{
     if(new_root->left == NULL){
       if(new_root->parent->side == 'R'){
	 new_root->parent->left =  NULL;
       }else{
	 new_root->parent->right =  NULL;
       }
     }else{
       if(new_root->parent->side == 'R'){
	 new_root->parent->left = new_root->left;
	 new_root->left->parent = NULL;
	 new_root->left = NULL;
       }else{
	 new_root->parent->right = new_root->left;
	 new_root->left->side='r';
	 new_root->left->parent = NULL;
	 new_root->left = NULL;
       }
     }
   }
   
  new_root->left = temp->left;
  if(temp-> left != NULL){
    temp->left->parent = NULL;
  }
  new_root->right = temp-> right;
  if(temp->right != NULL){
    temp->right->parent = NULL;
  }

  new_root->parent = NULL;
  new_root->side = 'R';

  p_splay->root = new_root;
  
  destroy_splay_node(temp);
  return temp;                            
}


void splaying(struct splay_node* p_splay_node, struct splay* p_splay){

  struct splay_node* p_parent = p_splay_node->parent; 
  
  while(p_parent != NULL){
    
    if(p_parent->parent == NULL){
      zig_step(p_splay_node,p_splay);
      p_parent = p_splay_node->parent; 
      continue;
    }
    if(p_splay_node->side == p_parent->side){
      zig_zig_step(p_splay_node,p_splay);
      p_parent = p_splay_node->parent; 
      continue;	
    }else{
      zig_zag_step(p_splay_node,p_splay);
      p_parent = p_splay_node->parent; 
      continue;
    }
  }


}

void zig_step(struct splay_node* p_splay_node,struct splay* p_splay){
  if(p_splay_node->side == 'l'){
    right_rotation(p_splay_node->parent);
  }else{
    left_rotation(p_splay_node->parent);
  }

  p_splay->root = p_splay_node;

}

void zig_zig_step(struct splay_node* p_splay_node,struct splay* p_splay){

  struct splay_node* p_parent = p_splay_node->parent; 
  struct splay_node* p_grandparent = p_parent->parent;

   if(p_splay->root == p_grandparent){
    p_splay->root = p_splay_node;

  }

  if(p_splay_node->side == 'l' && p_parent->side == 'l'){
    
    right_rotation(p_grandparent);
    right_rotation(p_parent);
  }

  if(p_splay_node->side == 'r' && p_parent->side == 'r'){
    left_rotation(p_grandparent);
    left_rotation(p_parent);
  }

}

void zig_zag_step(struct splay_node* p_splay_node, struct splay* p_splay){
  
  struct splay_node* p_parent = p_splay_node->parent; 
  struct splay_node* p_grandparent = p_parent->parent;

  
  if(p_splay->root == p_grandparent){
    p_splay->root = p_splay_node;

  }
 
  if(p_splay_node->side == 'l' && p_parent->side == 'r'){
    right_rotation(p_parent);
    left_rotation(p_grandparent);
  }
  if(p_splay_node->side == 'r' && p_parent->side == 'l'){
    left_rotation(p_parent);
    right_rotation(p_grandparent);
  }

}


void dfs_destroy(struct splay_node* p_splay_node){

  if(p_splay_node != NULL){
    if(p_splay_node->left != NULL){
      dfs_destroy(p_splay_node->left);
    }
    if(p_splay_node->right != NULL){
      dfs_destroy(p_splay_node->right);
    }    
    destroy_splay_node(p_splay_node);
  }
}



void dfs_debug(struct splay_node* p_splay_node){
  
  if(p_splay_node == NULL){
    printf("El arbol esta vacio\n\n");
  }else{
    if(p_splay_node->left != NULL){
      dfs_debug(p_splay_node->left);
    }
    if(p_splay_node->right != NULL){
      dfs_debug(p_splay_node->right);
    }    
    
    if(p_splay_node->right == NULL || p_splay_node->left == NULL){
      
      if(p_splay_node->right != NULL){
	printf("KEY = %d   LEFT_KEY = NULL   RIGHT_KEY = %d", p_splay_node->key,p_splay_node->right->key);
      }else{
	if(p_splay_node->left != NULL){
	  printf("KEY = %d   LEFT_KEY = %d   RIGHT_KEY = NULL", p_splay_node->key,p_splay_node->left->key);
	  }else{
	  printf("KEY = %d   LEFT_KEY = NULL   RIGHT_KEY = NULL", p_splay_node->key);
	}
      }
      
    }else{
      
      printf("KEY = %d   LEFT_KEY = %d   RIGHT_KEY = %d", p_splay_node->key,p_splay_node->left->key,p_splay_node->right->key); 
    }
            
      printf("  SIDE = %c \n",p_splay_node->side);
       
  } 
}
  
void right_rotation(struct splay_node* p_splay_node){

  struct splay_node* p_parent = p_splay_node->parent;
  struct splay_node* p_left = p_splay_node->left;
  
  if(p_splay_node == NULL || p_splay_node->left == NULL){
    return;
  }

  if(p_parent != NULL){
   
    if(p_splay_node->side == 'l'){
      p_parent->left = p_left;
      p_left->side = 'l';
    }else{
      p_parent->right = p_left;
      p_left->side = 'r';
    }

  }else{
    p_left->side = 'R';
  }

  if(p_left->right != NULL){
  p_left->right->side = 'l';
  }

  p_splay_node->left = p_left->right;
  p_left->right = p_splay_node;
  p_splay_node->side='r';
  p_left->parent = p_parent;
  
}

void left_rotation(struct splay_node* p_splay_node){

  struct splay_node* p_parent;
  struct splay_node* p_right; 
    
  if(p_splay_node == NULL || p_splay_node->right == NULL){
    return;
  }

  p_parent = p_splay_node->parent;
  p_right = p_splay_node->right;

  if(p_parent != NULL){
   
    if(p_splay_node->side == 'l'){
      p_parent->left = p_right;
      p_right->side = 'l';
    }else{
      p_parent->right = p_right;
      p_right->side = 'r';
    }

  }else{
    p_right->side = 'R';
  }

  if(p_right->left != NULL){
  p_right->left->side = 'r';
  }

  p_splay_node->right = p_right->left;
  p_right->left = p_splay_node;
  p_splay_node->side='l';
  p_right->parent = p_parent;
}


struct splay_node* search_new_root(struct splay* p_splay){

  struct splay_node* pr_temp = NULL;
  struct splay_node* temp = p_splay->root;

  if(temp->left == NULL && temp->right == NULL){
    return NULL;
  }
  
  if(temp->left != NULL){
    temp->parent = pr_temp;
    pr_temp = temp;
    temp = temp->left;  
    while(temp->right != NULL){
      temp->parent = pr_temp;
      pr_temp = temp;
      temp=temp->right;
    }
    temp->parent = pr_temp;
  }else{
    temp->parent = pr_temp;
    pr_temp = temp;
    temp = temp->right;
    while(temp->left != NULL){
      temp->parent = pr_temp;
      pr_temp = temp;
      temp=temp->left; 
    } 
    temp->parent = pr_temp;
  }
  
  return temp;
}


