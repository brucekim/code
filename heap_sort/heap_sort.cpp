//
//  main.cpp
//  heap_sort
//
//  Created by 김인태 on 2018. 8. 14..
//  Copyright © 2018년 김인태. All rights reserved.
//

#include <iostream>
using namespace std;

void swap(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}
void max_heapify(int arr[], int n, int i) {
    int l = 2*i + 1;
    int r = 2*i + 2;
    
    int largest = i;
    if (l < n && arr[l] > arr[i])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (i != largest) {
        swap(arr[largest], arr[i]);
        max_heapify(arr, n, largest);
    }
    
}


void heap_sort(int arr[], int n) {
    
    //build max heap
    for(int i = n/2 - 1; i>=0; i--) {
        max_heapify(arr, n, i);
    }
    
    //sort - move max to the end and heapify
    for (int i=n-1; i>0; i--) {
        cout << "max: " << arr[0] << endl;
        swap(arr[0], arr[i]);
        max_heapify(arr, i, 0);
    }
}

void test() {
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(arr) / sizeof(int);
    
    heap_sort(arr, n);
    
    for (auto &&it : arr) {
        cout << it << " ";
    }
    cout << endl;
    
}
int main(int argc, const char * argv[]) {
    test();
    return 0;
}
