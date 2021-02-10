#include "AVL-Recursive-Operations.c"

int main(){
    int choice = -1;
    AVL_Node *root = NULL;
    while(choice != 0){
        printf("Enter 0 to exit\nEnter 1 to insert nodes into AVL trees\nEnder 2 to search for the rank of an existng key\nEnter 3 to delete a node\n");
        scanf("%d", &choice);
        if(choice == 1){
            int key = 0;
            int num = 0;
            printf("Enter number of keys to enter:\n");
            scanf("%d", &num);
            printf("Enter keys:\n");
            for(int i=0; i<num; i++){
                scanf("%d", &key);
                root = insert_key(root, key);
            }
            printf("Insert complete\n");
        }
        if(choice == 2){
            int key = 0;
            printf("Enter the key to search for:\n");
            scanf("%d", &key);
            AVL_Node *temp = NULL;
            temp = search(root, key);
            if(temp == NULL)
                printf("The key is not in the tree\n");
            else   
                printf("The rank of the key %d is: %d\n", key, rank(root, key));
        }
        if(choice == 3){
            int key = 0;
            printf("Enter key to delete:\n");
            scanf("%d", &key);
            root = delete(root, key);
        }
    }
    return 0;
}