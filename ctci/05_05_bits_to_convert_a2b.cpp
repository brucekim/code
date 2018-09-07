/*
a를 b로 바꾸기위해 뒤집어야 하는 비트의 개수는
a와 b를 xor한다음에 1인 bit를 하나씩 세어야 한다
05.04에 나왔던 n&(n-1)을 이용하면 1의 개수를 모든 비트를 검사하지 않아도 셀 수 있다
*/
#include <iostream>
using namespace std;

int main() {
    auto a2b = [](int a, int b) -> void {
        int t = a ^ b;
        int c;
        for (c = 0; t > 0; ++c) {
            t = t & (t - 1);
        }
        cout << c << endl;
    };

    a2b(31, 14);
    a2b(29, 15);

    return 0;
}
