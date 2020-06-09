#include <string>
#include <iostream>
#include <bitset>
#include "BinaryTree.h"
#include <fstream>
#include <map>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;

//THE DESTRUCTOR FOR THE BINARY TREE NEEDS TO BE FIXED. 
//THIS PROGRAM IS SUSCEPTIBLE TO MASSIVE MEMORY LEAKS.
//
//
//
//
//
string CharToBinary(char c){
    return bitset<8>(int(c)).to_string();
}

char BinaryToChar(string binary){
    return bitset<8>(binary).to_ulong();
}

struct HuffNode{
    char ch;
    int freq;
    bool Done;
};

bool operator<(const BinaryTree<HuffNode> &a, const BinaryTree<HuffNode> &b){
    if(a.GetRootNodeValue().freq < b.GetRootNodeValue().freq)
        return true;
    return false;
}

bool CheckIfAllDone(list<BinaryTree<HuffNode> > huffList){
    list<BinaryTree<HuffNode> >::iterator huffIter;
    huffIter = huffList.begin();
    while(huffIter != huffList.end()){
        if((*huffIter).GetRootNodeValue().Done == false){
            return false;
        }
        else{
            char tempch = (*huffIter).GetRootNodeValue().ch;
            int tempfreq = (*huffIter).GetRootNodeValue().freq;
            cout<<tempfreq;
        }
        ++huffIter;
    }
    return true;
}

list<BinaryTree<HuffNode> >::iterator FirstNotDone(list<BinaryTree<HuffNode> > huffList){
    list<BinaryTree<HuffNode> >::iterator huffIter;
    huffIter = huffList.begin();
    while(huffIter != huffList.end()){
        if((*huffIter).GetRootNodeValue().Done == false){
            return huffIter;
        }
        ++huffIter;
    }
}

class HuffManEncodedText{
    private:
    BinaryTree<HuffNode> tree1;
    map<char, int> HuffManHistogram;
    public:
    HuffManEncodedText(string filename){
        ifstream inputText(filename + ".txt");
        char tempch;
        if(!inputText){
            cout<<"Empty file!";
        }
        else{
            while(inputText.get(tempch)){                                                   //This while loop builds a HuffMan histogram using a map.
                cout<<tempch;
                if(HuffManHistogram.find(tempch) == HuffManHistogram.end()){
                    HuffManHistogram[tempch] = 1;
                }
                else{
                    HuffManHistogram[tempch] += 1;
                }
            }
        }
        map<char, int>::iterator mapiter;
        mapiter = HuffManHistogram.begin();
        list<BinaryTree<HuffNode> > HuffNodeList;  
        for (int i=0;i<HuffManHistogram.size()-1;++i){
            HuffNode temp;
            temp.ch = mapiter -> first;
            temp.freq = mapiter -> second;
            temp.Done = false;
            BinaryTree<HuffNode> TreeTemp(temp);
            HuffNodeList.push_back(TreeTemp);
            ++mapiter;
        }
        HuffNodeList.sort();
        while(!CheckIfAllDone(HuffNodeList)){
            BinaryTree<HuffNode> Node1,Node2;
            HuffNode temp;
            Node1 = HuffNodeList.front();
            temp = Node1.GetRootNodeValue();
            temp.Done = true;
            Node1.ChangeVal(temp);
            HuffNodeList.pop_front();
            Node2 = HuffNodeList.front();
            temp = Node2.GetRootNodeValue();
            temp.Done = true;
            Node2.ChangeVal(temp);
            HuffNodeList.pop_front();
            temp.ch = '\0';
            temp.Done = true;
            temp.freq = Node1.GetRootNodeValue().freq + Node2.GetRootNodeValue().freq;
            BinaryTree<HuffNode> bmaster(temp,Node1,Node2);
            HuffNodeList.push_back(bmaster);
            HuffNodeList.sort(); 
        }
        cout<<"aa";
    }
};
int main(){
    HuffManEncodedText("demo");
    return 1;
}

// int main(){
//     cout<<CharToBinary('I');
//     return 1;
// }
