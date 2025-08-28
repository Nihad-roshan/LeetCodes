#define HASH_SIZE 2003 // larger prime bucket for fewer collisions

typedef struct Node{
    char* key;     // signature
    char** group;  // array of strings
    int size;      // number of strings
    int cap;       // capacity
    struct Node* next;
}Node;

unsigned long hashFunc(const char* s){
    unsigned long h=0;
    while(*s) h=h*131+*s++;
    return h%HASH_SIZE;
}

// Create a key from character counts instead of sorting
char* buildKey(char* s){
    int count[26]={0};
    for(int i=0;s[i];i++)count[s[i]-'a']++;
    // Build key string "c1#c2#c3..."
    char buf[128]; // enough since sum(count)<=100
    char* p=buf;
    for(int i=0;i<26;i++)p+=sprintf(p,"%d#",count[i]);
    return strdup(buf);
}

char*** groupAnagrams(char** strs,int strsSize,int* returnSize,int** returnColumnSizes)
{
    Node* table[HASH_SIZE]={0};
    for(int i=0;i<strsSize;i++)
    {
        char* key=buildKey(strs[i]);
        unsigned long h=hashFunc(key);
        Node* cur=table[h];

        while(cur&&strcmp(cur->key,key)!=0)
        cur=cur->next;

        if(!cur)
        {
            cur=(Node*)malloc(sizeof(Node));
            cur->key=key;
            cur->cap=4;
            cur->size=0;
            cur->group=(char**)malloc(cur->cap*sizeof(char*));
            cur->next=table[h];
            table[h]=cur;
        }
        else 
        free(key);

        if(cur->size==cur->cap)
        {
            cur->cap*=2;
            cur->group=(char**)realloc(cur->group,cur->cap*sizeof(char*));
        }
        cur->group[cur->size++]=strs[i];
    }

    // Count groups
    int count=0;
    for(int i=0;i<HASH_SIZE;i++){
        Node* cur=table[i];
        while(cur)
        {
            count++;
            cur=cur->next;
        }
    }
    *returnSize=count;
    *returnColumnSizes=(int*)malloc(count*sizeof(int));
    char*** result=(char***)malloc(count*sizeof(char**));

    int idx=0;
    for(int i=0;i<HASH_SIZE;i++)
    {
        Node* cur=table[i];
        while(cur)
        {
            result[idx]=cur->group;
            (*returnColumnSizes)[idx]=cur->size;
            idx++;
            cur=cur->next;
        }
    }
    return result;
}