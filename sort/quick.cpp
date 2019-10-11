#include <iostream>
using namespace std;

void Swap(int arr[], int idx1, int idx2) {
    
    int temp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;
}

int Partition(int arr[], int left, int right) {
    int mid = (left + right) / 2;
    Swap(arr, left, mid);
    
    int pivot = arr[left];
    int i = left, j = right;
    
    while(i < j) {
        while(pivot < arr[j]) j--;
        while(i < j && pivot >= arr[i]) i++;
        Swap(arr, i, j);
    }
    
    arr[left] = arr[i];
    arr[i] = pivot;
    return i;
}

void QuickSort(int arr[], int left, int right) {
    if(left <= right) {
        int pivot = Partition(arr, left, right);
        QuickSort(arr, left, pivot-1);
        QuickSort(arr, pivot+1, right);
    }
}

int main(void) {
    
    int arr[] = {3, 2, 4, 1, 7, 6 , 5};
    
    QuickSort(arr, 0, sizeof(arr)/sizeof(int)-1);
    
    for(int v : arr) cout << v << ' ';
    cout << '\n';
    
    return 0;
}
