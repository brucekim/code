/*
link: https://www.acmicpc.net/problem/1874
수열의 첫번째부터 읽어나간다. 읽은 수열의 값이 만났던 숫자보다 큰 경우에 그 차이만큼 푸쉬를 하고 1번 팝한다.
읽은 수열의 값이 만났던 숫자보다 작으면 팝한다.
*/
#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    stack<int> st;
    int n, s;
    int v = 0;
    stringstream ss;
    bool valid = true;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        while (s > v) {
            ++v;
            st.push(v);
            ss << "+\n";
        }
        if (st.top() != s) {
            valid = false;
        }
        st.pop();
        ss << "-\n";
    }
    if (valid == true) {
        cout << ss.str().c_str();
    } else {
        cout << "NO";
    }
    return 0;
}
