#include <iostream>
using namespace std;

#define MAX 10000
void d(int n, bool visit[]) {
    int p = n;
    while (n > 0) {
        p += n % 10;
        n /= 10;
    }
    if (p > MAX) {
        return;
    }
    visit[p] = true;
    d(p, visit);
}

void selfnum() {
    bool visit[MAX + 1] = {false};
    for (int i = 1; i <= MAX; ++i) {
        if (visit[i] == true) {
            continue;
        }
        cout << i << "\n";
        d(i, visit);
    }
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    selfnum();

    return 0;
}
