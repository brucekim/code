/*
link: https://www.acmicpc.net/problem/9012
괄호 문자열의 쌍이 유효한 지 판단하는 문제이다.
stack구조에서 '('이 push ')'이 pop이라 생각하고
짝이맞게 push/pop을 수행해서 마지막에서는 stack이 empty인지 판단한다.
*/
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    char arr[51] = {0};
    int t;
    auto vps = [](char arr[]) -> string {
        int st = 0;
        bool vps = true;
        for (int i = 0; arr[i] != '\0'; ++i) {
            if (arr[i] == '(') {
                ++st;
            } else {
                --st;
            }
            if (st < 0) {
                vps = false;
            }
        }
        if (st != 0) {
            vps = false;
        }
        return vps == true ? "YES" : "NO";
    };

    cin >> t;
    for (int i = 0; i < t; ++i) {
        cin >> arr;
        cout << vps(arr) << "\n";
    }
    return 0;
}
