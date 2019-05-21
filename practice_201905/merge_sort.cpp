#include <cstdio>

#define dbg_msg(fmt, ...) printf(fmt, ##__VA_ARGS__)

void merge(int *arr, int l, int m, int r) {
    int n1 = m-l+1;
    int n2 = r-m;

    int *arra = new int[n1];
    int *arrb = new int[n2];
    for(int i=0; i<n1; ++i) {
        arra[i] = arr[l+i];
    }
    for(int i=0; i<n2; ++i) {
        arrb[i] = arr[m+1+i];
    }
    int i=0;
    int j=0;
    int k=l;
    while(i < n1 && j < n2) {
        if (arra[i] < arrb[j]) {
            arr[k++] = arra[i++];
        } else {
            arr[k++] = arrb[j++];
        }
    }
    while(i < n1) {
        arr[k++] = arra[i++];
    }

    while (j < n2) {
        arr[k++] = arrb[j++];
    }

    delete arra;
    delete arrb;
}

void merge_sort(int *arr, int l, int r) {
    printf("chunk: ");
    for(int i=l; i<=r; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    if (l < r) {
        int m = l + (r-l)/2;
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void solve() {
    int arr[10] = {5, 4, 3, 2, 1, 10, 30, 20, 50, 40};
    merge_sort(arr, 0, 9);

    for(int i=0; i<10; ++i) {
        printf("%d ", arr[i]);
    }
}

int main() {
    solve();
    return 0;
}
