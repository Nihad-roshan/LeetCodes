/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

 void inorder(struct TreeNode *root,int *arr,int *id)
 {
    if(root==NULL) return;
    inorder(root->left,arr,id);
    arr[(*id)++]=root->val;
    inorder(root->right,arr,id);
 }
int* inorderTraversal(struct TreeNode* root, int* returnSize) {

    int capacity=1000;
    int *result=(int*)malloc(sizeof(int)*capacity);

    *returnSize=0; //initially

    inorder(root,result,returnSize);

    return result;
}