/*
link: https://www.acmicpc.net/problem/2485
임의의 간격으로 떨어져있는 가로수들을 모두 같은 간격이 되도록 가로수를 추가로 심는데 최소한의 가로수를 구해야 한다.
이미 심어져있는 간격들 의 최대공약수를 구해서 그 간격대로 가로수를 심는 것이 아이디어이다.
*/
#include <iostream>
using namespace std;

int getGcd(int a, int b) {
    return b == 0 ? a : getGcd(b, a % b);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, gcd, ans = 0;
    int arr[100'000] = {0};

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    gcd = arr[1] - arr[0];
    for (int i = 2; i < n; ++i) {
        gcd = getGcd(gcd, arr[i] - arr[i - 1]);
    }
    for (int i = 1; i < n; ++i) {
        ans += (arr[i] - arr[i - 1]) / gcd - 1;
    }
    cout << ans;

    return 0;
}

#ifdef COMMENT
1차 풀이 int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    /* init */
    int n, diff, cnt, gcd;
    cnt = gcd = 0;
    int arr[100'000] = {0};

    /* gcd */
    auto get_gcd = [](int a, int b) -> int {
        int t;
        while (b != 0) {
            t = b;
            b = a % b;
            a = t;
        }
        return a;
    };

    /* get input and calc gcd */
    cin >> n;
    cin >> t1;
    arr[0] = t1;
    for (int i = 1; i < n; ++i) {
        cin >> t2;
        arr[i] = t2;
        diff = t2 - t1;
        if (gcd == 0) {
            gcd = diff;
        } else {
            gcd = get_gcd(gcd, diff);
        }
        t1 = t2;
    }
    /* plant tree on empty */
    t1 = arr[0];
    for (int i = 1; i < n; ++i) {
        cnt += (arr[i] - t1) / gcd - 1;
        t1 = arr[i];
    }
    cout << cnt;

    return 0;
}
#endif
