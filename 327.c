/*int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    
}*/
typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    long value;
    Color color;
    struct RBNode *leftChild, *rightChild, *parent;
    int size; // subtree size for counting
} RBNode;

RBNode *treeRoot = NULL;

// ---------------- Create new node ----------------
RBNode* createNewNode(long value) {
    RBNode* newNode = (RBNode*)malloc(sizeof(RBNode));
    newNode->value = value;
    newNode->color = RED;
    newNode->leftChild = newNode->rightChild = newNode->parent = NULL;
    newNode->size = 1;
    return newNode;
}

int getSize(RBNode* node) {
    return node ? node->size : 0;
}

void updateSize(RBNode* node) {
    if (node) {
        node->size = getSize(node->leftChild) + getSize(node->rightChild) + 1;
    }
}

// ---------------- Rotations ----------------
void leftRotate(RBNode* x) {
    RBNode* y = x->rightChild;
    x->rightChild = y->leftChild;
    if (y->leftChild) y->leftChild->parent = x;
    y->parent = x->parent;
    if (!x->parent) treeRoot = y;
    else if (x == x->parent->leftChild) x->parent->leftChild = y;
    else x->parent->rightChild = y;
    y->leftChild = x;
    x->parent = y;

    updateSize(x);
    updateSize(y);
}

void rightRotate(RBNode* y) {
    RBNode* x = y->leftChild;
    y->leftChild = x->rightChild;
    if (x->rightChild) x->rightChild->parent = y;
    x->parent = y->parent;
    if (!y->parent) treeRoot = x;
    else if (y == y->parent->leftChild) y->parent->leftChild = x;
    else y->parent->rightChild = x;
    x->rightChild = y;
    y->parent = x;

    updateSize(y);
    updateSize(x);
}

// ---------------- Fix Insert ----------------
void fixInsert(RBNode* z) {
    while (z->parent && z->parent->color == RED) {
        RBNode* gp = z->parent->parent;
        if (z->parent == gp->leftChild) {
            RBNode* y = gp->rightChild;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->rightChild) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                rightRotate(gp);
            }
        } else {
            RBNode* y = gp->leftChild;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->leftChild) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                leftRotate(gp);
            }
        }
    }
    treeRoot->color = BLACK;
}

// ---------------- Insert ----------------
void insert(long value) {
    RBNode *z = createNewNode(value);
    RBNode *y = NULL, *x = treeRoot;
    while (x) {
        y = x;
        if (z->value < x->value) x = x->leftChild;
        else x = x->rightChild;
    }
    z->parent = y;
    if (!y) treeRoot = z;
    else if (z->value < y->value) y->leftChild = z;
    else y->rightChild = z;

    // update size on the path up
    RBNode* cur = z->parent;
    while (cur) {
        updateSize(cur);
        cur = cur->parent;
    }

    fixInsert(z);
}

// ---------------- Count ≤ value ----------------
int countLessEqual(RBNode* node, long value) {
    if (!node) return 0;
    if (value < node->value) {
        return countLessEqual(node->leftChild, value);
    } else {
        return getSize(node->leftChild) + 1 + countLessEqual(node->rightChild, value);
    }
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    treeRoot = NULL;
    long prefix = 0;
    int count = 0;

    insert(0); // base prefix

    for (int i = 0; i < numsSize; i++) {
        prefix += nums[i];
        int right = countLessEqual(treeRoot, prefix - lower);
        int left = countLessEqual(treeRoot, prefix - upper - 1);
        count += (right - left);
        insert(prefix);
    }
    return count;
}