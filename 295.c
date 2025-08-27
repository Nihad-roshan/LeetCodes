/*typedef struct {
    
} MedianFinder;


MedianFinder* medianFinderCreate() {
    
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    
}

double medianFinderFindMedian(MedianFinder* obj) {
    
}

void medianFinderFree(MedianFinder* obj) {
    
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 
 * double param_2 = medianFinderFindMedian(obj);
 
 * medianFinderFree(obj);
*/

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int value;
    Color color;
    int size; // subtree size
    struct RBNode *leftChild, *rightChild, *parent;
} RBNode;

typedef struct {
    RBNode *root;
} MedianFinder;

// Utility function
int getSize(RBNode *node) {
    return node ? node->size : 0;
}

void updateSize(RBNode *node) {
    if (node) {
        node->size = 1 + getSize(node->leftChild) + getSize(node->rightChild);
    }
}

// Create new node
RBNode* createNewNode(int value) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->value = value;
    node->color = RED;
    node->size = 1;
    node->leftChild = node->rightChild = node->parent = NULL;
    return node;
}

// Left rotate
void rotateLeft(RBNode **root, RBNode *x) {
    RBNode *y = x->rightChild;
    x->rightChild = y->leftChild;
    if (y->leftChild) y->leftChild->parent = x;

    y->parent = x->parent;
    if (!x->parent) *root = y;
    else if (x == x->parent->leftChild) x->parent->leftChild = y;
    else x->parent->rightChild = y;

    y->leftChild = x;
    x->parent = y;

    updateSize(x);
    updateSize(y);
}

// Right rotate
void rotateRight(RBNode **root, RBNode *y) {
    RBNode *x = y->leftChild;
    y->leftChild = x->rightChild;
    if (x->rightChild) x->rightChild->parent = y;

    x->parent = y->parent;
    if (!y->parent) *root = x;
    else if (y == y->parent->leftChild) y->parent->leftChild = x;
    else y->parent->rightChild = x;

    x->rightChild = y;
    y->parent = x;

    updateSize(y);
    updateSize(x);
}

// Fix violations
void fixViolations(RBNode **root, RBNode *z) {
    while (z->parent && z->parent->color == RED) {
        RBNode *parent = z->parent;
        RBNode *grandparent = parent->parent;
        if (!grandparent) break;

        if (parent == grandparent->leftChild) {
            RBNode *uncle = grandparent->rightChild;
            if (uncle && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                if (z == parent->rightChild) {
                    z = parent;
                    rotateLeft(root, z);
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(root, grandparent);
            }
        } else {
            RBNode *uncle = grandparent->leftChild;
            if (uncle && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                if (z == parent->leftChild) {
                    z = parent;
                    rotateRight(root, z);
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rotateLeft(root, grandparent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Insert into RBT
void insertRBTree(RBNode **root, int value) {
    RBNode *z = createNewNode(value);
    RBNode *y = NULL, *x = *root;

    while (x) {
        y = x;
        x->size++; // update size along the path
        if (value < x->value) x = x->leftChild;
        else x = x->rightChild;
    }

    z->parent = y;
    if (!y) *root = z;
    else if (value < y->value) y->leftChild = z;
    else y->rightChild = z;

    fixViolations(root, z);
}

// K-th smallest using subtree size
int findKthSmallest(RBNode *root, int k) {
    if (!root) return -1;
    int leftSize = getSize(root->leftChild);
    if (k == leftSize + 1) return root->value;
    else if (k <= leftSize) return findKthSmallest(root->leftChild, k);
    else return findKthSmallest(root->rightChild, k - leftSize - 1);
}

// ================= MedianFinder API =================
MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->root = NULL;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    insertRBTree(&obj->root, num);
}

double medianFinderFindMedian(MedianFinder* obj) {
    int n = getSize(obj->root);
    if (n % 2 == 1) {
        return findKthSmallest(obj->root, n/2 + 1);
    } else {
        int left = findKthSmallest(obj->root, n/2);
        int right = findKthSmallest(obj->root, n/2 + 1);
        return (left + right) / 2.0;
    }
}

void medianFinderFree(MedianFinder* obj) {
    // TODO: free tree nodes (not shown for brevity)
    free(obj);
}