#include <iostream>
#ifndef TREES_H_
#define TREES_H_
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
    void InsertItem(Item valenter){
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
    void InOrderTraversal(){
        if(rootnode == nullptr){
            return;
        }
        else{
            BinarySearchTree(*(rootnode -> left)).InOrderTraversal();
            std::cout<<"\n"<<rootnode -> val;
            BinarySearchTree(*(rootnode -> right)).InOrderTraversal();
        }
    }
};
#endif