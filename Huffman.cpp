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
};

bool operator<=(const BinaryTree<HuffNode> &a, const BinaryTree<HuffNode> &b){
    if(a.GetRootNodeValue().freq <= b.GetRootNodeValue().freq)
        return true;
    return false;
}

// bool CheckIfAllDone(list<BinaryTree<HuffNode> > huffList){
//     list<BinaryTree<HuffNode> >::iterator huffIter;
//     huffIter = huffList.begin();
//     while(huffIter != huffList.end()){
//         if((*huffIter).GetRootNodeValue().Done == false){
//             return false;
//         }
//         else{
//             char tempch = (*huffIter).GetRootNodeValue().ch;
//             int tempfreq = (*huffIter).GetRootNodeValue().freq;
//             cout<<tempfreq;
//         }
//         ++huffIter;
//     }
//     return true;
// }

// bool CheckIfAllDone(BinaryTree<HuffNode> *huffList, int n){
//     // list<BinaryTree<HuffNode> >::iterator huffIter;
//     for (int i=0;i<n;++i){
//         if(huffList[i].GetRootNodeValue().Done == false){
//             return false;
//         }
//     }
//     return true;
// }


// list<BinaryTree<HuffNode> >::iterator FirstNotDone(list<BinaryTree<HuffNode> > huffList){
//     list<BinaryTree<HuffNode> >::iterator huffIter;
//     huffIter = huffList.begin();
//     while(huffIter != huffList.end()){
//         if((*huffIter).GetRootNodeValue().Done == false){
//             return huffIter;
//         }
//         ++huffIter;
//     }
// }

void MinTwoSort(BinaryTree<HuffNode> huffList[], int n){
    int count = 0,minhuffindex = 0;
    BinaryTree<HuffNode> minhuff,temp;
    while(count<2){
        minhuff = huffList[count];
        for(int i=count;i<n;++i){
            if(huffList[i] <= minhuff){
                minhuff = huffList[i];
                minhuffindex = i;
            }
        }
        temp = huffList[minhuffindex];
        huffList[minhuffindex] = huffList[count];
        huffList[count] = temp;
        ++count;
    };
}

class HuffManDecoder{
    map<char, string> DecoderKey;
    public:
    HuffManDecoder(map<char, string> GivenDecoderKey){
        DecoderKey = GivenDecoderKey;
    }
    string DecodeFile(string filename){
        ifstream inputText(filename + "-encoded.txt");
        char CurrentCharacter[80];
        string OutputSentence;
        map<char, string>::iterator mapiter;
        while (inputText.getline(CurrentCharacter,80,' ')){
            mapiter = DecoderKey.begin();
            while(mapiter != DecoderKey.end()){
                if ((mapiter -> second) == CurrentCharacter){
                   OutputSentence.push_back(mapiter -> first); 
                }
                ++mapiter;   
            }
        }
        return OutputSentence;
    }
};

