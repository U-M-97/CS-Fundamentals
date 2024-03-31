#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void bucketSort(float arr[], int size){
    vector<float> *b = new vector<float>[size];

    for(int i = 0; i < size; i++){
        int index = size * arr[i];
        b[index].push_back(arr[i]);
    }

    for(int i = 0; i < size; i++){
        sort(b[i].begin(), b[i].end());
    }

    int index = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < b[i].size(); j++){
            arr[index++] = b[i][j];
        }
    }
}

int main(){
    float arr[] = {0.897, 0.3434,0.665, 0.1234, 0.656,  0.565 };
    int size = sizeof(arr) / sizeof(arr[0]);
    bucketSort(arr, size);
    
    for(int i = 0; i < size; i++){
        cout << arr[i] << endl;
    }
}