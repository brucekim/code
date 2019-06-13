/*
 * https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
       graph[][] = { {0,   5,  INF, 10},
                    {INF,  0,  3,  INF},
                    {INF, INF, 0,   1},
                    {INF, INF, INF, 0} }
which represents the following graph
             10
       (0)------->(3)
        |         /|\
      5 |          |
        |          | 1
       \|/         |
       (1)------->(2)

*/
#include <stdio.h>

const static int INF = 0x7ffffff;
const static int V = 4;

void floydwarshall(int g[][V]) {
    int dist[V][V];

    // init - copy
    for(int i=0; i<V; ++i) {
        for(int j=0; j<V; ++j) {
            dist[i][j] = g[i][j];
        }
    }

    for(int k=0; k<V; ++k) {
        for(int i=0; i<V; ++i) {
            for(int j=0; j<V; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for(int i=0; i<V; ++i) {
        for(int j=0; j<V; ++j) {
            if (dist[i][j] != INF) {
                printf("%d ", dist[i][j]);
            } else {
                printf("# ");
            }
        }
        printf("\n");
    }
}
void solve() {
    int g[V][V] = { {0, 5, INF, 10},
                    {INF, 0, 3, INF},
                    {INF, INF, 0, 1},
                    {INF, INF, INF, 0}
    };

    floydwarshall(g);
}

int main() {
    solve();
    return 0;
}
