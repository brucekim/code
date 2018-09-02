#include <iostream>

using namespace std;

int main() {
    char ch;
    int cnt = 0;
    bool flag = true;
    while ((ch = cin.get()) != '\n') {
        if (ch == ' ') {
            flag = true;
        } else {
            if (flag == true) {
                cnt++;
            }
            flag = false;
        }
    }
    cout << cnt;
    return 0;
}
