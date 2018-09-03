#include <iomanip>
#include <iostream>
using namespace std;

int insert(int n, int m, int i, int j) {
    int mask = 0;
    for (int k = j; k >= i; --k) {
        mask |= 1 << k;
    }
    n = (n & (~mask)) | (m << i);
    return n;
}
void printBin(int d) {
    if (d > 0) {
        printBin(d >> 1);
        cout << (d & 0x01);
    }
}
int main() {
    int n = 0b100'0000'0000;
    int m = 0b1'0011;
    int i = 2;
    int j = 6;
    insert(n, m, i, j);
    printBin(insert(n, m, i, j));

    return 0;
}
