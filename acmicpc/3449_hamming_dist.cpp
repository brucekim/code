#include <iostream>
using namespace std;

void sol() {
    string s1;
    string s2;
    cin >> s1 >> s2;
    int dist = 0;
    for (int i = 0; i < s1.size(); ++i) {
        if (s1[i] != s2[i]) {
            dist++;
        }
    }
    cout << "Hamming distance is " << dist << ".\n";
}
int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        sol();
    }
    return 0;
}
