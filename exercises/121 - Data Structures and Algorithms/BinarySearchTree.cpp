#include <iostream>

template <typename T>
class BTNode {
public:
    T data;
    BTNode<T> *left, *right;
    BTNode(T data, BTNode<T> *left = nullptr, BTNode<T> *right = nullptr);
    template <typename T2> friend class BST;
};

template <typename T>
BTNode<T>::BTNode(T data, BTNode<T> *left, BTNode<T> *right) {
    this->data = data;
    this->left = left;
    this->right = right;
}
// Binary search tree template class
template <typename T>
class BST {
private:
    BTNode<T> *root;
    void delete_tree(BTNode<T> *root);
    void inorder(BTNode<T> *root);
    void preorder(BTNode<T> *root);
    void postorder(BTNode<T> *root);
public:
    BST(BTNode<T> *root);
    BST();
    ~BST();
    static BTNode<T> *test_init();
    void insert(T data);
    void display();
};

template <typename T>
BST<T>::BST(BTNode<T> *root) {
    this->root = root;    
} 

template <typename T>
BST<T>::BST() : root(nullptr) {}

template <typename T>
BST<T>::~BST(){
    this->delete_tree(this->root);
}

template <typename T>
BTNode<T> *BST<T>::test_init(){
    BTNode<T> *n20 = new BTNode<int>(20);
    BTNode<T> *n40 = new BTNode<int>(40);
    BTNode<T> *n30 = new BTNode<int>(30, n20, n40);
    BTNode<T> *n0 = new BTNode<int>(0);
    BTNode<T> *n10 = new BTNode<int>(10, n0, n30);
    BTNode<T> *n90 = new BTNode<int>(90);
    BTNode<T> *n80 = new BTNode<int>(80, nullptr, n90);
    BTNode<T> *n60 = new BTNode<int>(60);
    BTNode<T> *n70 = new BTNode<int>(70, n60, n80);
    BTNode<T> *n50 = new BTNode<int>(50, n10, n70);
    return n50;
}

template <typename T>
void BST<T>::delete_tree(BTNode<T> *root){
// Put your answer here
}

template <typename T>
void BST<T>::display() {
    inorder(this->root);
    std::cout << '\n';
}

template <typename T>
void BST<T>::preorder(BTNode<T> *node) {
// define if needed
} 

template <typename T>
void BST<T>::inorder(BTNode<T> *node) {
    if (node != nullptr) {
        inorder(node->left);
        std::cout << node->data << '\n';
        inorder(node->right);
    }
}

template <typename T>
void BST<T>::postorder(BTNode<T> *node) {
// define if needed
} 

template <typename T>
void BST<T>::insert(T data) {
    BTNode<T> *temp = new BTNode<T>(data);
    BTNode<T> *x = this->root;
    BTNode<T> *y = nullptr;

    while (x != nullptr) {
        y = x;
        if (data < x->data) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    if (data < y->data) {
        y->left = temp;
    }
    else {
        y->right = temp;
    }

    
}


template <typename T>
void swap(BTNode<T> *node) {
    if (node->left == nullptr && node->right == nullptr) {
        return;
    }
    else if (node->left == nullptr) {
        node->left = node->right;
        node->right = nullptr;
        swap(node->left);
    }
    else if (node->right == nullptr) {
        node->right = node->left;
        node->left = nullptr;
        swap(node->right);
    }
    else {
        BTNode<T> *temp = node->left;
        node->left = node->right;
        node->right = temp;
        swap(node->left);
        swap(node->right);
    }
}


template <typename T>
void ninorder(BTNode<T> *node) {
    if (node != nullptr) {
        ninorder(node->left);
        std::cout << node->data << '\n';
        ninorder(node->right);
    }
}


int main() {
    BTNode<int> n0(0);
    BTNode<int> n1(1);
    BTNode<int> n2(2);
    BTNode<int> n3(3);
    BTNode<int> n4(5);
    BTNode<int> n5(8);
    BTNode<int> n6(13);
    BTNode<int> n7(21);
    BTNode<int> n8(34);
    BTNode<int> n9(55);
    n0.left = &n1;
    n0.right = &n2;
    n1.left = &n3;
    n1.right = &n4;
    n2.left = &n5;
    n2.right = &n6;
    n3.left = &n7;
    n3.right = &n8;
    n7.left = &n9;

    BST<int> bst(BST<int>::test_init());
    bst.display();
    bst.insert(5);
    bst.display();
}

/*
NOTES: Non Linear ADT
1. Tree
-root node; no parent
-parent<->child
-degree; number of children
-internal; kung may anak
-leaf; walang anak
-path; sequence of nodes, has length node-1
-depth(node) = path length from root to node
-height(node) = max length of path from node to leaf
-ancestor super lolo
-binary tree at most two nodes
--full node; has two child
--full binary tree;
--complete tree ???
*/


