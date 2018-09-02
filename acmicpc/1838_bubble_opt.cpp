#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 500000
inline void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}
int bubble(int arr[], int n) {
    int flag = 0;
    for (int i = 0; i < n; ++i) {
        flag = 0;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                flag = 1;
                swap(arr[j], arr[j + 1]);
            }
        }
        if (flag == 0) {
            flag = i;
            break;
        }
    }
    return flag;
}
void test() {
    int arr[MAX_N];
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    cout << bubble(arr, n) << endl;
}
int main() {
    test();
    return 0;
}
