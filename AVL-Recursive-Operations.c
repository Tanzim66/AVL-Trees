#include "AVL-Nodes.c"

AVL_Node *create_new_AVL_node(int key){
    AVL_Node *newNode = NULL;
    newNode = (AVL_Node *)(calloc(1, sizeof(AVL_Node)));
    if(newNode != NULL){
        newNode -> key = key;
        newNode -> left = NULL;
        newNode -> right = NULL;
        newNode -> height = 1;
        newNode -> rooted = 0;
    }
    return newNode;
}

int get_height(AVL_Node *node){
    int height = 1;  
    if(node -> left == NULL && node -> right == NULL)  
        return height;  
    if(node -> right != NULL)  
        height = node -> right -> height;  
    if(node -> left != NULL){  
        if(height < node -> left -> height)  
            height = node -> left -> height;  
    }  
     return height+1;  
}

int get_balance_factor(AVL_Node *node){
    int left_height = 0;
    int right_height = 0;
    if(node -> left != NULL){
        left_height = node -> left -> height;
    }
    if(node -> right != NULL){
        right_height = node -> right -> height;
    }
    return left_height - right_height;
}

int get_num_nodes_rooted(AVL_Node *node){
    int total = 0;
    if(node -> right != NULL){
        total += node -> right -> rooted+1;
    }
    if(node -> left != NULL){
        total += node -> left -> rooted+1;
    }
    return total;
}

AVL_Node *rotate_right(AVL_Node *node){
    AVL_Node *left_subtree = node -> left;
    node -> left = left_subtree -> right;
    left_subtree -> right = node;

    node -> height = get_height(node);
    left_subtree -> height = get_height(left_subtree);

    node -> rooted =  get_num_nodes_rooted(node);
    left_subtree -> rooted = get_num_nodes_rooted(left_subtree);

    return left_subtree;

}

AVL_Node *rotate_left(AVL_Node *node){
    AVL_Node *right_subtree = node -> right;
    node -> right = right_subtree -> left;
    right_subtree -> left = node;

    node -> height = get_height(node);
    right_subtree -> height = get_height(right_subtree);

    node -> rooted = get_num_nodes_rooted(node);
    right_subtree -> rooted = get_num_nodes_rooted(node);

    return right_subtree;
}

AVL_Node *balance_node(AVL_Node *node){
    int balance_factor = get_balance_factor(node);

    if(balance_factor > 1){
        int second_balanceFactor = get_balance_factor(node -> left);
        if(second_balanceFactor >= 0){
            node = rotate_right(node);
        }
        else{
            node -> left = rotate_left(node -> left);
            node = rotate_right(node);
        }
    }   
    else if(balance_factor < -1){
        int second_balanceFactor = get_balance_factor(node -> right);
        if(second_balanceFactor <= 0){
            node = rotate_left(node);
        }
        else{
            node -> right = rotate_right(node -> right);
            node = rotate_left(node);
        }
    }
    return node;
}

AVL_Node *insert_key(AVL_Node *root, int key){
    if(root == NULL)
        return create_new_AVL_node(key);
    else if(root -> key > key){
        root -> left = insert_key(root -> left, key);
    }
    else{
        root -> right = insert_key(root -> right, key);
    }
    root -> rooted = get_num_nodes_rooted(root);
    root -> height = get_height(root);
    root = balance_node(root);
    
    return root;
}

int rank(AVL_Node *root, int key){
    if(root -> key == key){
        int total = 1;
        if(root -> left != NULL){
            total += root -> left -> rooted + 1;
        }
        return total;
    }
    if(root -> key > key){
        return rank(root -> left, key);
    }
    else{
        int total = 1;
        if(root -> left != NULL){
            total += root -> left -> rooted + 1;
        }
        return total + rank(root -> right, key);
    }
}

AVL_Node *search(AVL_Node *root, int key){
    if(root == NULL)
        return NULL;
    else if(root -> key == key)
        return root;
    else if(root -> key > key)
        return search(root -> left, key);
    else
        return search(root -> right, key);
}

int get_left_most_key(AVL_Node *node){
    while(node -> left != NULL){
        node = node -> left;
    }
    return node -> key;
}


AVL_Node *delete(AVL_Node *root, int key){
    if(root == NULL){
        return NULL;
    }
    else if(root -> key == key){
        if(root -> right == NULL && root -> left == NULL){
            free(root);
            return NULL;
        }
        else if(root -> right != NULL && root -> left != NULL){
            int successor = get_left_most_key(root -> right);
            root -> right = delete(root -> right, successor);
            AVL_Node *newNode = create_new_AVL_node(successor);
            newNode -> right = root -> right;
            newNode -> left = root -> left;
            newNode -> rooted = get_num_nodes_rooted(newNode);
            newNode -> height = get_height(newNode);
            newNode = balance_node(newNode);
            free(root);
            return newNode;

        }
        else if(root -> right != NULL){
            AVL_Node *temp = root -> right;
            free(root);
            return temp;
        }
        else if(root -> left != NULL){
            AVL_Node *temp = root -> left;
            free(root);
            return temp;
        }
    }
    else if(root -> key > key){
        root -> left = delete(root -> left, key);
    }
    else{
        root -> right = delete(root -> right, key);
    }
    root -> rooted = get_num_nodes_rooted(root);
    root -> height = get_height(root);
    root = balance_node(root);
    return root;
}