#include <stdlib.h>
#include <stdio.h>

#include "interval.h"


i_list* init_list(){
  i_list* new_list = (i_list*) malloc(sizeof(i_list));
  new_list->interval = (int*) malloc(sizeof(int)*2);
  new_list->next = NULL;
  return new_list;
}

i_node* init_node(){
  i_node* new_node = (i_node*) malloc(sizeof(i_node));
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->left_list = NULL;
  new_node->right_list = NULL;
  new_node->key= 0;
}

void join_list(i_list* f_list ,i_list* s_list){ 

  i_list* pf_list = f_list;
  while(pf_list->next != NULL){
    pf_list = pf_list->next;
  }
  pf_list->next=s_list;
}

i_node* build_interval_tree(int** intervals,int tam){

  i_list* list_l = merge_sort(create_l_list(intervals,tam),tam);
  i_list* list_r = merge_sort(create_r_list(intervals,tam),tam);
  
  return list_build_interval_tree(list_l,tam,list_r,tam);

}


i_node* list_build_interval_tree(i_list* ll_mid,int l_tam,i_list* rl_mid, int r_tam){

  int mid;

  i_list* pointer_ll_mid = ll_mid; //left_list
  i_list* pointer_rl_mid = rl_mid; //right_list
 
  i_list* left_list = init_list();
  int tam_left_list = 0;
  i_list* right_list = NULL;
  int tam_right_list = 0;
  
  i_list* pointer_left_list = left_list;
  
  i_list* l_left_list = init_list();
  i_list* pointer_l_left_list = l_left_list; 
  int tam_l_left_list = 0;

  i_list* l_right_list = init_list();
  i_list* pointer_l_right_list = l_right_list;
  int tam_l_right_list = 0;         

  i_list* r_left_list = init_list();
  i_list* pointer_r_left_list = r_left_list;
  int tam_r_left_list = 0;
   
  i_list* r_right_list = init_list();
  i_list* pointer_r_right_list = r_right_list;
  int tam_r_right_list = 0; 

  i_node* node = init_node();

  if(l_tam == 0 && r_tam == 0){
    return NULL;
  }
  
  mid = find_mid(ll_mid,l_tam,rl_mid,r_tam);
  
  for(int cont = 0; cont < l_tam;cont++){

    if((pointer_ll_mid->interval)[0] > mid ){
      pointer_l_right_list->next = pointer_ll_mid;
      tam_l_right_list++;
      pointer_ll_mid = pointer_ll_mid->next;
      pointer_l_right_list = pointer_l_right_list->next;
      pointer_l_right_list->next = NULL;      
      continue;
    }
    if((pointer_ll_mid->interval[1]) >= mid){
      pointer_left_list->next = pointer_ll_mid;
      tam_left_list++;
      pointer_ll_mid = pointer_ll_mid->next;
      pointer_left_list = pointer_left_list -> next; 
      pointer_left_list->next = NULL;
      
    }else{
      pointer_l_left_list->next = pointer_ll_mid;
      tam_l_left_list++;
      pointer_ll_mid = pointer_ll_mid->next; 
      pointer_l_left_list = pointer_l_left_list->next;
      pointer_l_left_list->next = NULL;
    }
  }
 
  for(int cont = 0; cont < r_tam ;cont++){

    if((pointer_rl_mid->interval)[0] < mid){
      pointer_r_left_list->next=pointer_rl_mid;
      tam_r_left_list++;                            
      pointer_rl_mid = pointer_rl_mid->next;  
      pointer_r_left_list=pointer_r_left_list->next;
      pointer_r_left_list->next = NULL;
      continue;
    }   

    if((pointer_rl_mid->interval)[1] <= mid){
      i_list* temp =pointer_rl_mid;
      pointer_rl_mid = pointer_rl_mid->next;
      tam_right_list++;
      temp->next= right_list;
      right_list = temp;
    }
    else{
      pointer_r_right_list->next = pointer_rl_mid;
      tam_r_right_list++;
      pointer_rl_mid = pointer_rl_mid->next;
      pointer_r_right_list = pointer_r_right_list->next;
      pointer_r_right_list->next = NULL;
    }
  }

  
  left_list = del_first_elem(left_list);

  node->key = mid;
  node->left_list = left_list;
  node->right_list = right_list;             

  l_left_list = del_first_elem(l_left_list);

  r_left_list= del_first_elem(r_left_list); 

  l_right_list = del_first_elem(l_right_list);

  r_right_list = del_first_elem(r_right_list);

  node->left = list_build_interval_tree(l_left_list , tam_l_left_list , r_left_list, tam_r_left_list);
  node->right = list_build_interval_tree(l_right_list, tam_l_right_list , r_right_list, tam_r_right_list);

  return node;
  
}

