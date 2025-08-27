/*int createSortedArray(int* instructions, int instructionsSize)
{

}*/

#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int value;
    Color color;
    struct RBNode *leftChild, *rightChild, *parent;
    int size; // size of subtree rooted at this node
} RBNode;

RBNode* createNewNode(int value) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->value = value;
    node->color = RED; // new nodes are red
    node->leftChild = node->rightChild = node->parent = NULL;
    node->size = 1;
    return node;
}

int getSize(RBNode *node) {
    return node ? node->size : 0;
}

void updateSize(RBNode *node) {
    if (node)
        node->size = 1 + getSize(node->leftChild) + getSize(node->rightChild);
}

// ---------------- Rotations ----------------
void leftRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->rightChild;
    x->rightChild = y->leftChild;
    if (y->leftChild)
        y->leftChild->parent = x;

    y->parent = x->parent;
    if (!x->parent)
        *root = y;
    else if (x == x->parent->leftChild)
        x->parent->leftChild = y;
    else
        x->parent->rightChild = y;

    y->leftChild = x;
    x->parent = y;

    updateSize(x);
    updateSize(y);
}

void rightRotate(RBNode **root, RBNode *y) {
    RBNode *x = y->leftChild;
    y->leftChild = x->rightChild;
    if (x->rightChild)
        x->rightChild->parent = y;

    x->parent = y->parent;
    if (!y->parent)
        *root = x;
    else if (y == y->parent->leftChild)
        y->parent->leftChild = x;
    else
        y->parent->rightChild = x;

    x->rightChild = y;
    y->parent = x;

    updateSize(y);
    updateSize(x);
}

// ---------------- Fix Violations ----------------
void fixViolations(RBNode **root, RBNode *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->leftChild) {
            RBNode *y = z->parent->parent->rightChild;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->rightChild) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            RBNode *y = z->parent->parent->leftChild;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->leftChild) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// ---------------- Count helpers ----------------
int countLess(RBNode *root, int value) {
    if (!root) return 0;
    if (value <= root->value)
        return countLess(root->leftChild, value);
    else
        return 1 + getSize(root->leftChild) + countLess(root->rightChild, value);
}

int countGreater(RBNode *root, int value) {
    if (!root) return 0;
    if (value >= root->value)
        return countGreater(root->rightChild, value);
    else
        return 1 + getSize(root->rightChild) + countGreater(root->leftChild, value);
}

// ---------------- Insertion ----------------
void insertNode(RBNode **root, int value) {
    RBNode *z = createNewNode(value);
    RBNode *y = NULL;
    RBNode *x = *root;

    while (x) {
        y = x;
        x->size++; // update size along the path
        if (z->value < x->value)
            x = x->leftChild;
        else
            x = x->rightChild;
    }

    z->parent = y;
    if (!y)
        *root = z;
    else if (z->value < y->value)
        y->leftChild = z;
    else
        y->rightChild = z;

    fixViolations(root, z);
}

// ---------------- Main function ----------------
int createSortedArray(int* instructions, int instructionsSize) {
    RBNode *root = NULL;
    long long cost = 0;

    for (int i = 0; i < instructionsSize; i++) {
        int val = instructions[i];
        int less = countLess(root, val);
        int greater = countGreater(root, val);
        cost = (cost + (less < greater ? less : greater)) % MOD; //min(less, greater)
        insertNode(&root, val);
    }

    return (int)cost;
}