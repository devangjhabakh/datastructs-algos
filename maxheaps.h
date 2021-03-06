#include <iostream>
#include <string>
#define HEAPSIZE 1000
using namespace std;
template <typename Item>
//IMPLEMENTATION NOTE:
//Whenever you do use this with a user-defined class, be sure that the class that you use this with has 
//defined methods for operator>() AND operator<(), as they are both used here.
//To heap sort an array, convert it into a valid heap using the Parameterized Heap constructor. Then, 
//repetedly extract from the heap in order to get all the elements in a sorted manner.
class Heap{
    Item HeapArray[HEAPSIZE];
    int count;
    public:
    Heap(){
        count = 0;
    }
    Heap(Item InitialArray[], int GivenCount){        //Take a given array and turn it into a valid heap. (Defined in Notes under Heap Sort)
        for (int i=0;i<GivenCount;++i){
            HeapArray[i] = InitialArray[i];
        }
        count = GivenCount;
        int CurrNode = this -> GetParentAddress(GivenCount - 1);
        while (CurrNode != -1){
            int TraversalNode = CurrNode;
            int RightChildAddress = this -> GetRightChild(TraversalNode);
            int LeftChildAddress = this -> GetLeftChild(TraversalNode);
            Item RightChild = HeapArray[RightChildAddress];
            Item LeftChild = HeapArray[LeftChildAddress];
            Item temp;
            while (LeftChildAddress <= GivenCount - 1){
                if (RightChildAddress>=count){
                    if(LeftChild > HeapArray[TraversalNode]){
                        temp = LeftChild;
                        HeapArray[LeftChildAddress] = HeapArray[TraversalNode];
                        HeapArray[TraversalNode] = temp;
                        TraversalNode = LeftChildAddress;
                    }
                    break;
                }
                else if (RightChild > HeapArray[TraversalNode] || LeftChild > HeapArray[TraversalNode]){
                    if(RightChild>LeftChild){
                        temp = RightChild;
                        HeapArray[RightChildAddress] = HeapArray[TraversalNode];
                        HeapArray[TraversalNode] = temp;
                        TraversalNode = RightChildAddress;
                    }
                    else{
                        temp = LeftChild;
                        HeapArray[LeftChildAddress] = HeapArray[TraversalNode];
                        HeapArray[TraversalNode] = temp;
                        TraversalNode = LeftChildAddress;
                    }
                }
                else{
                    break;
                }
                RightChildAddress = this -> GetRightChild(TraversalNode);
                LeftChildAddress = this -> GetLeftChild(TraversalNode);
                RightChild = HeapArray[RightChildAddress];                 
                LeftChild = HeapArray[LeftChildAddress];
            }
            CurrNode--;
        }
    }
    int GetSizeOfHeap(){
        return count;
    }
    Item GetRootValue(){
        return HeapArray[0];
    }
    int GetParentAddress(int ChildAddress){
        return (ChildAddress - 1)/2;
    }
    int GetLeftChild(int ParentAddress){
        return 2*ParentAddress + 1;
    }
    int GetRightChild(int ParentAddress){
        return 2*ParentAddress + 2;
    }
    void InsertIntoHeap(Item EnteredValue){         //Every time a new node is added to a heap, we reform our heap using the reheapification
        if(count == 0)                              //algorihthm. (Defined in notes)
            HeapArray[count++] = EnteredValue;  
        else{
            int ChildAdd = count;
            HeapArray[count++] = EnteredValue;
            Item temp;
            bool flag = true;
            int ParentAdd = this -> GetParentAddress(count-1);
            while(flag){
                if(ParentAdd == 0){
                    flag = false;
                }
                if(HeapArray[ParentAdd] < HeapArray[ChildAdd]){
                    temp = HeapArray[ChildAdd];
                    HeapArray[ChildAdd] = HeapArray[ParentAdd];
                    HeapArray[ParentAdd] = temp;
                    ChildAdd = ParentAdd;
                    ParentAdd = this -> GetParentAddress(ParentAdd);
                }
                else{
                    for (int i=0;i<count;++i){
                        cout<<HeapArray[i];
                    }
                    return;
                }
            }
        }
        for (int i=0;i<count;++i){
            cout<<HeapArray[i];
        }
        
    }
    Item ExtractRootFromHeap(){                 //Here, we copy and return the value of the root node, which is also the greatest node
        Item c,temp;                            //and then use the process of "sifting down" in order to reconfigure the tree to make it 
        int CurrParent = 0;                     //a valid heap. (Refer notes for a more elaborate explanation)
        c = HeapArray[CurrParent];    
        HeapArray[CurrParent] = HeapArray[--count];                   
        while (CurrParent < ((count+1)/2)){
            int RightChildAddress = this -> GetRightChild(CurrParent);
            int LeftChildAddress = this -> GetLeftChild(CurrParent);
            Item RightChild = HeapArray[RightChildAddress];
            Item LeftChild = HeapArray[LeftChildAddress];
            if (RightChildAddress>=count){
                if(LeftChild > HeapArray[CurrParent]){
                    temp = LeftChild;
                    HeapArray[LeftChildAddress] = HeapArray[CurrParent];
                    HeapArray[CurrParent] = temp;
                    CurrParent = LeftChildAddress;
                }
                break;
            }
            if (RightChild > HeapArray[CurrParent] || LeftChild > HeapArray[CurrParent]){
                if(RightChild>LeftChild){
                    temp = RightChild;
                    HeapArray[RightChildAddress] = HeapArray[CurrParent];
                    HeapArray[CurrParent] = temp;
                    CurrParent = RightChildAddress;
                }
                else{
                    temp = LeftChild;
                    HeapArray[LeftChildAddress] = HeapArray[CurrParent];
                    HeapArray[CurrParent] = temp;
                    CurrParent = LeftChildAddress;
                }
            }
            else{
                return c;
            }
        }   
        return c;
    }
};