void overlapping_interval_search(i_node* tree,int* interval,i_list* answer){

  i_node* pointer = tree;
  
  if(tree == NULL){
    return;
  }
  
  if(answer == NULL){
    answer = init_list();
  }
  
  i_list* ans_pointer= answer;
  
  if(pointer->key >= interval[0] && pointer->key <= interval[1]){
   
    for(i_list* left_pointer = pointer->left_list; left_pointer != NULL ; left_pointer = left_pointer->next){      
      ans_pointer->next = init_list();
      ans_pointer = ans_pointer->next;
      (ans_pointer->interval)[0] = (left_pointer->interval)[0]; 
      (ans_pointer->interval)[1] = (left_pointer->interval)[1]; 
    }

    overlapping_interval_search(pointer->left,interval,ans_pointer);
    for(;ans_pointer->next != NULL;ans_pointer = ans_pointer->next);
    overlapping_interval_search(pointer->right,interval,ans_pointer);
  
  }else{
    if(pointer->key > interval[1]){
  
      for(i_list* left_pointer = pointer->left_list; left_pointer != NULL && (left_pointer->interval)[0] <= interval[1];
	  left_pointer=left_pointer->next){
 	ans_pointer->next = init_list();
	ans_pointer = ans_pointer->next;
	(ans_pointer->interval)[0] = (left_pointer->interval)[0]; 
	(ans_pointer->interval)[1] = (left_pointer->interval)[1]; 
      }

      overlapping_interval_search(pointer->left,interval,ans_pointer);
    }
    else{
      if(pointer->key < interval[0]){

	for(i_list* right_pointer = pointer->right_list; right_pointer != NULL && (right_pointer->interval)[0] >= interval[0];
	    right_pointer=right_pointer->next){
	  ans_pointer->next = init_list();
	  ans_pointer = ans_pointer->next;
	  (ans_pointer->interval)[0] = (right_pointer->interval)[1]; 
	  (ans_pointer->interval)[1] = (right_pointer->interval)[0]; 
	}
	overlapping_interval_search(pointer->right,interval,ans_pointer);
      }

    }
  }
}


int find_mid(i_list* f_list,int f_tam ,i_list* s_list,int s_tam){
  
  int* endpoints = (int*) malloc(sizeof(int)* (f_tam+s_tam));
  int mid = 0;
  i_list* f_pointer = f_list;
  i_list* s_pointer = s_list;

  for(int cont = 0;cont < (f_tam+s_tam);cont++){

    if(f_pointer == NULL){
      endpoints[cont]=(s_pointer->interval)[0];
      s_pointer = s_pointer->next;
      continue;
    }
    if(s_pointer == NULL){
      endpoints[cont]=(f_pointer->interval)[0];
      f_pointer = f_pointer->next;
      continue;
    }
    if((f_pointer->interval)[0] < (s_pointer->interval)[0]){
      endpoints[cont]=(f_pointer->interval)[0];
      f_pointer = f_pointer->next;
    }else{
      endpoints[cont]=(s_pointer->interval)[0];
      s_pointer = s_pointer->next;
    }
  }

  mid = endpoints[(f_tam+s_tam)/2];
  free(endpoints);
  return mid;
}



i_list* merge_sort(i_list* p_list,int tam){

  int mid = tam/2;
  i_list* f_list = p_list;
  i_list* s_list = disjoin_list(f_list,mid);
 
  if(mid == 0){
    return p_list;
  }else{
    f_list = merge_sort(f_list,mid);
    s_list = merge_sort(s_list,tam-mid);
            
    return merge(f_list,mid,s_list,tam-mid);
  }
}

i_list* merge(i_list* f_list,int f_tam, i_list* s_list,int s_tam){

  i_list* new_list = NULL;
  i_list* pointer = NULL;

  if(f_list->interval[0] < s_list->interval[0]){
    new_list = f_list;
    pointer = f_list;
    f_list = f_list->next;
    f_tam--;
   }else{
    new_list = s_list;
    pointer = s_list;
    s_list = s_list->next;
    s_tam--;
   }
  
  while(f_tam > 0 && s_tam > 0){    
    if(f_list->interval[0] < s_list->interval[0]){
      pointer->next = f_list;
      pointer = pointer->next;
      f_list = f_list->next;
      f_tam--;
    }else{  
      pointer->next=s_list;
      pointer = pointer->next;
      s_list = s_list->next;
      s_tam--;
    }
  }

  if(f_tam > 0){
    pointer->next = f_list;
  }else{
    pointer->next = s_list;
  }

  return new_list;

}


i_list* disjoin_list(i_list* p_list,int index){

  i_list* pp_list = p_list;
  i_list* pred = NULL;
  int cont = 0;

  if(index == 0){
    return p_list;
  }
  while(pp_list->next != NULL || cont == index){
    if(cont == index){
      pred->next = NULL;
      return pp_list;
    }
    cont++;
    pred = pp_list;
    pp_list = pp_list->next;
  }
  return NULL;

}


void destroy_list(i_list* list){

  list->next = NULL;
  free(list->interval);
  free(list);

}

//indices empiezan en 0 

i_list* index_elem(i_list* p_list, int index){
  i_list* pp_list = p_list;
  int cont = 0;

  if(index == 0){
    return p_list;
  }
  while(pp_list->next != NULL){
    if(cont == index){
      return pp_list;
    }
    cont++;
    pp_list = pp_list->next;
  }
  return NULL;
}


i_list* del_first_elem(i_list* p_list){

  i_list* pointer = p_list->next;
  destroy_list(p_list);
  return pointer;

}