class HuffManEncodedText{
    private:
    BinaryTree<HuffNode> HuffmanTree;
    map<char, int> HuffManHistogram;
    public:
    string pathtofound(BTNode<HuffNode> *Node, char item){
        if(Node == NULL){
            return "2";                                     //A failure code.
        }
        else if(Node -> val.ch == item){    
            return "3";                                     //A success code.
        }
        else{
            string foundleft = pathtofound(Node -> left, item);
            string foundright = pathtofound(Node -> right, item);
            if(foundleft[foundleft.size()-1] == '2'){
                return "1"+foundright;
            }
            else{
                return "0"+foundleft;
            }
        }
    }
    BinaryTree<HuffNode> BuildHuffmanTree(BinaryTree<HuffNode> huffList[], int n){
        if(n == 1){
            return huffList[0];
        }
        MinTwoSort(huffList,n);
        BinaryTree<HuffNode> Tree1, Tree2;
        HuffNode temp;
        Tree1 = huffList[0];
        Tree2 = huffList[1];
        temp.ch = '\0';
        temp.freq = Tree1.GetRootNodeValue().freq + Tree2.GetRootNodeValue().freq;
        BinaryTree<HuffNode> MasterTree(temp,Tree1,Tree2);
        BinaryTree<HuffNode> *NewList = new BinaryTree<HuffNode>[n-1];
        NewList[0] = MasterTree;
        for(int i = 1;i<n-1;++i){
            NewList[i] = huffList[i+1];
        }
        return BuildHuffmanTree(NewList,n-1);
    }
    HuffManEncodedText(string filename){
        ifstream inputText(filename + ".txt");
        string concatenatedinput = "";
        char tempch;
        if(!inputText){
            cout<<"Empty file!";
        }
        else{
            while(inputText.get(tempch)){                       //This while loop builds a HuffMan histogram using a map.
                concatenatedinput.push_back(tempch);                         
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
        BinaryTree<HuffNode> *HuffNodeList = new BinaryTree<HuffNode>[HuffManHistogram.size()];  
        for(int i=0;i<HuffManHistogram.size();++i){
            HuffNode temp;
            temp.ch = mapiter -> first;
            temp.freq = mapiter -> second;
            BinaryTree<HuffNode> TreeTemp(temp);
            HuffNodeList[i] = TreeTemp;
            ++mapiter;
        }
        // sort(HuffNodeList, HuffNodeList + (HuffManHistogram.size()));
        HuffmanTree = BuildHuffmanTree(HuffNodeList,HuffManHistogram.size());
        // while(!CheckIfAllDone(HuffNodeList),HuffManHistogram.size()){
        //     BinaryTree<HuffNode> Node1,Node2;
        //     HuffNode temp;
        //     Node1 = HuffNodeList.front();
        //     temp = Node1.GetRootNodeValue();
        //     temp.Done = true;
        //     Node1.ChangeVal(temp);
        //     HuffNodeList.pop_front();
        //     Node2 = HuffNodeList.front();
        //     temp = Node2.GetRootNodeValue();
        //     temp.Done = true;
        //     Node2.ChangeVal(temp);
        //     HuffNodeList.pop_front();
        //     temp.ch = '\0';
        //     temp.Done = true;
        //     temp.freq = Node1.GetRootNodeValue().freq + Node2.GetRootNodeValue().freq;
        //     BinaryTree<HuffNode> bmaster(temp,Node1,Node2);
        //     HuffNodeList.push_back(bmaster);
        //     HuffNodeList.sort(); 
        // };
        ofstream outputText(filename+"-encoded.txt");
        mapiter = HuffManHistogram.begin();
        string PathVector;
        for (int i=0;i<concatenatedinput.size();++i){
            PathVector = pathtofound(HuffmanTree.GetRootNode(),concatenatedinput[i]);
            outputText<<PathVector.substr(0,(PathVector.size()-1));
            outputText<<" ";
        }
        outputText.close();
        inputText.close();
    }
    HuffManDecoder GetDecodingKey(){
        string currentpath;
        map<char, string> DecoderMap;
        map<char, int>::iterator HistIter = HuffManHistogram.begin();
        while(HistIter != HuffManHistogram.end()){
            currentpath = pathtofound(HuffmanTree.GetRootNode(),HistIter -> first);
            DecoderMap[HistIter -> first] = currentpath.substr(0,(currentpath.size()-1));
            ++HistIter;
        }
        return HuffManDecoder(DecoderMap);
    }
};
int main(){
    string filename = "demo";
    HuffManEncodedText MyHuffManTree(filename);
    HuffManDecoder MyHuffManDecoder = MyHuffManTree.GetDecodingKey();
    ofstream DecoderFile(filename + "-decoderkey.obj",ios::binary);
    DecoderFile.write((char*)&MyHuffManDecoder, sizeof(HuffManDecoder));
    cout<<MyHuffManDecoder.DecodeFile("demo");
    return 1;
}

// int main(){
//     cout<<CharToBinary('I');
//     return 1;
// }
