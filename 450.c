/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
 struct TreeNode *max(struct TreeNode *m)
 {
    while(m && m->right)
    {
        m=m->right;
    }
    return m;
 }
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if(root==NULL) return NULL;

    
    
    
    if(key < root->val)
    {
        root->left=deleteNode(root->left,key);
    }
    else if(key > root->val)
    {
        root->right=deleteNode(root->right,key);
    }
    else
    {//found node to delete
        if(root->left == NULL)
        {//only right child
        struct TreeNode *temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {//only left child
        struct TreeNode *temp=root->left;
            free(root);
            return temp;
        }
        struct TreeNode *temp=max(root->left);
        root->val=temp->val;
        root->left=deleteNode(root->left,temp->val);
    }
    return root;
}