#include <stdlib.h>
#include <stdio.h>

typedef struct Avl_Node_struct{
    int key;

    struct Avl_Node_struct *left;
    struct Avl_Node_struct *right;

    int height;
    int rooted;

}AVL_Node;