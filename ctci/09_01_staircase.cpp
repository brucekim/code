#include <chrono>
#include <iostream>
using namespace std;
/*

1 or 2 or 3 steps ok--
53798080
memo time: 1.2893e-05
53798080
brute time: 0.462665
all steps ok--
117897839
memo time: 3.084e-06
536870912
brute time: 5.4808

*/

const static int ARR_MAX = 1'000'000;
int howtosteps(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    return howtosteps(n - 1) + howtosteps(n - 2) + howtosteps(n - 3);
}
int howtosteps_memo(int n, int arr[]) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    if (arr[n] != 0) {
        return arr[n];
    }
    arr[n] = howtosteps_memo(n - 1, arr) + howtosteps_memo(n - 2, arr) + howtosteps_memo(n - 3, arr);
    return arr[n];
}
int howtostepsall(int n) {
    if (n == 0) {
        return 1;
    }
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += howtostepsall(n - i);
    }
    return sum;
}
int howtostepsall_memo(int n, int arr[]) {
    if (n == 0) {
        arr[n] = 1;
        return 1;
    }
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (arr[i] != 0) {
            sum += arr[i];

        } else {
            arr[i] = howtostepsall_memo(n - i, arr);
            sum += arr[i];
        }
    }
    return sum;
}
int main() {
    int n = 30;

    std::chrono::high_resolution_clock::time_point t1, t2;
    std::chrono::duration<double> diff;

    cout << "1 or 2 or 3 steps ok--" << endl;
    /* memoziation */
    int arr[ARR_MAX] = {0};
    t1 = std::chrono::high_resolution_clock::now();
    cout << howtosteps_memo(n, arr) << endl;
    t2 = std::chrono::high_resolution_clock::now();
    diff = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    cout << "memo time: " << diff.count() << endl;

    /* brute force */
    t1 = std::chrono::high_resolution_clock::now();
    cout << howtosteps(n) << endl;
    t2 = std::chrono::high_resolution_clock::now();
    diff = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    cout << "brute time: " << diff.count() << endl;

    cout << "all steps ok--" << endl;
    t1 = std::chrono::high_resolution_clock::now();
    cout << howtostepsall_memo(n, arr) << endl;
    t2 = std::chrono::high_resolution_clock::now();
    diff = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    cout << "memo time: " << diff.count() << endl;

    t1 = std::chrono::high_resolution_clock::now();
    cout << howtostepsall(n) << endl;
    t2 = std::chrono::high_resolution_clock::now();
    diff = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    cout << "brute time: " << diff.count() << endl;
    return 0;
}
