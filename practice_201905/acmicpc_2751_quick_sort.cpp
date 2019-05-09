/* 1 <= n <= 1'000'000
*/
#include <cstdio>

static const int N_MAX = 1'000'000;

inline void swap(int &a, int&b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int partition(int arr[], int low, int high) {
    int i = low-1;
    int pivot = arr[high];
    for (int j=low; j<high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi-1);
        quick_sort(arr, pi+1, high);
    }
}

void test() {
    auto print = [](int arr[], int n) -> void {
        for(int i=0; i<n; ++i) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    };
    int arr[] = {5, 3, 1, 2, 4};
    int n = sizeof(arr) / sizeof(int);
    print(arr, n);
    quick_sort(arr, 0, 4);
    print(arr, n);
}

void solve() {
    int arr[N_MAX] = {0};
    int n;
    int t;
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        scanf("%d", &t);
        arr[i] = t;
    }

    quick_sort(arr, 0, n-1);
}

int main() {
    test();
    //solve();
    return 0;
}
