#include <iostream>
using namespace std;

int score(const string &str) {
    int sum = 0;
    int c = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == 'O') {
            sum += ++c;
        } else {
            c = 0;
        }
    }
    return sum;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    string str;
    str.resize(100);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> str;
        cout << score(str) << "\n";
    }
    return 0;
}
