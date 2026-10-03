#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertBST(Node* root, int key) {
    if (root == NULL) return createNode(key);
    if (key < root->key)
        root->left = insertBST(root->left, key);
    else if (key > root->key)
        root->right = insertBST(root->right, key);
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

int searchBST(Node* root, int key, int* comparisons) {
    Node* curr = root;
    while (curr != NULL) {
        (*comparisons)++;
        if (curr->key == key) return 1;
        if (key < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return 0;
}

int linearSearch(int arr[], int n, int key, int* comparisons) {
    for (int i = 0; i < n; i++) {
        (*comparisons)++;
        if (arr[i] == key) return 1;
    }
    return 0;
}

int main() {
    int isbns[] = {45, 20, 60, 10, 30, 50, 70, 25, 55};
    int n = sizeof(isbns) / sizeof(isbns[0]);

    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insertBST(root, isbns[i]);
    }

    printf("=== BST Traversals ===\n");
    printf("Inorder   : "); inorder(root); printf("\n");
    printf("Preorder  : "); preorder(root); printf("\n");
    printf("Postorder : "); postorder(root); printf("\n\n");

    int targets[] = {25, 55, 90};
    int numTargets = sizeof(targets) / sizeof(targets[0]);

    printf("=== Search Comparisons ===\n");
    printf("%-10s | %-12s | %-15s | %-15s\n", "Target", "Status", "BST Comparisons", "Linear Search");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < numTargets; i++) {
        int target = targets[i];
        int bstComps = 0, linComps = 0;
        int foundBST = searchBST(root, target, &bstComps);
        linearSearch(isbns, n, target, &linComps);

        printf("%-10d | %-12s | %-15d | %-15d\n", 
               target, 
               foundBST ? "Found" : "Not Found", 
               bstComps, 
               linComps);
    }

    return 0;
}