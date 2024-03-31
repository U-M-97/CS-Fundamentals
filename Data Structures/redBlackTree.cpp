#include <iostream>
using namespace std;

class RedBlackTree {
    private:
        struct Node {
            int data;
            Node *left;
            Node *right;
            Node *parent;
            char color;

            Node(int data){
                this->data = data;
                left = nullptr;    
                right = nullptr;
                parent = nullptr;
                color = 'r';
            }
        };

        Node *root;
        bool ll;
        bool rr;
        bool lr;
        bool rl;

        Node* leftRotate(Node* root){
            Node* x = root->right;
            Node* y = x->left;
            x->left = root;
            root->right = y;
            root->parent = x;
            if(y != nullptr){
                y->parent = root;
            }
            return x;
        }

        Node* rightRotate(Node* root){
            Node* x = root->left;
            Node* y = x->right;
            x->right = root;
            root->left = y;
            root->parent = x;
            if(y != nullptr){
                y->parent = root;
            }
            return x;
        }

        Node* insertChild(Node *root, int data){
            bool rConflict = false;

            if(root == NULL){
                return new Node(data);
            }
            else{
                if(data < root->data){
                    root->left = insertChild(root->left, data);
                    root->left->parent = root;
                    if(root != this->root){
                        if(root->color == 'r' && root->left->color == 'r'){
                            rConflict = true;
                        }
                    }
                }
                else{
                    root->right = insertChild(root->right, data);
                    root->right->parent = root;
                    if(root != this->root){
                        if(root->color == 'r' && root->right->color == 'r'){
                            rConflict = true;
                        }
                    }
                }
            }

            if(ll){
                root = leftRotate(root);
                root->color = 'b';
                root->left->color = 'r';
                ll = false;
            }
            else if(rr){
                root = rightRotate(root);
                root->color = 'b';
                root->right->color = 'r';
                rr = false;
            }
            else if(lr){
                root->left = leftRotate(root->left);
                root->left->parent = root;
                root = rightRotate(root);
                root->color = 'b';
                root->right->color = 'r';
                lr = false;
            }
            else if(rl){
                root->right = rightRotate(root->right);
                root->right->parent = root;
                root = leftRotate(root);
                root->color = 'b';
                root->left->color = 'r';
                rl = false;
            }

            if(rConflict){
                if(root->parent->right == root){
                    if(root->parent->left == nullptr || root->parent->left->color == 'b'){
                        if(root->left != nullptr && root->left->color == 'r'){
                            rl = true;
                        }
                        else if(root->right != nullptr && root->right->color == 'r'){
                            ll = true;
                        }
                    }
                    else{
                        root->parent->left->color == 'b';
                        root->color == 'b';
                        if(root->parent != this->root){
                            root->parent->color = 'r';
                        }
                    }
                }
                else{
                    if(root->parent->right == nullptr || root->parent->right->color == 'b'){
                        if(root->left != nullptr && root->left->color == 'r'){
                            rr = true;
                        }
                        else if(root->right != nullptr && root->right->color == 'r'){
                            lr = true;
                        }
                    }
                    else{
                        root->parent->right->color = 'b';
                        root->color = 'b';
                        if(root->parent != this->root){
                            root->parent->color = 'r';
                        }
                    }
                }
                
                rConflict = false;
            }

            return root;
        }


    public:
        RedBlackTree(){
            root = nullptr;
            ll = false;
            rr = false;
            lr = false;
            rl = false;
        }

        void insert(int data){
            if(root == NULL){
                root = new Node(data);
                root->color = 'b';
            }
            else{
                root = insertChild(root, data);
            }
        } 

        void inorderTraversal(Node* root){
            if(root != nullptr){
                inorderTraversal(root->left);
                cout << root->data << endl;
                inorderTraversal(root->right);
            }
        }

        void display(){
            inorderTraversal(root);
        }
};

int main(){
    RedBlackTree t;
    t.insert(12);
    t.insert(14);
    t.insert(18);
    t.insert(1);
    t.insert(3);
    t.display();
}