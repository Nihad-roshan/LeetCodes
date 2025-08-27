/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode* root) {

    if(root==NULL) return 0;

    int leftdepth=maxDepth(root->left);
    int rightdepth=maxDepth(root->right);

    return (leftdepth>rightdepth ? leftdepth : rightdepth)+1;

    
}