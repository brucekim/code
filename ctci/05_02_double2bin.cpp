#include <unistd.h>
#include <iostream>
#include <string>
using namespace std;

string printBin(int i) {
    string str;
    while (i > 0) {
        str.insert(0, to_string(i % 2));
        i = i / 2;
    }
    return str;
}
string printBin(double d) {
    string str_int;
    string str_dp = "";
    double dp = d - static_cast<int>(d);
    int cnt = 0;
    while ((cnt < 32) && (dp > 0)) {
        dp = dp * 2;
        if (dp >= 1) {
            str_dp.append("1");
            dp -= 1;
        } else {
            str_dp.append("0");
        }
        ++cnt;
    }
    if (cnt == 32) {
        str_dp = "ERROR";
    }

    str_int = printBin(static_cast<int>(d));
    return str_int + "." + str_dp;
}
int main() {
    double d1 = 8.125;

    cout << printBin(d1);
    return 0;
}
