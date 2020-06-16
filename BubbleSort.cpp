#include <iostream>
#include <chrono> 
using namespace std;
using namespace std::chrono;
// A bubble sort function that sorts in ascending order - 35 microseconds.
void BubbleSort(int arr[], int n){
    int temp, min = arr[0];
    for(int i = 0;i < n;++i){
        for(int j=0;j < n-i-1; ++j){
            if(arr[j+1]<arr[j]){
                temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main(){
    int testArr[] = { 10, 14, 28, 11, 7, 16, 30, 50, 25, 18};
    auto start = high_resolution_clock::now();
    BubbleSort(testArr, 10);
    cout<<"The sorted array is: \n";
    for(int i = 0;i < 10; ++i){
        cout<<testArr[i]<<"\t";
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken by function: " << duration.count() <<" microseconds"; 
    return 1;
}