/*
link: https://www.acmicpc.net/problem/10211
주어진 배열에서 각 원소의 합이 가장 큰 부분 배열을 찾는 maximum subarray problem을 푸는 문제
부분 집합이 아니라 부분 배열이다. 부분 배열이기 때문에 연속적으로 이어진 원소들의 집합이 된다.

슬라이딩 윈도우가 오른쪽으로 늘어나는데, 윈도우내에 있는 원소의 합이 음수가 되면 윈도우 왼쪽을 shrink한다.
슬라이딩 윈도우내에 있는 원소의 합이 최대인 값을 찾는다.

*/
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, n;
    int arr[1001] = {0};
    auto max_subarr = [](const int arr[], int n) -> int {
        int max_sum_global = -1000;
        int max_sum_local = 0;
        for (int i = 0; i < n; ++i) {
            max_sum_local += arr[i];
            if (max_sum_global < max_sum_local) {
                max_sum_global = max_sum_local;
            }
            if (max_sum_local < 0) {
                max_sum_local = 0;
            }
        }
        return max_sum_global;
    };

    cin >> t;
    for (int i = 0; i < t; ++i) {
        cin >> n;
        for (int j = 0; j < n; ++j) {
            cin >> arr[j];
        }
        cout << max_subarr(arr, n) << "\n";
    }
    return 0;
}
