/**
 * Note: The returned array must be malloced, assume caller calls free().
 
int* countSmaller(int* nums, int numsSize, int* returnSize) {
    
}*/ 
#include <stdio.h>
#include <stdlib.h>

typedef struct AVL {
    int key;
    int height;
    int size;     // size of subtree rooted here
    struct AVL *left, *right;
} AVL;

// Utility
int max(int a,int b){ return (a>b)?a:b; }

AVL* createnode(int key){
    AVL* node=(AVL*)malloc(sizeof(AVL));
    node->key=key;
    node->left=node->right=NULL;
    node->height=1;
    node->size=1;
    return node;
}

int getheight(AVL* n){ return (n? n->height:0); }
int getsize(AVL* n){ return (n? n->size:0); }

void update(AVL* n){
    if(n){
        n->height=1+max(getheight(n->left),getheight(n->right));
        n->size=1+getsize(n->left)+getsize(n->right);
    }
}

int getbalance(AVL* n){ return (n? getheight(n->left)-getheight(n->right):0); }

AVL* rightrotate(AVL* y){
    AVL* x=y->left;
    AVL* T2=x->right;
    x->right=y;
    y->left=T2;
    update(y); update(x);
    return x;
}

AVL* leftrotate(AVL* x){
    AVL* y=x->right;
    AVL* T2=y->left;
    y->left=x;
    x->right=T2;
    update(x); update(y);
    return y;
}

// Insert with count of smaller numbers
AVL* insertCount(AVL* root,int key,int* countSmaller){
    if(root==NULL) return createnode(key);

    if(key <= root->key){
        root->left = insertCount(root->left,key,countSmaller);
    } else {
        *countSmaller += getsize(root->left)+1; // left subtree + root
        root->right = insertCount(root->right,key,countSmaller);
    }

    update(root);

    int balance=getbalance(root);
    if(balance>1 && key<root->left->key) return rightrotate(root);
    if(balance<-1 && key>root->right->key) return leftrotate(root);
    if(balance>1 && key>root->left->key){
        root->left=leftrotate(root->left);
        return rightrotate(root);
    }
    if(balance<-1 && key<root->right->key){
        root->right=rightrotate(root->right);
        return leftrotate(root);
    }
    return root;
}

// Main LeetCode function
int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* counts = (int*)malloc(numsSize * sizeof(int));
    if(numsSize==0) return counts;

    AVL* root=NULL;

    // Traverse from right to left
    for(int i=numsSize-1;i>=0;i--){
        int smaller=0;
        root=insertCount(root,nums[i],&smaller);
        counts[i]=smaller;
    }
    return counts;
}