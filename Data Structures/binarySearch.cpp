#include <iostream>
using namespace std;

int binarySearch(int arr[], int x, int low, int high){
    if(high >= low){
        int mid = low + (high - low) / 2;

        if(arr[mid] == x){
            return mid;
        }

        if(arr[mid] > x){
            return binarySearch(arr, x, low, mid - 1);
        }

        if(arr[mid] < x){
            return binarySearch(arr, x, mid + 1, high);
        }
    }
    
    return -1;
}

int main(){
    int arr[] = { 2, 3, 4, 10, 40 };
    int x = 10;
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = binarySearch(arr, x, 0, n - 1);
    result == -1 ? cout << "element is not present" : cout << "element is present at index " << result;
}