#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binary_tree_node.h"
#include "stack.h"

/**
 * @brief create a new binary tree node.
 * 
 * @param value 
 * @return btn_t* 
 */
btn_t* btn_new(t_elem value){
  btn_t* new_node = (btn_t*)malloc(sizeof(btn_t));
  if(new_node==NULL){
    printf("memory cannot be reserved for a btn new node\n");
    exit(EXIT_FAILURE);
  }
  new_node->value=value;
  new_node->left=NULL;
  new_node->right=NULL;
  return new_node;
}

/**
 * @brief free the memory of a node.
 * 
 * @param node 
 */
void btn_free(btn_t** node){
  if(node!= NULL && *node!=NULL){
    btn_free(&(*node)->left);
    btn_free(&(*node)->right);
    free(*node);
    *node = NULL;
  }
}

/**
 * @brief get the element of a node.
 * 
 * @param node 
 * @return t_elem 
 */
t_elem btn_get_value(btn_t* node){
  if(node == NULL){
    printf("btn node is NULL(1)");
    exit(EXIT_FAILURE);
  }
  return node->value;
}

/**
 * @brief get the left child of a node.
 * 
 * @param node 
 * @return btn_t* 
 */
btn_t* btn_get_left_child(btn_t* node){
  if(node == NULL){
    printf("btn node is NULL(2)");
    exit(EXIT_FAILURE);
  }
  return node->left;
}

/**
 * @brief get the right child of a node.
 * 
 * @param node 
 * @return btn_t* 
 */
btn_t* btn_get_right_child(btn_t* node){
  if(node == NULL){
    printf("btn node is NULL(3)");
    exit(EXIT_FAILURE);
  }
  return node->right;
}

/**
 * @brief get the reference of a left child of a node.
 * 
 * @param node 
 * @return btn_t** 
 */
btn_t** btn_get_left_child_reference(btn_t* node){
  if(node == NULL){
    printf("btn node is NULL(4)");
    exit(EXIT_FAILURE);
  }
  return &node->left;
}

/**
 * @brief get the reference of the right child of a node.
 * 
 * @param node 
 * @return btn_t** 
 */
btn_t** btn_get_right_child_reference(btn_t* node){
  if(node == NULL){
    printf("btn node is NULL(5)");
    exit(EXIT_FAILURE);
  }
  return &node->right;
}

/**
 * @brief return true if the node is leaf and false otherwise.
 * 
 * @param node 
 * @return true 
 * @return false 
 */
