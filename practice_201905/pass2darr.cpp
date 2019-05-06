#include <cstdio>

template <typename T>
void pass2dArrT(T &arr) {
    arr[5][5] = 1;
}
template <size_t sz_x, size_t sz_y>
void pass2dArrSz(int (&arr)[sz_x][sz_y]) {
    arr[4][4] = 1;
}

template <typename T>
void print2darr(T &arr) {
    int sz_y = sizeof(arr[0]) / sizeof(int);
    int sz_x = sizeof(arr) / sz_y / sizeof(int);
    for (int i = 0; i < sz_x; ++i) {
        for (int j = 0; j < sz_y; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int arr[10][10]{0};
    pass2dArrT(arr);
    pass2dArrSz(arr);
    print2darr(arr);
}
