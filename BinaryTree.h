#include <iostream>
#include <string>
using namespace std;

template <typename Item>
struct BTNode{
    Item val;
    BTNode *left,*right;
};
template <typename Item>
BTNode<Item> *RecursiveCopy(BTNode<Item> *Node){
    if (Node == nullptr)
        return nullptr;
    BTNode<Item> *temp = (BTNode<Item> *)malloc(sizeof(Node));
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
    // void DestroyRecursive(BTNode<Item> *Node){
    //     if(Node != nullptr){
    //         this -> DestroyRecursive(Node -> right);
    //         this -> DestroyRecursive(Node -> left);
    //     }
    //     delete Node;
    // }
    // ~BinaryTree(){
    //     DestroyRecursive(rootnode);
    // }
    BinaryTree(){
        ;
    }
    BinaryTree<Item>& operator=(const BinaryTree<Item> &src){
        // if (src.rootnode == nullptr )
        //     this -> rootnode = nullptr;
        // BTNode<Item> *temp = (BTNode<Item> *)malloc(sizeof(rootnode));
        // temp->val = src.rootnode -> val;    
        // temp->left = RecursiveCopy(src.rootnode -> left);   
        // temp->right = RecursiveCopy(src.rootnode -> right);
        this -> rootnode = RecursiveCopy(src.rootnode);
        return *this;
    }
    BinaryTree(Item val){
        BTNode<Item> *temp = (BTNode<Item> *)malloc(sizeof(BTNode<Item>));
        temp -> val = val;
        temp -> right = nullptr;
        temp -> left = nullptr;
        rootnode = temp;
    }
    BinaryTree(BTNode<Item> &Node){
        BTNode<Item> *temp = (BTNode<Item> *)malloc(sizeof(BTNode<Item>));
        temp -> val = Node.val;
        temp -> right = Node.right;
        temp -> left = Node.left;
        rootnode = temp;
    }
    BinaryTree(Item val, BinaryTree<Item> &b1, BinaryTree<Item> &b2){
        BTNode<Item> *temp = (BTNode<Item> *)malloc(sizeof(BTNode<Item>));
        temp -> val = val;
        temp -> right = b1.rootnode;
        temp -> left = b2.rootnode;
        rootnode = temp;
    }
    Item GetRootNodeValue() const {
        return (*rootnode).val;
    }
    Item* GetRootNode(){
        return rootnode;
    }
    void ChangeVal(Item val){
        rootnode -> val = val;
    }
};

