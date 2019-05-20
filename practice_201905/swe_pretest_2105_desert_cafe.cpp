#include <cstdio>

#define  DBG
#define DBG_STDIN

#ifdef DBG
#define dbg_msg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg_msg(fmt, ...)
#endif

const static int const_max_n = 20;
const static int const_max_v= 101;

void clear (bool *visited) {
    for(int i=0; i<const_max_v; ++i) {
        visited[i] = false;
    }
}

void solve() {
    int n, tmp;
    int cafe[const_max_n][const_max_n]{{0}};
    bool visited[const_max_v]{0};
    scanf("%d", &n);

    // input & init
    for (int i=0; i<const_max_n; ++i) {
        for (int j=0; j<const_max_n; ++j) {
            cafe[i][j] =  0;
        }
    }
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            scanf("%d", &tmp);
            cafe[i][j] =  tmp;
        }
    }

    int max_size = -1;
    bool giveup = false;

    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            for (int a=1; a<n; ++a) {
                for (int b=1; b<n; ++b) {
                    clear(visited);
                    giveup = false;

                    if (i+a+b >= n || j-b < 0 || j+a >= n) {
                        continue;
                    }
                    if (2*(a+b) < max_size) {
                        continue;
                    }
                    for(int k=0; k<a; ++k) {
                        int tmp = cafe[i+k][j+k];
                        if (visited[tmp] == true) {
                            giveup = true;
                            break;
                        } else {
                            visited[tmp] = true;
                        }
                    }
                    if (giveup == true) {
                        continue;
                    } 
                    for(int k=0; k<b; ++k) {
                        int tmp = cafe[i+a+k][j+a-k];
                        if (visited[tmp] == true) {
                            giveup = true;
                            break;
                        } else {
                            visited[tmp] = true;
                        }
                    }
                    if (giveup == true) {
                        continue;
                    } 
                    for(int k=0; k<a; ++k) {
                        int tmp = cafe[i+a+b-k][j+a-b-k];
                        if (visited[tmp] == true) {
                            giveup = true;
                            break;
                        } else {
                            visited[tmp] = true;
                        }
                    }
                    if (giveup == true) {
                        continue;
                    } 
                     for(int k=0; k<b; ++k) {
                        int tmp = cafe[i+b-k][j-b+k];
                        if (visited[tmp] == true) {
                            giveup = true;
                            break;
                        } else {
                            visited[tmp] = true;
                        }
                    }
                    if (giveup == true) {
                        continue;
                    } 
                    max_size = 2*(a+b);
                }
            }
        }
    }
    printf("%d\n", max_size);

}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/swe_pretest_2105_input.txt", "r", stdin);
#endif
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        printf("#%d ", i+1);
        solve();
    }
    return 0;
}
