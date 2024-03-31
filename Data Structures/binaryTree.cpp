#include <iostream>
#include <cstdlib>
#include <limits>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
} node;

node* createNode(int data){
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

void inOrder(node *root){
    if(root == NULL){
        return;
    }
    inOrder(root->left);
    std::cout << root->data << std::endl;
    inOrder(root->right);
}

void preOrder(node *root){
    if(root == NULL){
        return;
    }
    std::cout << root->data << std::endl;
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(node *root){
    if(root == NULL){
        return;
    }    
    postOrder(root->left);
    postOrder(root->right);
    std::cout << root->data << std::endl;
}

bool isFullBinaryTree(node *root){
    if(root == NULL){
        return true;
    }

    if(root->left == NULL && root->right == NULL){
        return true;
    }

    if(root->left == NULL || root->right == NULL){
        return false;
    }

    if(root->left && root->right){
        return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
    }
}

int depth(node* root){
    int d = 0;
    while(root->left != NULL){
        d++;
        root = root->left;
    }
    return d;
}

int totalNodes(node* root, int n = 0){
    if(root == NULL){
        return 0;
    }
    return 1 + totalNodes(root->left, n) + totalNodes(root->right, n);
}

bool isPerfectBinaryTree(node *root, int d, int level = 0){
    if(root == NULL){
        return true;
    }

    if(root->left == NULL && root->right == NULL){
        return (d == level);
    }

    if(root->left == NULL ||  root->right == NULL){
        return false;
    }

    return isPerfectBinaryTree(root->left, d, level + 1) && isPerfectBinaryTree(root->right, d, level + 1);
}

bool isCompleteBinaryTree(node* root, int index, int totalNodes){
    if(root == NULL){
        return true;
    }
    
    if(index >= totalNodes){
        return false;
    }

    return isCompleteBinaryTree(root->left, 2 * index + 1, totalNodes) && isCompleteBinaryTree(root->right, 2 * index + 2, totalNodes);
}

bool isBalancedTree(node* root, int* height){
    int lh = 0, rh = 0, l = 0, r = 0;
    if(root == NULL){
        *height = 0;
        return 1;
    }

    l = isBalancedTree(root->left, &lh);
    r = isBalancedTree(root->right, &rh);

    *height = (lh > rh ? lh : rh) + 1;

    if(std::abs(lh - rh) >= 2){
        return 0;
    }

    else{
        return l && r;
    }
}

long long minValue(node* root){
    if(root == NULL){
        return INT64_MAX;
    }
    long long left = minValue(root->left);
    long long right = minValue(root->right);
    return std::min<long long>(root->data, std::min(left, right));   
}

long long maxValue(node* root){
    if(root == NULL){
        return INT64_MIN;
    }
    long long left = maxValue(root->left);
    long long right = maxValue(root->right);
    return std::max<long long>(root->data, std::max(left, right));
}

bool isBST(node* root){
    if(root == NULL){
        return true;
    }

    if(maxValue(root->left) > root->data || minValue(root->right) < root->data){
        return false;
    }
    
    return isBST(root->left) && isBST(root->right);
}

node* insertBST(node* root, int data){
    if(root == NULL){
        return createNode(data);
    }

    if(data < root->data){
        root->left = insertBST(root->left, data);
    }else{
        root->right = insertBST(root->right, data);
    }
    return root;
}

node* minValueBST(node* root){
    if(root != NULL && root->left != NULL){
        root = root->left;
    }
    return root;
}

node* deleteBST(node* root, int data){
    if(root == NULL){
        return root;
    }

    if(data < root->data){
        root->left = deleteBST(root->left, data);
    }
    else if(data > root->data){
        root->right = deleteBST(root->right, data);
    }
    else{
        if(root->left == NULL){
            node* tmp = root->right;
            free(root);
            return tmp;
        }
        else if(root->right == NULL){
            node* tmp = root->left;
            free(root);
            return tmp;
        }
        node* tmp = minValueBST(root->right);
        root->data = tmp->data;
        root->right = deleteBST(root->right, tmp->data);
    }

    return root;
}

int height(node* root){
    if(root == NULL){
        return 0;
    }
    return root->height;
}

node* leftRotate(node* root){
    node* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;

    root->height = std::max(height(root->left), height(root->right)) + 1;
    tmp->height = std::max(height(tmp->left), height(tmp->right)) + 1;
    return tmp;
}

node* rightRotate(node* root){
    node* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;

    root->height = std::max(height(root->left), height(root->right)) + 1;
    tmp->height = std::max(height(tmp->left), height(tmp->right)) + 1;
    return tmp;
}

int balanceFactor(node* root){
    if(root == NULL){
        return 0;
    }
    return height(root->left) - height(root->right);
}

node* insertAVL(node* root, int data){
    if(root == NULL){
        return createNode(data);        
    }
    else if(data < root->data){
        root->left = insertAVL(root->left, data);
    }
    else if(data > root->data){
        root->right = insertAVL(root->right, data);
    }
    else {
        return root;
    }

    root->height = std::max(height(root->left), height(root->right)) + 1;
    if(balanceFactor(root) > 1){
        if(data < root->left->data){
            return rightRotate(root);
        }
        else if(data > root->left->data){
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    
    if(balanceFactor(root) < -1){
        if(data > root->right->data){
            return leftRotate(root);
        }
        else if(data < root->right->data){
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    
    return root;
}

node* deleteAVL(node* root, int data){
    if(root == NULL){
        return root;
    }
    else if(data < root->data){
        root->left = deleteAVL(root->left, data);
    }
    else if(data > root->data){
        root->right = deleteAVL(root->right, data);
    }
    else{
        if(root->left == NULL){
            node* tmp = root->right;
            free(root->right);
            return tmp;
        }
        else if(root->right == NULL){
            node* tmp = root->left;
            free(root->left);
            return tmp;
        }
        node* tmp = minValueBST(root);    
        root->data = tmp->data;
        root->right = deleteAVL(root->right, tmp->data);
    }

    if(root == NULL){
        return root;
    }

    if(balanceFactor(root) > 1){
        if(balanceFactor(root->left) >= 0){
            return rightRotate(root);
        }
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    if(balanceFactor(root) < -1){
        if(balanceFactor(root->right) <= 0){
            return leftRotate(root);
        }
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// Print the tree
void printTree(Node *root, std::string indent, bool last) {
  if (root != nullptr) {
    std::cout << indent;
    if (last) {
      std::cout << "R----";
      indent += "   ";
    } else {
      std::cout << "L----";
      indent += "|  ";
    }
    std::cout << root->data << std::endl;
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
  }
}

int main(){
    std::cout << "neovim";
    return 0;
}