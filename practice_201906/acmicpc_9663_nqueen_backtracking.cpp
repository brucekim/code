#include <stdio.h>
#include <time.h>

bool col[16];
bool inc[31];
bool dec[31];

class meas {
    public:
        meas() {
            start = clock();
        }
        ~meas() {
            end = clock();
            duration = static_cast<double>(end-start);
            printf("consume..%lf\n", duration/CLOCKS_PER_SEC);
        }
        time_t start, end;
        double duration;
};

class solver {
    public:
        solver() : ans (0) {
            scanf("%d", &N);
            cols = new int[N+1];
            checks = new bool[((N+1)*2)*3];


            //init
            for(int i=0; i<N+1; ++i) {
                cols[i] = 0;
            }
            for(int i=0; i<((N+1)*2)*3; ++i) {
                checks[i] = false;
            }
        }
        virtual ~solver() {
            delete[] cols;
            delete[] checks;
        }
        int run() {
            queens_fast(0);
            return ans;
        }
        void queens_naive(int level) {
            if  (level == N) {
                ++ans;
                return;
            }
            
            for (int i=1; i<=N; ++i) {
                cols[level+1] = i;

                if (promising_naive(level+1) == true) {
                    queens_naive(level+1);
                }
                cols[level+1] = 0;
            }
        }

        bool promising_naive(int level) {
            for (int i=1; i<level; ++i) {
                if (cols[i] == cols[level])
                    return false;
                else if (level-i == abs(cols[level] - cols[i]))
                    return false;
            }
            return true;
        }

        void queens_fast(int level) {
            if (level == N) {
                ++ans;
                return;
            }

            for(int i=1; i<=N; ++i) {
                if (promising_fast(level, i) == true) {

                    col[i] = inc[level+i] = dec[level-i+N+1] = true;
                    queens_fast(level+1);
                    col[i] = inc[level+i] = dec[level-i+N+1] = false;
                }
            }
        }
        inline bool promising_fast(int level, int i) {
            return col[i] == false && inc[level+i] == false && dec[level-i+N+1] == false;
        }
        void queens_fast_2(int r) {
            if (r > N) {
                ans++;
                return;
            }
            for (int i = 1; i <= N; i++) {
                if (!col[i] && !inc[r + i] && !dec[N + (r - i) + 1]){
                    col[i] = inc[r + i] = dec[N + (r - i) + 1] = true;
                    queens_fast_2(r + 1);
                    col[i] = inc[r + i] = dec[N + (r - i) + 1] = false;
                }
            }
        }

        void info() {
            printf("....\n");
            for(int i=0; i<3; i++) {
                for(int j=0; j<N*2; j++) {
                    printf("%d ", checks[idx(i, j)]);
                }
                printf("\n");
            }
        }

        inline int idx(int r, int c) {
            return r*((N+1)*2) + c;
        }

        int abs(int d) {
            return d < 0 ? -d : d;
        }
    private:
        int N, ans;
        int *cols;
        bool *checks;
        //meas meas_test;
};

void solve() {
    solver sol;
    int ans = sol.run();
    printf("%d\n", ans);
}
int main() {
    solve();
}
