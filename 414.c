
/*int thirdMax(int* nums, int numsSize) {
    
}*/

#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

// Node structure
typedef struct RBNode {
    int value;
    Color color;
    struct RBNode *leftChild, *rightChild, *parent;
} RBNode;

RBNode *treeRoot = NULL;

// --------------------- Create a new node ---------------------
RBNode* createNewNode(int value) {
    RBNode* newNode = (RBNode*)malloc(sizeof(RBNode));
    newNode->value = value;
    newNode->color = RED; 
    newNode->leftChild = newNode->rightChild = newNode->parent = NULL;
    return newNode;
}

// --------------------- Rotate Left ---------------------
void rotateLeft(RBNode **root, RBNode *pivot) {
    RBNode *rightChild = pivot->rightChild;
    pivot->rightChild = rightChild->leftChild;

    if (rightChild->leftChild != NULL)
        rightChild->leftChild->parent = pivot;

    rightChild->parent = pivot->parent;

    if (pivot->parent == NULL) {          
        *root = rightChild;
    } else if (pivot == pivot->parent->leftChild) {
        pivot->parent->leftChild = rightChild;
    } else {
        pivot->parent->rightChild = rightChild;
    }

    rightChild->leftChild = pivot;
    pivot->parent = rightChild;
}

// --------------------- Rotate Right ---------------------
void rotateRight(RBNode **root, RBNode *pivot) {
    RBNode *leftChild = pivot->leftChild;
    pivot->leftChild = leftChild->rightChild;

    if (leftChild->rightChild != NULL)
        leftChild->rightChild->parent = pivot;

    leftChild->parent = pivot->parent;

    if (pivot->parent == NULL) {          
        *root = leftChild;
    } else if (pivot == pivot->parent->leftChild) {
        pivot->parent->leftChild = leftChild;
    } else {
        pivot->parent->rightChild = leftChild;
    }

    leftChild->rightChild = pivot;
    pivot->parent = leftChild;
}

// --------------------- Fix Violations ---------------------
void fixViolations(RBNode **root, RBNode *newNode) {
    while (newNode != *root && newNode->parent->color == RED) {
        RBNode *parentNode = newNode->parent;
        RBNode *grandParentNode = parentNode->parent;

    if (grandParentNode == NULL)
    break;


        if (parentNode == grandParentNode->leftChild) {
            RBNode *uncleNode = grandParentNode->rightChild;

            if (uncleNode != NULL && uncleNode->color == RED) {
                parentNode->color = BLACK;
                uncleNode->color = BLACK;
                grandParentNode->color = RED;
                newNode = grandParentNode;
            } else {
                if (newNode == parentNode->rightChild) {
                    newNode = parentNode;
                    rotateLeft(root, newNode);
                }
                parentNode->color = BLACK;
                grandParentNode->color = RED;
                rotateRight(root, grandParentNode);
            }
        } else {
            RBNode *uncleNode = grandParentNode->leftChild;

            if (uncleNode != NULL && uncleNode->color == RED) {
                parentNode->color = BLACK;
                uncleNode->color = BLACK;
                grandParentNode->color = RED;
                newNode = grandParentNode;
            } else {
                if (newNode == parentNode->leftChild) {
                    newNode = parentNode;
                    rotateRight(root, newNode);
                }
                parentNode->color = BLACK;
                grandParentNode->color = RED;
                rotateLeft(root, grandParentNode);
            }
        }
    }
    (*root)->color = BLACK; 
}

// --------------------- Insert into Tree (skip duplicates) ---------------------
void insertNode(RBNode **root, int value) {
    RBNode *newNode = createNewNode(value);
    RBNode *previousNode = NULL;
    RBNode *currentNode = *root;

    while (currentNode != NULL) {
        previousNode = currentNode;
        if (value == currentNode->value) {
            free(newNode); // skip duplicates
            return;
        } else if (value < currentNode->value) {
            currentNode = currentNode->leftChild;
        } else {
            currentNode = currentNode->rightChild;
        }
    }

    newNode->parent = previousNode;

    if (previousNode == NULL) {
        *root = newNode; 
    } else if (value < previousNode->value) {
        previousNode->leftChild = newNode;
    } else {
        previousNode->rightChild = newNode;
    }

    fixViolations(root, newNode); 
}

// --------------------- Reverse Inorder Traversal ---------------------
void reverseInorder(RBNode *root, int *count, int *result) {
    if (root == NULL || *count >= 3) return;

    reverseInorder(root->rightChild, count, result);

    if (*count < 3) {
        result[*count] = root->value;
        (*count)++;
    }

    reverseInorder(root->leftChild, count, result);
}

// --------------------- LeetCode Function ---------------------
int thirdMax(int* nums, int numsSize) {
    treeRoot = NULL;

    for (int i = 0; i < numsSize; i++) {
        insertNode(&treeRoot, nums[i]);
    }

    int result[3] = {0};
    int count = 0;
    reverseInorder(treeRoot, &count, result);

    if (count >= 3) return result[2]; 
    else return result[0]; 
}