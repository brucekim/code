#include <iostream>

using namespace std;

#define SZ_ALPHA 26
char isPengram(const char buf[], int len) {
    int arr_alpha[SZ_ALPHA] = {0};
    for(int i=0; i<len; i++) {
        if (buf[i] == ' ') {
            continue;
        }
        arr_alpha[buf[i]-'a']++;
    }
    for(int i=0; i<SZ_ALPHA; i++) {
        if (arr_alpha[i] == 0) {
            return 'N';
        }
    }
    return 'Y';
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    char buf[201] = {0};
    char ch = 0;
    int idx = 0;
    while((ch = cin.get()) != '*') {
        if (ch == '\n') {
            cout << isPengram(buf, idx) << endl;
            idx = 0;
            continue;
        }
        buf[idx++] = ch;
    }
    return 0;
}
