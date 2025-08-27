/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* create(struct ListNode *low,struct ListNode *high)
{
    if(low==high) return NULL;

    struct ListNode *slow=low;
    struct ListNode *fast=low;

    while(fast !=high && fast->next!=high)
    {
        slow=slow->next;
        fast=fast->next->next;
    }

    struct TreeNode *node=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val=slow->val;
    node->left=create(low,slow);
    node->right=create(slow->next,high);

    return node;
}


struct TreeNode* sortedListToBST(struct ListNode* head) {
    if(head==NULL) return NULL;

    struct TreeNode *root=create(head,NULL);

    return root;
}