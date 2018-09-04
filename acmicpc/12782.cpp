#include <iostream>
using namespace std;

int getNum(string &n, string &m) {
    int len = n.length();
    int n_1 = 0;
    int m_1 = 0;
    int ret = 0;
    for (int i = 0; i < len; i++) {
        if (n[i] != m[i]) {
            if (n[i] == '1') {
                ++n_1;
            } else {
                ++m_1;
            }
        }
    }
    return ret = max(n_1, m_1);
}

int main() {
    int t;
    string n, m;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        cin >> n >> m;
        cout << getNum(n, m) << "\n";
    }

    return 0;
}
