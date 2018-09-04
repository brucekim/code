#include <iostream>

using namespace std;

int stratum(int a1, int a2, int b1, int b2) {
    if (a1 > b2 || a2 < b1) {
        return 0;
    } else if (a1 == b2 || a2 == b1) {
        return 1;
    } else {
        return 2;
    }
}
int main() {
    int a[4], b[4];
    char ans[] = {'d', 'c', 'b', ' ', 'a'};
    for (int t = 4; t > 0; --t) {
        cin >> a[0] >> a[1] >> a[2] >> a[3];
        cin >> b[0] >> b[1] >> b[2] >> b[3];
        cout << ans[stratum(a[0], a[2], b[0], b[2]) * stratum(a[1], a[3], b[1], b[3])] << endl;
    }
    return 0;
}
