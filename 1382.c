/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

 struct TreeNode* newnode(int val)
 {
    struct TreeNode *node=malloc(sizeof(struct TreeNode));
    node->val=val;
    node->left=NULL;
    node->right=NULL;
    return node;
 }
void inorder(struct TreeNode* root,int *arr,int *n)
{//storing values in array
    if(!root) return;

    inorder(root->left,arr,n);
    arr[(*n)++]=root->val;
    inorder(root->right,arr,n);
}
struct TreeNode *build(int *arr,int left,int right)
{
    if(left>right) return NULL;
    int mid=(left+right)/2;
    struct TreeNode *root=newnode(arr[mid]);
    root->left=build(arr,left,mid-1);
    root->right=build(arr,mid+1,right);
    return root;
}
struct TreeNode* balanceBST(struct TreeNode* root) {
    int arr[10000],n=0;
    inorder(root,arr,&n);
    return build(arr,0,n-1); //building balanced BST
}