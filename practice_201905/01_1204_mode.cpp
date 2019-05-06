/* 최빈수 구하기 */

#include <cstdio>

const int max_score = 101;
const int num_students = 1000;

struct mode_info {
    int score;
    int mode;
};
void solve() {
    int n;
    int scores[max_score]{0};
    int st = 0;
    mode_info mode{-1, -1};

    scanf("%d", &n);
    for (int i = 0; i < num_students; ++i) {
        scanf("%d", &st);
        ++scores[st];
    }
    for (int i = 0; i < max_score; ++i) {
        if (mode.mode <= scores[i] && mode.score < i) {
            mode.mode = scores[i];
            mode.score = i;
        }
    }
    printf("#%d %d\n", n, mode.score);
}

int main() {
    int t;
    //freopen("01_1204_input.txt", "r", stdin);
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        solve();
    }
}
