#include <iostream>
#include <string>
#include <vector>
using namespace std;
template <typename Item>
struct BSTNode{
    Item val;
    BSTNode *left,*right;
};
template <typename Item>
class BinarySearchTree{
    private:
    BSTNode<Item> *rootnode;
    public:
    BinarySearchTree(){
        rootnode = nullptr;
    }
    BinarySearchTree(BSTNode<Item> &b){
        rootnode = &b;
    }
    void InsertItem(Item);
    void InOrderTraversal();
};
template <typename Item>
void BinarySearchTree<Item>::InsertItem(Item valenter){
    if(rootnode == nullptr){
        BSTNode<Item> *EnteringNode;
        EnteringNode = new BSTNode<Item>;
        EnteringNode -> val = valenter;
        EnteringNode -> left = nullptr;
        EnteringNode -> right = nullptr;
        rootnode = EnteringNode;
    }
    else if(valenter == rootnode -> val){
        return;
    }     
    else if(rootnode -> val>valenter){
        if(rootnode -> left != nullptr){
                BinarySearchTree(*(rootnode -> left)).InsertItem(valenter);
        }
        else{
            BSTNode<Item> *EnteringNode;
            EnteringNode = new BSTNode<Item>;
            EnteringNode -> val = valenter;
            EnteringNode -> left = nullptr;
            EnteringNode -> right = nullptr;
            rootnode -> left = EnteringNode;
        }
    }
    else{
        if(rootnode -> right != nullptr){
                BinarySearchTree(*(rootnode -> right)).InsertItem(valenter);
        }
        else{
            BSTNode<Item> *EnteringNode;
            EnteringNode = new BSTNode<Item>;
            EnteringNode -> val = valenter;
            EnteringNode -> left = nullptr;
            EnteringNode -> right = nullptr;
            rootnode -> right = EnteringNode;
        }
    }
}

template <typename Item>
void BinarySearchTree<Item>::InOrderTraversal(){
    if(rootnode == nullptr){
        return;
    }
    else{
        BinarySearchTree(*(rootnode -> left)).InOrderTraversal();
        cout<<"\n"<<rootnode -> val;
        BinarySearchTree(*(rootnode -> right)).InOrderTraversal();
    }
}
int main(){
    BinarySearchTree<int> Tree1;
    int opt = 1;
    do{
        cout<<"Enter a value you want to enter in the BST, and enter -1 if you wish to print and quit.";
        cin>>opt;
        if(opt == -1){
            ;
        }
        else{
            Tree1.InsertItem(opt);
        }
    }while(opt != -1);
    Tree1.InOrderTraversal();
    return 1;
}

