#include <stdio.h>
#include <stdlib.h>

#include "stack/stack.h"

char isBalance(char* cadena){
  
  int cont = 0;
  struct stack* stack = init_stack(); 
  
  while(cadena[cont] != '\0'){

    if(cadena[cont] == '('){
      push('(',stack);
    } 

    if(cadena[cont] == ')'){
      if(empty(stack) == 1){
      destroy_stack(stack);
      return 0;
      }
    pop(stack);
    }
    cont++;

  }
  
  if(empty(stack) == 0){
    destroy_stack(stack);
    return 0;
  }
  
  destroy_stack(stack);
  return 1;
}

int main()
{
	printf("Compila de forma correcta.\n");
	printf("El resultado es: %d\n",isBalance("(())"));

	
	return EXIT_FAILURE;
}





