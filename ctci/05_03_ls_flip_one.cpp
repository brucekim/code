#include <iostream>
#include <vector>
using namespace std;

int longestOne(int in) {
    vector<vector<int>> v;
    v.push_back(vector<int>());
    int idx = 0;

    bool flag = false;
    while (in > 0) {
        int b = in % 2;
        if (b == 1) {
            v[idx].push_back(1);
            flag = false;
        } else if (b == 0 && flag == false) {
            flag = true;
            v.push_back(vector<int>());
            ++idx;
        }
        in /= 2;
    }
    if (idx == 0) {
        return v[0].size();
    }
    int max = 0;
    for (int i = 0; i < idx; ++i) {
        int t = v[i].size() + v[i + 1].size();
        if (t > max) {
            max = t;
        }
    }
    return max + 1;
}

int main() {
    int in = 0b1111;
    cout << longestOne(in) << endl;
    in = 0b01111;
    cout << longestOne(in) << endl;
    in = 0b11110;
    cout << longestOne(in) << endl;
    in = 0b1110101111;
    cout << longestOne(in) << endl;
    return 0;
}