bool btn_isLeaf(btn_t* node){
  if(node == NULL){
    printf("btn node is NULL(6)");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if((node->left == NULL) && (node->right == NULL)){
    returned = true;
  }
  return returned;
}

/**
 * @brief return the amount of nodes attached to the specified node.
 * 
 * @param node 
 * @return int 
 */
int btn_count(btn_t* node){
  int result = 0;
  if(node != NULL) {
    result = 1 + btn_count(node->left) + btn_count(node->right);
  }
  return result;
}

/**
 * @brief search a element in a tree node. Return the reference if the element exist and NULL otherwise.
 * 
 * @param root 
 * @param value 
 * @param compare 
 * @return btn_t** 
 */
btn_t** btn_find(btn_t** root, t_elem value, int (*compare)(t_elem, t_elem)){
  if(root == NULL){
    printf("btn node double pointer is NULL(1)");
    exit(EXIT_FAILURE);
  }
  btn_t** returned = NULL;
  if(*root!=NULL && compare(btn_get_value(*root),value)!=0){
    returned = btn_find(&(*root)->left,value,compare);
    if(returned == NULL){
      returned = btn_find(&(*root)->right,value,compare);
    }
  }
  else{
    if(*root == NULL){
      returned = NULL;
    }
    else{
      returned = root;
    }
  }
  return returned;
}

/**
 * @brief insert a node in a tree in a balanced form.
 * 
 * @param root 
 * @param new_node 
 */
void btn_insert(btn_t** root,btn_t* new_node){
  if(root == NULL){
    printf("btn node double pointer is NULL(2)");
    exit(EXIT_FAILURE);
  }
  if(*root == NULL){
    *root = new_node;
  }
  else{
    if(btn_count((*root)->left)<=btn_count((*root)->right)){
      btn_insert(&(*root)->left,new_node);
    }
    else{
      btn_insert(&(*root)->right,new_node);
    }
  }
}

/**
 * @brief insert a value in a tree. Procedure that uses btn_insert.
 * 
 * @param root 
 * @param value 
 */
void btn_insert_value(btn_t** root,t_elem value){
  if(root == NULL){
    printf("btn node double pointer is NULL(3)");
    exit(EXIT_FAILURE);
  }
  btn_t* new_node = btn_new(value);
  btn_insert(root,new_node);
}


/**
 * @brief auxiliar function in btn_level.
 * 
 * @param node 
 * @param value 
 * @param level 
 * @param cmp 
 * @return int 
 */
int _btn_level(btn_t* node, t_elem value, int level, int cmp(t_elem, t_elem)){
 int counter = 0;
 if(node == NULL){
   return -1;
 }
 else{
   if(cmp(node->value,value)==0){
     return level;
   }
   else{
     counter = _btn_level(node->left,value,level+1,cmp);
     if(counter!=-1){
       return counter;
     }
     counter = _btn_level(node->right,value,level+1,cmp);
     if(counter!=-1){
       return counter;
     }
     return -1;
   }
 }
}

/**
 * @brief return the level of a tree.
 * 
 * @param root 
 * @param value 
 * @param cmp 
 * @return int 
 */
int btn_level(btn_t* root, t_elem value, int cmp(t_elem, t_elem)){
  int level = 0;
  if(root == NULL){
    return -1;
  }
  else{
    if(cmp(root->value,value)==0){
      return level;
    }
    else{
      int reference = _btn_level(root->left,value,level+1,cmp);
      if(reference==-1){
        reference = _btn_level(root->right,value,level+1,cmp);
      }
      return reference;
    }
  }
}

/**
 * @brief Procedure to traverse a tree inorder using a context variable.
 * 
 * @param node 
 * @param btn_do 
 * @param ctx 
 */
void btn_inorder(btn_t* node,void btn_do(btn_t*, void*),void* ctx){
  if(node!=NULL){
    btn_inorder(node->left,btn_do,ctx);
    btn_do(node,ctx);
    btn_inorder(node->right,btn_do,ctx);
  }
}

/**
 * @brief Procedure to traverse a tree postorder using a context variable.
 * 
 * @param node 
 * @param btn_do 
 * @param ctx 
 */
void btn_postorder(btn_t* node, void btn_do(btn_t*, void*), void* ctx){
  if(node!=NULL){
    btn_postorder(node->left,btn_do,ctx);
    btn_postorder(node->right,btn_do,ctx);
    btn_do(node,ctx);
  }
}

/**
 * @brief Procedure to traverse a tree preorder using a context variable.
 * 
 * @param node 
 * @param btn_do 
 * @param ctx 
 */
void btn_preorder(btn_t* node, void btn_do(btn_t*, void*), void* ctx){
  if(node!=NULL){
    btn_do(node,ctx);
    btn_preorder(node->left,btn_do,ctx);
    btn_preorder(node->right,btn_do,ctx);
  }
}

/**
 * @brief Procedure to traverse a tree inorder using a context variable.Iterative version that uses
 * a stack.
 * 
 * @param root 
 * @param btn_do 
 * @param ctx 
 */
void btn_inorder_iterativeStack(btn_t* root, void btn_do(btn_t*,void*),void* ctx){
  if(root != NULL){
    stack_t* stack= stack_new(100);
    btn_t* auxiliar = root;
    while(auxiliar != NULL || !stack_isempty(stack)){
      while(auxiliar != NULL){
        push(stack,auxiliar);
        auxiliar = btn_get_left_child(auxiliar);
      }
      auxiliar = pop(stack);
      btn_do(auxiliar,ctx);
      auxiliar = btn_get_right_child(auxiliar);
    }
    stack_free(&stack);
  }
}

/**
 * @brief Procedure to traverse a tree postorder using a context variable. Iterative version that uses
 * a stack.
 * 
 * @param root 
 * @param btn_do 
 * @param ctx 
 */
void btn_postorder_iterativeStack(btn_t* root, void btn_do(btn_t*,void*),void* ctx){
  if(root != NULL){
    stack_t* stack_in = stack_new(100);
    stack_t* stack_out = stack_new(100);
    btn_t* auxiliar = root;
    push(stack_in,auxiliar);
    while(!stack_isempty(stack_in)){
      auxiliar = pop(stack_in);
      push(stack_out,auxiliar);
      if(btn_get_left_child(auxiliar)!=NULL){
        push(stack_in,auxiliar);
      }
      if(btn_get_right_child(auxiliar)!=NULL){
        push(stack_in,auxiliar);
      }
    }
    while(!stack_isempty(stack_out)){
      auxiliar = pop(stack_out);
      btn_do(auxiliar,ctx);
    }
    stack_free(&stack_in);
    stack_free(&stack_out);
  }
}

/**
 * @brief Procedure to traverse a tree preorder using a context variable.Iterative version that uses
 * a stack.
 * 
 * @param root 
 * @param btn_do 
 * @param ctx 
 */
void btn_preorder_iterativeStack(btn_t* root, void btn_do(btn_t*,void*),void* ctx){
  if(root != NULL){
    stack_t* stack= stack_new(100);
    btn_t* auxiliar = root;
    while(auxiliar != NULL || !stack_isempty(stack)){
      while(auxiliar != NULL){
        push(stack,auxiliar);
        btn_do(auxiliar,ctx);
        auxiliar = btn_get_left_child(auxiliar);
      }
      auxiliar = pop(stack);
      auxiliar = btn_get_right_child(auxiliar);
    }
    stack_free(&stack);
  }
}

int _max(int a, int b) { return (a > b) ? a : b; }

/**
 * @brief return the height of a node.
 * 
 * @param node 
 * @return int 
 */
int btn_height(btn_t* node) {
  if(node == NULL){
    return -1;
  }
  else{
    return 1+_max(btn_height(node->left),btn_height(node->right));
  }
}

/**
 * @brief auxiliar function to print a tree.
 * 
 * @param tree 
 * @param is_left 
 * @param offset 
 * @param depth 
 * @param s 
 * @param toStr 
 * @return int 
 */
int _btn_print(btn_t* tree, int is_left, int offset, int depth, char s[20][255], void toStr (btn_t*, char*)) {
    char b[200];
    int width = 5;

    if (!tree) return 0;
    toStr(tree, b);
    //sprintf(b, "%s", str);


    int left = _btn_print(tree->left, 1, offset, depth + 1, s, toStr);
    int right = _btn_print(tree->right, 0, offset + left + width, depth + 1, s, toStr);

    // for (int i = 0; i < width; i++) s[2 * depth][offset + left + i] = b[i];
    for (int i = 0; i < strlen(b); i++) s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {
        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

    } else if (depth && !is_left) {
        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset - width / 2 - 1] = '+';
    }

    return left + width + right;
}

