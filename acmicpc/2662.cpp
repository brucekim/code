/* 
link: https://www.acmicpc.net/problem/2662
brute force로 먼저 풀기
시간초과 발생함
o n^m
= o 2^(mlgn)
= 2^(20 * lg300) m = 20, n = 300 일때
~= 2^160 ~= 2^120 sec, 2^30 이 1 sec 걸린다고 가정할때,

memoization으로 풀어야 함
*/
#include <iostream>

using namespace std;

const static int max_n = 300;
const static int max_m = 20;

struct infoList {
    infoList() : n(0), m(0), max_profit(0) {
        for (int i = 0; i < max_m; ++i) {
            best[i] = interim[i] = 0;
        }
        for (int i = 0; i <= max_n; ++i) {
            for (int j = 0; j < max_m; ++j) {
                profitTable[i][j] = 0;
            }
        }
    }
    void copyBest() {
        for (int i = 0; i < m; ++i) {
            best[i] = interim[i];
        }
    }
    void printSol() {
        cout << max_profit << "\n";
        for (int i = 0; i < m; ++i) {
            cout << best[i] << " ";
        }
    }
    int n;
    int m;
    int max_profit;
    int best[max_m];
    int interim[max_m];
    int profitTable[max_n + 1][max_m] = {0};
};

void getMaxProfit(int idx, int invest, int profit, infoList &info) {
    if (invest > info.n) {
        return;
    }
    if (idx == info.m) {
        if (profit > info.max_profit) {
            info.copyBest();
            info.max_profit = profit;
        }
        return;
    }
    for (int i = 0; i <= info.n; ++i) {
        info.interim[idx] = i;
        getMaxProfit(idx + 1, invest + i, profit + info.profitTable[i][idx], info);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tmp;
    infoList info;

    /* input */
    cin >> info.n >> info.m;
    for (int i = 1; i <= info.n; ++i) {
        cin >> tmp;
        for (int j = 0; j < info.m; ++j) {
            cin >> info.profitTable[i][j];
        }
    }

    getMaxProfit(0, 0, 0, info);
    info.printSol();

    return 0;
}
