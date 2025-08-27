typedef struct {
int *mid;// *memory
int size;
} Allocator;


Allocator* allocatorCreate(int n) {
    Allocator *obj = malloc(sizeof(Allocator));
    if(!obj)
    return NULL;

    obj->mid=malloc(n*sizeof(int));
    if(!obj->mid)
    {
        free(obj);
        return NULL;
    }

    obj->size=n;
    for(int i=0;i<n;i++)
    {
        obj->mid[i]=-1; //initializing to free
    }
    return obj;
}


int allocatorAllocate(Allocator* obj, int size, int mID) {
    int start=-1,count=0;
    for(int i=0;i<obj->size;i++)
    {
        if(obj->mid[i]==-1)
        {
            if(count==0)
            {
                start=i;
            }
            count++;
            if(count==size)
            {
                for(int j=start;j<start+size;j++)
                {
                    obj->mid[j]=mID;
                }
                return start;
            }
        }
        else
        {
            count = 0;
        }
    }
    return -1;
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int freed=0;
    for(int i=0;i<obj->size;i++)
    {
        if(obj->mid[i]==mID)
        {
            obj->mid[i]=-1;
            freed++;
        }
    }
    return freed;
}

void allocatorFree(Allocator* obj) {
    free(obj->mid);
    free(obj);
}

/**
 * Your Allocator struct will be instantiated and called as such:
 * Allocator* obj = allocatorCreate(n);
 * int param_1 = allocatorAllocate(obj, size, mID);
 
 * int param_2 = allocatorFreeMemory(obj, mID);
 
 * allocatorFree(obj);
*/