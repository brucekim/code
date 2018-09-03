#include <iostream>
using namespace std;

#define MAX 1000000

int main() {
    //ios_base::sync_with_stdio(false);

    int n = 0;
    int max = 0;
    int lis = 0;
    int arr_lis[MAX + 1] = {0};
    int d[MAX + 1] = {0};

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> arr_lis[i];
    }
    for (int i = 1; i <= n; ++i) {
        int p = arr_lis[i];
        d[p] = d[p - 1] + 1;
        if (d[p] > max) {
            max = d[p];
        }
    }
    cout << n - max;
    return 0;
}
