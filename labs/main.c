#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
};

struct Node* add_node(struct Node* root, int val) {
    if (root == NULL) {
        struct Node* node = (struct Node*) malloc(sizeof(struct Node));
        node->val = val;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    
    if (val >= root->val) {
        root->right = add_node(root->right, val);
    } else {
        root->left = add_node(root->left, val);
    }

    return root;
}

struct Node* get_kth_element(struct Node* node, int k) {
    // TODO
    if(node == NULL)
        return NULL;
    struct Node* left = get_kth_element(node->left, k);
    if (left != NULL)
        return left;
    
    if (k == 1)
        return node;
    
    return get_kth_element(node->right, k - 1);
    
};

int main() {
    /*DO NOT MODIFY*/
    struct Node* root = NULL;
    int n, x, k;

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        root = add_node(root, x);
    }

    printf("%d\n", get_kth_element(root, k)->val);

    return 0;
}
