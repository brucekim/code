#include <iostream>
using namespace std;

/* 
(n & (n-1)) == 0이 갖는 의미는
n이 0 또는 1인 비트가 딱 하나있는지 확인하는 것이다
후자는 2의 배수 형태로 바꿔말할 수 있다.
이를 이용하면 해밍 거리를 구할수도 있고,
1인 비트가 몇개인지 셀 수 도 있다.

*/
int main() {
    auto one_haming = [](const int &u, const int &v) -> bool {
        if (u == 0 && v == 0) {
            return false;
        }
        int n = u ^ v;
        return (n & (n - 1)) == 0;
    };
    /* 해밍 거리를 구하는 또다른 방법
       (n & -n) == n
       자기 자신의 2의 보수와 and연산을 하게 되면 해밍거리 1인 경우에만 다시 자기 자신이 된다.
       여기서 2의보수의 역할이 모든 비트를 inverted한 상태에서 1을 더한 값이기 때문에, 다시 and 연산을 하게 되면 원래의 1비트만 남게 된다
    */
    auto one_haming_better = [](const int &u, const int &v) -> bool {
        int n = u ^ v;
        return (n & -n) == n;
    };

    auto count_ones = [](int n) -> int {
        int c;
        for (c = 0; n > 0; ++c) {
            n = n & (n - 1);
        }
        return c;
    };

    cout << one_haming(0b0001, 0b1001) << endl;
    cout << one_haming_better(0b0001, 0b1001) << endl;
    cout << count_ones(0b1111'1111'1111'1100) << endl;
    cout << count_ones(0b1000'0000'0000'0001) << endl;
    cout << count_ones(0b0000'0000'0000'0001) << endl;
    cout << count_ones(0b1000'0000'0000'0000) << endl;
    return 0;
}
