#include <iostream>
#include <chrono> 
using namespace std;
using namespace std::chrono;
//A Merge sort function that sorts in ascending order - 29 microseconds.
void Merge(int arr[],int start1,int start2,int end){        //Merges two sorted arrays in ascending order.
    int i=start1,j=start2,k = 0;
    int *arr2 = new int[end - start1];
    while(i != start2 && j != end){
        if(arr[i] < arr[j]){
            arr2[k] = arr[i];    
            ++i;
        }
        else{
            arr2[k] = arr[j];
            ++j;
        }
        ++k;
    };
    //Fill up arr2 with all remaining elements.
    while(i != start2){
        arr2[k] = arr[i];
        ++k;
        ++i;
    }
    while(j != end){
        arr2[k] = arr[j];
        ++k;
        ++j;
    }
    //Copying elements back into the source array.
    for(int k=0,i=start1;i<end;++i,++k){
        arr[i] = arr2[k];
    }
}
void Mergesort(int arr[], int start, int end){
    if(start == end-1){
        return;
    }
    if(start == 3 && end == 4){
        cout<<"aaa";
    }
    int midpoint = (start+end)/2;
    Mergesort(arr,start,midpoint);
    Mergesort(arr,midpoint,end);
    Merge(arr,start,midpoint,end);
}  

int main(){
    int testArr[] = { 10, 14, 28, 11, 7, 16, 30, 50, 25, 18};
    auto start = high_resolution_clock::now();
    Mergesort(testArr, 0, 10);
    cout<<"The sorted array is: \n";
    for(int i = 0;i < 10; ++i){
        cout<<testArr[i]<<"\t";
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken by function: " << duration.count() <<" microseconds"; 
    return 1;
}