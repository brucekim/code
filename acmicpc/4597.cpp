#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    char ch;
    int cnt_1 = 0;
    while ((ch = cin.get()) != '#') {
        if (ch == 'o') {
            if (cnt_1 % 2 == 0) {
                ch = '1';
            } else {
                ch = '0';
            }
        } else if (ch == 'e') {
            if (cnt_1 % 2 == 0) {
                ch = '0';
            } else {
                ch = '1';
            }
        } else if (ch == '\n') {
            cnt_1 = 0;
        } else if (ch == '1') {
            ++cnt_1;
        }
        cout << ch;
    }

    return 0;
}
