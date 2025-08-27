int firstUniqChar(char* s) {

    int hash[26]={0};
    int size=strlen(s);

    for(int i=0;i<size;i++)
    {
        hash[s[i]-'a']++;
    }

    for(int i=0;i<size;i++)
    {
        if(hash[s[i]-'a']==1)
        return i;
    }
    return -1;

    
    
    
}