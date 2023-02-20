#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary_tree_node.h"
#include "stack.h"

btn_t* btn_int(int amount_of_nodes);
void btn_intTostring(btn_t* node, char* string);
void btn_do_addition(btn_t* node,void* context);
bool even_node_check(btn_t* node);
bool tree_of_even(btn_t* root);
void mirror_tree(btn_t** root);
void btn_doPrintfElem(btn_t* node,void* ctx);
void btn_doAddToStack(btn_t* node, void* context);
void stack_printf(stack_t* stck, void (*print_elem)(t_elem));
void print_telem(t_elem value);
btn_t* mirror_tree_creation(btn_t* root);

int compare(t_elem one,t_elem two);
int main(void){
  btn_t* root = btn_int(15);
  btn_t* root_mirror = NULL;
  stack_t* stack_in = stack_new(15);
  stack_t* stack_pre = stack_new(15);
  stack_t* stack_post = stack_new(15);
  int addition = 0;
  
  //print the tree
  btn_print(root,btn_intTostring);
  
  //mirror tree
  mirror_tree(&root);
  
  //print the tree again
  printf("\n\n");
  btn_print(root,btn_intTostring);

  //creation of a new mirror tree
  root_mirror = mirror_tree_creation(root);
  
  //print the new tree
  printf("\n\n");
  btn_print(root_mirror,btn_intTostring);

  //addition of all elements
  printf("\n\n");
  btn_inorder(root,btn_do_addition,&addition);
  printf("the addition of all elements : %i",addition);
  
  //impression inorder postorder preorder
  
  printf("\nelements inorder:\n");
  btn_inorder(root,btn_doAddToStack,stack_in);
  stack_printf(stack_in,print_telem);
  
  printf("\nelements preorder:\n");
  btn_preorder(root,btn_doAddToStack,stack_pre);
  stack_printf(stack_pre,print_telem);
  
  printf("\nelements postorder:\n");
  btn_postorder(root,btn_doAddToStack,stack_post);
  stack_printf(stack_post,print_telem);
   
  //free all the memory used.
  btn_free(&root);
  btn_free(&root_mirror);
  stack_free(&stack_in);
  stack_free(&stack_pre);
  stack_free(&stack_post);
  return 0;    
}
//****************Examples of application************************//

/**
 * @brief auxiliar function to compare elements.
 * 
 * @param one 
 * @param two 
 * @return int 
 */
int compare(t_elem one,t_elem two){
  return one-two;  
}

/**
 * @brief create a new tree of ints with the specified amoun of nodes.
 * 
 * @param amount_of_nodes 
 * @return btn_t* 
 */
btn_t* btn_int(int amount_of_nodes){
  btn_t* root = NULL;
  srand(time(NULL));
  for(int i=0;i<amount_of_nodes;i++){
    btn_insert_value(&root,rand()%20);          
  }
  return root;
}

/**
 * @brief auxiliar procedure to use the routes inorder, preorder and postorder.
 * 
 * @param node 
 * @param ctx 
 */
void btn_doPrintfElem(btn_t* node,void* ctx){
  printf("%i ",btn_get_value(node));  
}

/**
 * @brief auxiliar procedure to print an element.
 * 
 * @param value 
 */
void print_telem(t_elem value){
  printf("%i ",value);  
}

/**
 * @brief auxiliar procedure to use the routes inorder, preorder and postorder.
 * 
 * @param node 
 * @param string 
 */
void btn_intTostring(btn_t* node, char* string){
  if(node==NULL){
    printf("btn node is NULL");
    return;  
  }
  sprintf(string,"(%03d)",btn_get_value(node));  
} 

/**
 * @brief addition of all elements of a tree.
 * 
 * @param node 
 * @param context 
 */
void btn_do_addition(btn_t* node,void* context){
  if(node!=NULL){
    *(int*)context += btn_get_value(node);  
  }  
}

/**
 * @brief Return true if the int element is even and false otherwise.
 * 
 * @param node 
 * @return true 
 * @return false 
 */
bool even_node_check(btn_t* node){
  bool returned = true;
  if(btn_get_value(node)%2!=0){
    returned = false;  
  }
  return returned; 
}

/**
 * @brief Return true if all int elements in a tree are even and false otherwise.
 * 
 * @param root 
 * @return true 
 * @return false 
 */
bool tree_of_even(btn_t* root){
  return (root == NULL)||((even_node_check(root))&&(tree_of_even(btn_get_left_child(root)))&&(tree_of_even(btn_get_right_child(root))));  
}


/**
 * @brief procedure to get the mirror of the tree.
 * 
 * @param root 
 */
void mirror_tree(btn_t** root){
  if(*root != NULL){
    mirror_tree(btn_get_left_child_reference(*root));
    mirror_tree(btn_get_right_child_reference(*root));
    btn_t* auxiliar = btn_get_left_child(*root);
    btn_left_child_assign(root,btn_get_right_child(*root));
    btn_right_child_assign(root,auxiliar);
  }    
}

/**
 * @brief create a mirror tree of the specified tree.
 * 
 * @param root 
 * @return btn_t* 
 */
btn_t* mirror_tree_creation(btn_t* root){
  btn_t* new_node = NULL;
  if(root!=NULL){
    new_node = btn_new(btn_get_value(root));
    btn_right_child_assign(&new_node,mirror_tree_creation(btn_get_left_child(root)));
    btn_left_child_assign(&new_node,mirror_tree_creation(btn_get_right_child(root)));  
  }
  return new_node;    
}


/**
 * @brief procedure to use the routes inorder, preorder and postorder.
 * 
 * @param node 
 * @param context 
 */
void btn_doAddToStack(btn_t* node, void* context){
  if(context != NULL){
    context = (stack_t*)context;
    push(context,node);  
  }  
}

/**
 * @brief print a stack.
 * 
 * @param stck 
 * @param print_elem 
 */
void stack_printf(stack_t* stck, void (*print_elem)(t_elem)){
  if(!stack_isempty(stck)){
    btn_t* auxiliar = pop(stck);
    print_elem(btn_get_value(auxiliar));
    stack_printf(stck,print_elem);
    push(stck,auxiliar); 
  }    
}
