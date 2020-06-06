#include <functional>
#include <iostream>
#include <string>
#include "trees.h"
#define TABLESIZE 100
using namespace std;
hash<string> str_hash;
class StudentNode{
    private:
    string name;
    int ID;
    int marks;
    public:
    StudentNode(){
        name = "";
        ID = 0;
        marks = 0;
    }
    StudentNode(string given_name, int given_ID, int given_marks){
        name = given_name;
        ID = given_ID;
        marks = given_marks;
    }
    bool operator>(const StudentNode &other) const {
        if(marks>other.marks){
            return true;
        }
        return false;
    }
    bool operator==(const StudentNode &other) const {
        if(marks == other.marks && name == other.name && ID == other.ID){
            return true;
        }
        return false;
    }
    string GetName(){
        return name;
    }
};
template <typename Item>
class HashTable{
    private:
    BinarySearchTree<Item> Buckets[TABLESIZE];
    public:
    int HashFunc(string GivenName){
        return str_hash(GivenName) % TABLESIZE;
    }
    void Insert(string name, int ID, int marks){
        int hashValue = HashFunc(name);
        Buckets[hashValue].InsertItem(StudentNode(name,ID,marks));
    }
    bool CheckIfPresent(StudentNode s1){
        int hashValue = HashFunc(s1.GetName());
        return Buckets[hashValue].CheckForItem(s1);
    }
};
int main(){
    int opt;
    StudentNode temp;
    string temp_name;
    int temp_ID,temp_marks;
    HashTable<StudentNode> hash1;
    while (1){
        cout<<"\nEnter 1 to Enter and 2 to Check. -1 to exit.";
        cin>>opt;
        cout<<opt;
        switch(opt){
            case 1: cout<<"\nEnter a student's\nname:";
                    cin>>temp_name;
                    cout<<"\nID:";
                    cin>>temp_ID;
                    cout<<"\nmarks:";
                    cin>>temp_marks;
                    hash1.Insert(temp_name,temp_ID,temp_marks);
                    break;
            case 2: cout<<"\nEnter a name to search for: ";
                    cin>>temp_name;
                    cout<<"\nID:";
                    cin>>temp_ID;
                    cout<<"\nmarks:";
                    cin>>temp_marks;
                    if(hash1.CheckIfPresent(StudentNode(temp_name,temp_ID,temp_marks)) == true){
                        cout<<"The name is present!";
                    }
                    else{
                        cout<<"The name is absent!";
                    }
                    break;
            case -1: exit(0);
            default: cout<<"Invalid option! Try again";
        }
    }
    return 1;
}
