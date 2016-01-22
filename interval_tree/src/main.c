#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "interval_tree/interval.h"

int main(){

  int tam = 8; // # de intervalos
  //Intervalos
  int values_s[8][2] = {{1,11},{15,19},{8,16},{3,10},{14,21},{4,15},{5,7},{22,24}};  
  int** values = (int**) malloc(sizeof(int*)*tam);
  //Intervalo al cual se deben sobreponer 
  int interval[2] = {10,15};


  for(int cont = 0;cont<tam;cont++){
    values[cont] = values_s[cont];
  }

  i_node* tree = build_interval_tree(values,tam);
  i_list* answer = init_list();

  overlapping_interval_search(tree,interval,answer); 
  
  printf("RESPUESTA = ");
  uz_print_list(answer->next);

  return 0;
}

i_list* create_l_list(int** numbers, int tam){

  int cont = 0;
  i_list* new_list = NULL;
  i_list* pointer = NULL;

  new_list = init_list();
  (new_list->interval)[0]=numbers[0][0];
  (new_list->interval)[1]=numbers[0][1];
 
  pointer = new_list;
  cont = cont++;

  while(cont < tam){
    pointer->next = init_list();
    (pointer->next->interval)[0]=numbers[cont][0];
    (pointer->next->interval)[1]=numbers[cont][1];
    pointer = pointer->next;
    cont = cont++;
  }

  return new_list;
}

i_list* create_r_list(int** numbers, int tam){

  int cont = 0;
  i_list* new_list = NULL;
  i_list* pointer = NULL;

  new_list = init_list();
  (new_list->interval)[0]=numbers[0][1];
  (new_list->interval)[1]=numbers[0][0];
 
  pointer = new_list;
  cont = cont++;

  while(cont < tam){
    pointer->next = init_list();
    (pointer->next->interval)[0]=numbers[cont][1];
    (pointer->next->interval)[1]=numbers[cont][0];
    pointer = pointer->next;
    cont = cont++;
  }

  return new_list;
}


void print_list(i_list* p_list, int tam){

  i_list* pointer = p_list;
  int cont = 0;

  while(cont < tam){
    printf("( %d , %d )  ",(pointer->interval)[0],(pointer->interval)[1]);
    cont++;
    pointer = pointer->next;
  }

  printf("\n");  
}


void uz_print_list(i_list* p_list){

  for(i_list* pointer = p_list; pointer != NULL; pointer=pointer->next ){ 
    printf("( %d , %d )  ",(pointer->interval)[0],(pointer->interval)[1]);
  }
  
  printf("\n");

}

