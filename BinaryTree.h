#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename Item>
struct BTNode{
    Item val;
    BTNode *left,*right;
};
template <typename Item>
BTNode<Item> *RecursiveCopy(BTNode<Item> *Node){
    if (Node == NULL)
        return NULL;
    BTNode<Item> *temp = new BTNode<Item>;
    temp -> val = Node -> val;
    temp -> left = RecursiveCopy(Node -> left);
    temp -> right = RecursiveCopy(Node -> right);
    return temp;
}
template <typename Item>
class BinaryTree{
    private:
    BTNode<Item> *rootnode;
    public:
    void DestroyRecursive(BTNode<Item> *Node){
        if(Node != NULL){
            this -> DestroyRecursive(Node -> right);
            this -> DestroyRecursive(Node -> left);
        }
        delete Node;
    }
    ~BinaryTree(){
        DestroyRecursive(rootnode);
    }
    BinaryTree(){
        rootnode = NULL;
    }
    BinaryTree<Item>& operator=(const BinaryTree<Item> &src){
        BTNode<Item> *temp = new BTNode<Item>;
        temp = RecursiveCopy(src.rootnode);
        this -> rootnode = temp;
        return *this;
    }
    BinaryTree(Item val){
        BTNode<Item> *temp = new BTNode<Item>;
        temp -> val = val;
        temp -> right = NULL;
        temp -> left = NULL;
        rootnode = temp;
    }
    BinaryTree(BTNode<Item> &Node){
        BTNode<Item> *temp = new BTNode<Item>;
        temp -> val = Node.val;
        temp -> right = Node.right;
        temp -> left = Node.left;
        rootnode = temp;
    }
    BinaryTree(Item val, BinaryTree<Item> &b1, BinaryTree<Item> &b2){
        BTNode<Item> *temp = new BTNode<Item>;
        temp -> val = val;
        temp -> right = RecursiveCopy(b1.rootnode);
        temp -> left = RecursiveCopy(b2.rootnode);
        rootnode = temp;
    }
    Item GetRootNodeValue() const {
        return (*rootnode).val;
    }
    BTNode<Item>* GetRootNode(){
        return rootnode;
    }
    void ChangeVal(Item val){
        rootnode -> val = val;
    }
};