/**
 * @brief print a tree using characters. The values must be between 0-999.
 * 
 * @param tree 
 * @param toStr 
 */
void btn_print(btn_t* tree, void toStr (btn_t*, char*)) {
    char s[20][255];
    for (int i = 0; i < 20; i++) sprintf(s[i], "%80s", " ");

    _btn_print(tree, 0, 0, 0, s, toStr);

    for (int i = 0; i < 20; i++) {
        int j = 0;
        while (s[i][j] != '\0' && s[i][j] == ' ') {
            j++;
        }
        if (s[i][j] != '\0') {
            printf("%s\n", s[i]);
        }
    }
}

/**
 * @brief set the left child of a node.
 * 
 * @param root 
 * @param left_child 
 * @return bool
 */
bool btn_left_child_assign(btn_t** root,btn_t* left_child){
  if(root == NULL){
    printf("btn node double pointer is NULL(4)");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(*root != NULL){
    (*root)->left = left_child;
    returned = true;
  }
  return returned;
}

/**
 * @brief set the right child of a node.
 * 
 * @param root 
 * @param right_child 
 * @return bool 
 */
bool btn_right_child_assign(btn_t** root,btn_t* right_child){
  if(root == NULL){
    printf("btn node double pointer is NULL(5)");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(*root != NULL){
    (*root)->right = right_child;
    returned = true;
  }
  return returned;
}

/**
 * @brief set the element of a node.
 * 
 * @param node 
 * @param element 
 */
void btn_setElement(btn_t** node, t_elem element){
  if(node == NULL){
    printf("btn node double pointer is NULL(6)");
    return;
  }
  (*node)->value = element;  
}

