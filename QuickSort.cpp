#include <iostream>
#include <chrono> 
using namespace std;
using namespace std::chrono;
//A QuickSort sorting function that sorts in ascending order - 29 microseconds.
int partition(int arr[], int left, int right){
    int temp,pivot = arr[(left+right)/2];
    while(left <= right){
        while(arr[left] < pivot)
            ++left;
        while(arr[right] > pivot)
            --right;
        if(left <= right){
            temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    };
    return left;
}

void QuickSort(int arr[], int left, int right){
    int index = partition(arr,left,right);
    if(left < index - 1){           //Sort left half
        QuickSort(arr,left,index-1);
    }
    if(index < right){
        QuickSort(arr,index,right);
    }
}

int main(){
    int testArr[] = { 10, 14, 28, 11, 7, 16, 30, 50, 25, 18};
    auto start = high_resolution_clock::now();
    QuickSort(testArr, 0, 9);
    cout<<"The sorted array is: \n";
    for(int i = 0;i < 10; ++i){
        cout<<testArr[i]<<"\t";
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken by function: " << duration.count() <<" microseconds"; 
    return 1;
}

