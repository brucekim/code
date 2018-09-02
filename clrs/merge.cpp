
#include <iostream>
#include <fstream>
using namespace std;

void merge(int arr[], int l, int m, int r) {
    int nl = m-l;

    int arr[nl];

}

void merge_sort(int arr[], int l, int r) {
    
    if (l < r) {
        int m = l + (r-l)/2;
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

void test() {
    int arr[100] = {0};
    int n;
    std::ifstream input("input\\unsorted.txt");
    input >> n;
    for(int i=0; i<n; i++) {
        input >> arr[i];
    }
    int m = n / 2;
    merge_sort(arr, 0, n-1);

    for (int i=0; i<n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
int main() {
    test();
    return 0;
}
