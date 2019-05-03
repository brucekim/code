#include <iostream>
using namespace std;

void test(int n) {
    int c1 = 0;
    int c0 = 0;
    while (n > 0) {
        if (n % 2 == 1) {
            ++c1;
        } else {
            ++c0;
        }
        n /= 2;
    }
    cout << c;
}
int main() {
    test(20);
    return 0;
}
