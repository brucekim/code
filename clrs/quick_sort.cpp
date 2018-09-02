#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
int partition(int arr[], int l, int h) {
    int pivot = arr[h];

    int i = l-1;

    for (int j=l; j<=h-1; j++) {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[h]);
    return i+1;

    
}

void quick_sort(int arr[], int l, int h) {
    /* 
    1. pivot
    2. partition
    */
   if (l < h) {
       int p = partition(arr, l, h);

       quick_sort(arr, l, p-1);
       quick_sort(arr, p+1, h);
   }
}

void test() {
    int arr[100] = {0};

    std::ifstream input("input\\unsorted.txt", std::ios_base::in);
    int n;
    input >> n;

    for (int i=0; i<n; i++) {
        input >> arr[i];
    }

    quick_sort(arr, 0, n-1);
    
    for (int i=0; i<n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

}

int main()
{
    test();
    return 0;
}
