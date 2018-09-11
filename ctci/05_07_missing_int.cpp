#include <iostream>
using namespace std;

int main() {
    int A[5] = {0, 1, 3, 4, 5};
    auto fetch_jth_bit = [](int a, int j) -> bool {
        return a & (1 << j);
    };
    int expected_sum = (1 + 5) * (5 / 2) + 3;
    int cumulated = 0;

    for (int i = 0; i < 5; ++i) {
        int integer = 0;
        for (int j = 0; j < 32; ++j) {
            integer |= (fetch_jth_bit(A[i], j) << j);
        }
        cumulated += integer;
    }
    cout << expected_sum - cumulated;

    return 0;
}
