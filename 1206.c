
#define MAX_LEVEL 32
#define P_FACTOR 0.5

typedef struct SkiplistNode {
    int key;
    int level;
    struct SkiplistNode **forward;
} SkiplistNode;

typedef struct Skiplist {
    int level;
    SkiplistNode *header;
} Skiplist;

int randLevel() {
    int level = 1;
    while (((double)rand() / RAND_MAX) < P_FACTOR && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

SkiplistNode *createNode(int key, int level) {
    SkiplistNode *node = malloc(sizeof(SkiplistNode));
    node->key = key;
    node->level = level;
    node->forward = calloc(level, sizeof(SkiplistNode *));
    return node;
}

Skiplist* skiplistCreate() {
    Skiplist *list = malloc(sizeof(Skiplist));
    list->level = 1;
    list->header = createNode(-1, MAX_LEVEL);
    return list;
}

bool skiplistSearch(Skiplist* obj, int target) {
    SkiplistNode *current = obj->header;
    for (int i = obj->level - 1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < target) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    return (current && current->key == target);
}

void skiplistAdd(Skiplist* obj, int num) {
    SkiplistNode *update[MAX_LEVEL];
    SkiplistNode *current = obj->header;

    for (int i = obj->level - 1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < num) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    int newLevel = randLevel();
    if (newLevel > obj->level) {
        for (int i = obj->level; i < newLevel; i++) {
            update[i] = obj->header;
        }
        obj->level = newLevel;
    }

    SkiplistNode *node = createNode(num, newLevel);
    for (int i = 0; i < newLevel; i++) {
        node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = node;
    }
}

bool skiplistErase(Skiplist* obj, int num) {
    SkiplistNode* update[MAX_LEVEL];
    SkiplistNode* cur = obj->header;

    for (int lvl = obj->level - 1; lvl >= 0; lvl--) {
        while (cur->forward[lvl] && cur->forward[lvl]->key < num)
            cur = cur->forward[lvl];
        update[lvl] = cur;
    }

    cur = cur->forward[0];
    if (!cur || cur->key != num) return false;

    for (int i = 0; i < obj->level; i++) {
        if (update[i]->forward[i] == cur)
            update[i]->forward[i] = cur->forward[i];
    }

    while (obj->level > 1 && obj->header->forward[obj->level - 1] == NULL)
        obj->level--;

    free(cur->forward);
    free(cur);

    return true;
}

void skiplistFree(Skiplist* obj) {
    SkiplistNode* cur = obj->header->forward[0];
    while (cur) {
        SkiplistNode* nxt = cur->forward[0];
        free(cur->forward);
        free(cur);
        cur = nxt;
    }
    free(obj->header->forward);
    free(obj->header);
    free(obj);
}


/**
 * Your Skiplist struct will be instantiated and called as such:
 * Skiplist* obj = skiplistCreate();
 * bool param_1 = skiplistSearch(obj, target);
 
 * skiplistAdd(obj, num);
 
 * bool param_3 = skiplistErase(obj, num);
 
 * skiplistFree(obj);
*/