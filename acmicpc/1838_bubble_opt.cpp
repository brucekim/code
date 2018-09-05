#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 500000
int getIdx(int arr[], int s, int e, int d) {
    if (s <= e) {
        int m = s + (e - s) / 2;
        if (d == arr[m]) {
            for (int i = m - 1; i >= s; --i) {
                if (d == arr[i]) {
                    m = i;
                } else {
                    break;
                }
            }
            return m;
        }
        if (d < arr[m]) {
            return getIdx(arr, s, m - 1, d);
        } else {
            return getIdx(arr, m + 1, e, d);
        }
    }
    return -1;
}
int test() {
    int arr[MAX_N + 1] = {0};
    int sort_arr[MAX_N + 1] = {0};
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        sort_arr[i] = arr[i];
    }
    sort(sort_arr, sort_arr + n);
    int max = 0;
    for (int i = 0; i < n; ++i) {
        int t = getIdx(sort_arr, 0, n, arr[i]);
        if (i - t > max) {
            max = i - t;
        }
    }
    return max;
}
int main() {
    cout << test();
    return 0;
}
