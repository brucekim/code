#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    const char a = 'a';
    int mask = 1 << ('a' - a) |
               1 << ('e' - a) |
               1 << ('i' - a) |
               1 << ('o' - a) |
               1 << ('u' - a);
    getline(cin, s);
    int len = s.size();
    for (int i=0; i<len; ++i) {
        cout << s[i];
        if ((1 << (s[i] - a)) & mask) {
            i+=2;
        }
    }
    return 0;
}

