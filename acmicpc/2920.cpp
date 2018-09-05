#include <iostream>
using namespace std;

int main() {
    int arr[8] = {0};
    for (int i = 0; i < 8; ++i) {
        cin >> arr[i];
    }
    int diff = arr[1] - arr[0];
    int i, t = 0;
    for (i = 1; i < 8; ++i) {
        if (arr[i - 1] + diff != arr[i]) {
            cout << "mixed";
            break;
        }
    }
    if (i == 8) {
        if (diff > 0) {
            cout << "ascending";
        } else {
            cout << "descending";
        }
    }
    return 0;
}
