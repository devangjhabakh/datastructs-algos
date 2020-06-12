#include <iostream>
#include <string>
#include <vector>
#define NUM_VERTICES 9
using namespace std;
bool CheckIfAllTrue(bool *boolArray, int n){
    for (int i = 0; i < n; ++i){
        if(boolArray[i] == false){
            return false;
        }
    }
    return true;
}

void AdjacentMinDistance(int G1[][NUM_VERTICES], bool Done[], int n, int start,int pathLengths[], int MinIndexPath[]){
    int minpath = INT16_MAX, minindex = 0;
    for (int i=0;i<n;++i){
        if(G1[start][i]<minpath && G1[start][i] != 0 && Done[i] == false){  //Initialize the distances for all adjacent vertices.
            if(pathLengths[i] > G1[start][i] + pathLengths[start]){
                pathLengths[i] = G1[start][i] + pathLengths[start];
            }
        }
    }
    for (int i=0;i<n;++i){                                                  //Find the minimum distance out of ALL vertices. 
        if(Done[i] == false){
            if(pathLengths[i] < minpath){
                 minpath = pathLengths[i];
                minindex = i;
            }
        }
    }
    MinIndexPath[0] = minindex;
    MinIndexPath[1] = minpath;
}

void Dijkstra(int G1[][NUM_VERTICES], int n, int start){
    bool Done[NUM_VERTICES];                                //A boolean array that keeps track of whether vertex labeled "i" had its shortest path discovered.
    int pathLengths[NUM_VERTICES];                          //An integer array that keeps track of the minimum distances from our starting vertex to any given vertex.
    for(int i = 0;i<n;++i){
        Done[i] = false;
        pathLengths[i] = INT16_MAX;
    }
    Done[start] = true;                             //Initialising special values for the starting node.
    pathLengths[start] = 0;
    int minpath = INT16_MAX, minindex = 0;
    while(!CheckIfAllTrue(Done,n)){
        int MinIndexPath[2];                        //A temporary pair of values that keep track of the next minimum index and its path length for a given iteration of Dijkstra.
        AdjacentMinDistance(G1,Done,n,minindex,pathLengths,MinIndexPath);   //This function initialises the minimum distance for all adjacent vertices.
        Done[MinIndexPath[0]] = true;       //Mark the vertex with the current minimum path as done.
        minindex = MinIndexPath[0];         
    }; 
    cout<<"The distances are: \n";
    for(int i=0;i<n;++i){
        cout<<i<<" "<<pathLengths[i]<<"\n";
    }
}

int main(){ 
    int graph[NUM_VERTICES][NUM_VERTICES] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 }, 
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 }, 
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 }, 
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 }, 
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 }, 
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 }, 
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 }, 
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 }, 
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
    Dijkstra(graph,NUM_VERTICES,0);
    cout<<"End of program!";
    return 1;
}