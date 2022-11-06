#include <stdio.h>
#include <stdlib.h>

struct node {

    int data;
    int color;
    struct node* parent;
    struct node* left;
    struct node* right;
};

void rightRotate(struct node* temp);


struct node* root = NULL;

struct node* insert(struct node* trav, struct node* temp){

    if(trav == NULL){
        return temp;
    }

    if(temp->data < trav->data){
        trav->left = insert(trav->left, temp);
        trav->left->parent = trav;
    }
    else if(temp->data > trav->data){
        trav->right = insert(trav->right, temp);
        trav->right->parent = trav;
    }

    return trav;

}

void rightrotate(struct node* temp){
    struct node* left = temp->left;
    temp->left = left->right;
    if(temp->left)
        temp->left->parent = temp;
        left->parent = temp->parent;
    if(!temp->parent)
        root = left;
    else if( temp == temp->parent->left)
        temp->parent->left = left;
    else 
        temp->parent->right = left;
        left->right = temp;
        temp->parent = left;
    
    
}

void leftrotate(struct node* temp)
{
    struct node* right = temp->right;
    temp->right = right->left;
    if (temp->right)
        temp->right->parent = temp;
    right->parent = temp->parent;
    if (!temp->parent)
        root = right;
    else if (temp == temp->parent->left)
        temp->parent->left = right;
    else
        temp->parent->right = right;
    right->left = temp;
    temp->parent = right;
}
 

 void fixup(struct node* root, struct node* pt)
{
    struct node* parent_pt = NULL;
    struct node* grand_parent_pt = NULL;
 
    while ((pt != root) && (pt->color != 0)
           && (pt->parent->color == 1))
    {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
 
        
        if (parent_pt == grand_parent_pt->left)
        {
 
            struct node* uncle_pt = grand_parent_pt->right;
 
            /* Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == 1)
            {
                grand_parent_pt->color = 1;
                parent_pt->color = 0;
                uncle_pt->color = 0;
                pt = grand_parent_pt;
            }
 
            else {
 
                /* Case : 2
                     pt is right child of its parent
                     Left-rotation required */
                if (pt == parent_pt->right) {
                    leftrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
 
                /* Case : 3
                     pt is left child of its parent
                     Right-rotation required */
                rightrotate(grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = t;
                pt = parent_pt;
            }
        }
 
        /* Case : B
             Parent of pt is right
             child of Grand-parent of
           pt */
        else {
            struct node* uncle_pt = grand_parent_pt->left;
 
            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == 1))
            {
                grand_parent_pt->color = 1;
                parent_pt->color = 0;
                uncle_pt->color = 0;
                pt = grand_parent_pt;
            }
            else {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->left) {
                    rightrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
 
                /* Case : 3
                     pt is right child of its parent
                     Left-rotation required */
                leftrotate(grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = t;
                pt = parent_pt;
            }
        }
    }
 
    root->color = 0;
}
 
// Function to print inorder traversal
// of the fixated tree
void inorder(struct node* trav)
{
    if (trav == NULL)
        return;
    inorder(trav->left);
    printf("%d ", trav->data);
    inorder(trav->right);
}

int main()
{
    int n = 5;
    int a[5] = {5, 4, 3, 2, 1 };
 /*
  struct node* temp
            = (struct node*)malloc(sizeof(struct node));
        temp->right = NULL;
        temp->left = NULL;
        temp->parent = NULL;
        temp->data = 1;
        temp->color = 1;
*/
        /*struct node* temp1
            = (struct node*)malloc(sizeof(struct node));
            
        temp1->right = NULL;
        temp1->left = NULL;
        temp1->parent = NULL;
        */
       // temp->data = 2;
        //temp->color = 1;

        /*struct node* temp2
            = (struct node*)malloc(sizeof(struct node));
        temp2->right = NULL;
        temp2->left = NULL;
        temp2->parent = NULL;*/
        //temp->data = 3;
        //temp2->color = 1;
/*
    root = insert(root, temp);
     root = insert(root, temp);
      root = insert(root, temp);

 */
    for (int i = 0; i < n; i++) {
 
        // allocating memory to the node and initializing:
        // 1. color as red
        // 2. parent, left and right pointers as NULL
        // 3. data as i-th value in the array
        struct node* temp
            = (struct node*)malloc(sizeof(struct node));
        temp->right = NULL;
        temp->left = NULL;
        temp->parent = NULL;
        temp->data = a[i];
        temp->color = 1;
 
        // calling function that performs bst insertion of
        // this newly created node
        root = insert(root, temp);
 
        // calling function to preserve properties of rb
        // tree
        fixup(root, temp);
    }
 
//fixup(root, temp);
    printf("Inorder Traversal of Created Tree\n");
    inorder(root);
 
    return 0;
}
 