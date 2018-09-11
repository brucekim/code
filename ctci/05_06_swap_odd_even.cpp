#include <iostream>
#include <string>

using namespace std;

int main() {
    int bits = 0b11'0101;
    auto swapbits_1 = [](int bits) -> int {
        return (bits << 1 & 0xAAAAAAAA) | (bits >> 1 & 0x55555555);
    };
    auto swapbits_2 = [](int bits) -> int {
        int idx = 0;
        int ret = 0;
        while (bits > 0) {
            ret |= (((bits & 2) >> 1) | (bits & 1) << 1) << idx;
            bits = bits >> 2;
            idx += 2;
        }
        return ret;
    };

    auto printbin = [](int bits) -> void {
        string out;
        while (bits > 0) {
            int bit = bits % 2;
            bits /= 2;
            out = to_string(bit) + out;
        }
        cout << out << endl;
    };

    printbin(bits);
    printbin(swapbits_1(bits));
    printbin(swapbits_2(bits));

    return 0;
}
