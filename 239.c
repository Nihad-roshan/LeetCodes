/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) 
{
    if(numsSize==0||k==0){
        *returnSize=0;
        return NULL;
    }
    *returnSize=numsSize-k+1;
    int* result=(int*)malloc((*returnSize)*sizeof(int));
    int* deque=(int*)malloc(numsSize*sizeof(int));
    int front=0,back=0;
    for(int i=0;i<numsSize;i++)
    {
        if(front<back&&deque[front]<=i-k)
            front++;
        while(front<back&&nums[deque[back-1]]<=nums[i])
            back--;
        deque[back++]=i;
        if(i>=k-1)
            result[i-k+1]=nums[deque[front]];
    }
    free(deque);
    return result;


}
