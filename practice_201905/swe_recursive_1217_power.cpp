/* n power m */
#include <cstdio>

int power(int n, int m) {
    if (m == 1) {
        return n;
    }
    return n * power(n, m-1);
}

void solve() {
    int tc, n, m;
    scanf("%d", &tc);
    scanf("%d %d", &n, &m);

    printf("#%d %d\n", tc, power(n, m));
}

int main() {
    for (int i=0; i<10; ++i) {
        solve();
    }
    return 0;
}
