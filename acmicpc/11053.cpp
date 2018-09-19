/*
link: https://www.acmicpc.net/problem/11053
lis,
d[i] = 1 + max(d[j]),  0 < j < i, arr[j] < arr[i]

*/
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    int A[1001] = {0};
    int lis[1001] = {0};

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> A[i];
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int max = 0;
        for (int j = 1; j < i; ++j) {
            if ((A[j] < A[i]) && lis[j] > max) {
                max = lis[j];
            }
        }
        lis[i] = 1 + max;
        if (ans < lis[i]) {
            ans = lis[i];
        }
    }
    cout << ans;
    return 0;
}
