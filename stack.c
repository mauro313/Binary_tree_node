#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/**
 * @brief create a new stack of the specified max size.
 * 
 * @param maxsize 
 * @return stack_t* 
 */
stack_t* stack_new(int maxsize){
  stack_t* new_stack = (stack_t*)malloc(sizeof(stack_t));
  if(new_stack == NULL){
    printf("memory cannot be reserved for a new stack pointer");
    exit(EXIT_FAILURE);  
  }
  new_stack->s = (t_elem_1*)malloc(maxsize*sizeof(t_elem_1));
  if(new_stack->s == NULL){
    printf("memory cannot be reserved for a t_elem pointer");
    free(new_stack);
    exit(EXIT_FAILURE);        
  }
  new_stack->top = 0;
  new_stack->maxsize = maxsize;
  return new_stack;    
}

/**
 * @brief free the memory of a stack.
 * 
 * @param s 
 */
void stack_free(stack_t** s){
  if(s != NULL && *s != NULL){
    free((*s)->s);
    (*s)->s = NULL;
    free(*s);
    *s = NULL; 
  }
}

/**
 * @brief get the current size of a stack.
 * 
 * @param s 
 * @return int 
 */
int stack_getsize(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null(1)");
    exit(EXIT_FAILURE);    
  }
  return s->top;    
}

/**
 * @brief get the max size of a stack.
 * 
 * @param s 
 * @return int 
 */
int stack_getmaxsize(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null(2)");
    exit(EXIT_FAILURE);    
  }
  return s->maxsize;    
}

/**
 * @brief return true if the stack is empty and false otherwise.
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool stack_isempty(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null(3)");
    exit(EXIT_FAILURE);    
  }
  return (s->top == 0);
}

/**
 * @brief return true if the stack is full and false otherwise.
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool stack_isfull(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null(4)");
    exit(EXIT_FAILURE);    
  }
  return (s->top == s->maxsize);
}

/**
 * @brief introduce an element into a stack.Return true if the element was introduced and false 
 * otherwise(full stack).
 * 
 * @param s 
 * @param elem 
 * @return bool 
 */
bool push(stack_t* s, t_elem_1 elem){
  if(s == NULL){
    printf("stack pointer is null(5)");
    exit(EXIT_FAILURE);    
  }
  bool returned = false;
  if(!stack_isfull(s)){
    s->s[s->top] = elem;
    s->top++;
    returned = true;    
  }
  return returned;     
}

/**
 * @brief remove the top element from a stack.
 * 
 * @param s 
 * @return t_elem_1 
 */
t_elem_1 pop(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null(6)");
    exit(EXIT_FAILURE);    
  }
  if(stack_isempty(s)){
    printf("stack is empty(1)");
    exit(EXIT_FAILURE);  
  }
  t_elem_1 returned = s->s[s->top-1];
  s->top--;   
  return returned;
}

/**
 * @brief allows to see the top element from a stack.
 * 
 * @param s 
 * @return t_elem_1 
 */
t_elem_1 top(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null(7)");
    exit(EXIT_FAILURE);   
  }
  if(stack_isempty(s)){
    printf("stack is empty(2)");
    exit(EXIT_FAILURE);  
  }
  return s->s[s->top];
}

/**
 * @brief traverse the stack using a context variable.
 * 
 * @param stack 
 * @param stack_do 
 * @param context 
 */
void stack_traverse(stack_t* stack,bool stack_do(t_elem_1,void*),void* context){
  if(stack == NULL){
    printf("stack pointer is null(8)");
    exit(EXIT_FAILURE);  
  }  
  if(!stack_isempty(stack) && stack_do(top(stack),context)){
    t_elem_1 auxiliar = pop(stack);
    stack_traverse(stack,stack_do,context);
    push(stack,auxiliar);  
  }
}

