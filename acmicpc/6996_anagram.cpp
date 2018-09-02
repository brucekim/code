#include <iostream>
using namespace std;

bool isAnagram(string &a, string &b) {
    int alpha[26] = {0};
    for (string::iterator it = begin(a); it != end(a); ++it) {
        ++alpha[*it - 'a'];
    }
    for (string::iterator it = begin(b); it != end(b); ++it) {
        --alpha[*it - 'a'];
    }
    for (int i = 0; i < 26; ++i) {
        if (alpha[i] != 0) {
            return false;
        }
    }
    return true;
}
void test() {
    int tc;
    cin >> tc;
    string a, b;
    for (int i = 0; i < tc; ++i) {
        cin >> a >> b;
        cout << a << " & " << b << " are";
        cout << (isAnagram(a, b) == true ? " " : " NOT ")
             << "anagrams." << endl;
    }
}
int main() {
    test();
    return 0;
}
