#include <cstdio>

#define DBG_STDIN

int graph[20][20];
int dist[20][20];

int floydwarshall(int n) {

    for(int k=0; k<n; ++k) {
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                if (i==k || j==k)
                    continue;
                if (dist[i][k] + dist[k][j] == dist[i][j]) {
                    graph[i][j] = 0;
                } else if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    return -1;
                }
            }
        }
    }

    int ans = 0;
    for(int i=0; i<n; ++i) {
        for(int j=i; j<n; ++j) {
            ans += graph[i][j];
        }
    }
    return ans;
}
void info(int N) {
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}
void solve() {
    int N, tmp;
    scanf("%d", &N);

    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            int tmp;
            scanf("%d", &tmp);
            graph[i][j] = dist[i][j] = tmp;
        }
    }

    int ans = floydwarshall(N);
    printf("%d\n", ans);
}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/acmicpc_1507_input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
