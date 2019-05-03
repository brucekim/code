#include <iostream>
#include <vector>

using namespace std;

int main() {
    string teststr = "abc";

    auto allpermutation = [](const string &str) -> void {
        vector<vector<char>> res;
        res.push_back({});
        for (int i = 0; i < str.size(); ++i) {
            int len = res.size();
            for (int j = 0; j < len; ++j) {
                vector<char> l = res[j];
                l.push_back(str[i]);
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

    allpermutation(teststr);
    return 0;
}
