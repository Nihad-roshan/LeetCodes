/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
 #include <stdbool.h>

 long prev;
 bool isvalid;

 bool inorder(struct TreeNode *root)
 {
    //if(!isvalid || !root) return;
    if(root == NULL) return true;

    if(!inorder(root->left)) return false; //First, go all the way left.

    //checking current node
    if(!isvalid && root->val<=prev) return false;
    
    isvalid=false;
    prev=root->val;

    return inorder(root->right);


 }

bool isValidBST(struct TreeNode* root) {
    if(root==NULL) return false;

    prev=-999;
    isvalid=true;

    return inorder(root);
}