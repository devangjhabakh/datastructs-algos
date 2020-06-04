#include <functional>
#include <iostream>
#include <string>
#include "trees.h"
#define TABLESIZE 100
using namespace std;
class StudentNode{
    private:
    string name;
    int ID;
    int marks;
    public:
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
};
template <typename Item>
class HashTable{
    private:
    BinarySearchTree<Item> Buckets[TABLESIZE];
    public:
    void Insert(string name, int ID, int marks){
        int hashValue = ID % TABLESIZE;
        Buckets[hashValue].InsertItem(StudentNode(name,ID,marks));
    }
};