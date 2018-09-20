#include <iostream>
#include <list>
#include <vector>

using namespace std;

const static int n = 3;
int main() {
    int arr[n] = {1, 2, 3};

    auto allsubset = [](int arr[], int n) -> void {
        vector<list<int>> res;
        res.push_back({});
        for (int i = 0; i < n; ++i) {
            int len = res.size();
            for (int j = 0; j < len; ++j) {
                list<int> l = res[j];
                l.push_back(arr[i]);
                res.push_back(l);
            }
        }
        for (auto &&it : res) {
            for (auto &&it2 : it) {
                cout << it2 << " ";
            }
            cout << "\n";
        }
    };

    allsubset(arr, n);
    return 0;
}
