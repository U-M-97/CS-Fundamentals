#include <iostream>
using namespace std;

class Node {
    int *items;
    int totalItems;
    int t;
    Node **children;
    bool isLeaf;

    Node(int t, bool isLeaf);

    void insertIncompleteNode(int value);
    void splitChild(int i, Node *x);
    void traverse();

    friend class BTree;
};

class BTree {
    int t;
    Node *root;

    public:
        BTree(int t){
            root = NULL;
            this->t = t;
        }

        void insert(int value);

        void traverse(){
            if(root != NULL){
                root->traverse();
            }
        }
};

Node::Node(int t, bool isLeaf){
    items = new int[2 * t - 1];
    totalItems = 0;
    this->t = t;
    children = new Node *[2 * t];
    this->isLeaf = isLeaf;
}

void Node::traverse(){
    int i;
    for(i = 0; i < totalItems; i++){
        if(isLeaf == false){
            children[i]->traverse();
        }
        cout << " " << items[i];
    }

    if(isLeaf == false){
        children[i]->traverse();
    }
}

void Node::splitChild(int i, Node *x){
    Node *a = new Node(x->t, x->isLeaf);
    a->totalItems = t - 1;

    for(int j = 0; j < t - 1; j++){
        a->items[j] = x->items[j + t];
    }

    if(x->isLeaf == false){
        for(int j = 0; j < t; j++){
            a->children[j] = x->children[j + t];
        }
    }

    x->totalItems = t - 1;

    for(int j = totalItems; j >= i + 1; j--){
        children[j + 1] = children[j];
    }

    children[i + 1] = a;

    for(int j = totalItems - 1; j >= i; j--){
        items[j + 1] = items[j];
    }

    items[i] = x->items[t - 1];

    totalItems++;
}

void Node::insertIncompleteNode(int value){
    int i = totalItems - 1;

    if(isLeaf == true){
        while(i >= 0 && items[i] > value){
            items[i + 1] = items[i];
            i--;
        }

        items[i + 1] = value;
        totalItems++;
    }
    else{
        while(i >= 0 && items[i] > value){
            i--;
        }

        if(children[i + 1]->totalItems == 2 * t - 1){
            splitChild(i + 1, children[i + 1]);
            
            if(items[i + 1] < value){
                i++;
            }
        }
        children[i + 1]->insertIncompleteNode(value);
    }
}

void BTree::insert(int value){
    if(root == NULL){
        root = new Node(t, true);
        root->items[0] = value;
        root->totalItems = 1;
    }
    else{
        if(root->totalItems == 2 * t - 1){
            Node *a = new Node(t, false);            

            a->children[0] = root;
            
            a->splitChild(0, root);

            int i = 0;
            if(a->items[i] < value){
                i++;
            }
            a->children[i]->insertIncompleteNode(value);

            root = a;
        }
        else{
            root->insertIncompleteNode(value);
        }
    }
}

int main() {
    BTree t(3);
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);
    t.traverse();
}