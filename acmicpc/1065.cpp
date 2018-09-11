/*
link: https://www.acmicpc.net/problem/1065
주어진 숫자에서 첫번째 자리수를 빼낸다
나머지 숫자가 0보다 크면 나머지 숫자 중에 첫번째 자리수와 diff를 구한다. 그리고 나머지 숫자가 0보다 작을때까지 diff를 더해서 다음 자리수가 등차수열인지 판별한다
*/
#include <iostream>
using namespace std;

int main() {
    int n, sum = 0;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto hansu = [](int n) -> bool {
        int f = n % 10;
        n /= 10;
        int diff = f - (n % 10);
        while (n > 0) {
            if ((f - (n % 10)) != diff) {
                return false;
            }
            f = n % 10;
            n /= 10;
        }
        return true;
    };

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        if (hansu(i) == true) {
            ++sum;
        }
    }
    cout << sum;
    return 0;
}
