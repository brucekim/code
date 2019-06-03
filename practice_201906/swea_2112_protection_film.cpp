#include <stdio.h>

#define DBG
#define DBG_STDIN

#ifdef DBG
#define dbg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg(fmt, ...)
#endif

const static int const_a = 0;
const static int const_b = 1;
const static int const_x = 2;

class solver {
    public:
    solver() : min(0x7fffffff) {
        scanf("%d %d %d", &d, &w, &k);
        int sz_arr = d*w;
        arr = new int[sz_arr];
        consecutive = new int[sz_arr];
        max_consecutive = new int[sz_arr];
        chemical = new int[w];

        for(int i=0; i<d; ++i) {
            for(int j=0; j<w; ++j) {
                scanf("%d", arr + idx(i, j));
            }
        }
        for(int i=0; i<sz_arr; ++i) {
            consecutive[i] = max_consecutive[i] = 1;
        }
    }
    virtual ~solver() {
        delete[] arr;
        delete[] consecutive;
        delete[] max_consecutive;
        delete[] chemical;
    }
    inline int idx(int r, int c) {
        return r*w + c;
    }
    void info() {
        printf("info...d(%d) w(%d) k(%d)\n", d, w, k);
        for(int i=0; i<d; ++i) {
            for(int j=0; j<w; ++j) {
                printf("%d ", arr[idx(i, j)]);
            }
            printf("\n");
        }
    }
    int run() {
        //info();
        chemical[0] = const_x;
        dfs(1, 0);
        chemical[0] = const_a;
        dfs(1, 1);
        chemical[0] = const_b;
        dfs(1, 1);
        return min;
    }
    void dfs(int curD, int cnt) {
        //가지치기
        if (min <= cnt) {
            return;
        }
        if (curD == d) {
            //연속하는 셀들이 모든 열에서 k개 이상을 만족하여 성능 기준이 만족된다면, 약품 투입수를 보고 최저값을 갱신한다
            //약품 투입수가 알려진 최저값보다 크다면 성능 기준을 검사할 필요가 없음

            for(int i=0; i<w; ++i) {
                if (max_consecutive[idx(curD-1, i)] < k)
                return;
            }
            min = (cnt < min) ? cnt : min;
            return;
        }


        //약품 처리 및 필름 막 검사
        for(int i=0; i<3; ++i) {
            //backup
            chemical[curD] = i;
            for(int j=0; j<w; ++j) { int curr = (chemical[curD] != const_x) ? chemical[curD] : arr[idx(curD, j)]; int prev = (chemical[curD-1] != const_x) ? chemical[curD-1] : arr[idx(curD-1, j)];
                //이전 막과 비교해서 동일한 특성이면 연속하는 셀 갯수 1증가, 아니면 다시 1로 초기화
                consecutive[idx(curD, j)] = (prev == curr) ? consecutive[idx(curD-1, j)] + 1 : 1;
                //현재까지 최대 연속하는 셀 개수 유지
                max_consecutive[idx(curD, j)] = (max_consecutive[idx(curD-1, j)] < consecutive[idx(curD, j)]) ? consecutive[idx(curD, j)] : max_consecutive[idx(curD-1, j)];
            }
            //처리한 약품 누적 횟수 - 약품 사용한 경우는 cnt + 1, 사용하지 않았으면 cnt
            int nextCnt = (chemical[curD] != const_x) ? cnt + 1 : cnt;
            dfs(curD + 1, nextCnt);
            //restore
            for(int j=0; j<w; ++j) {
                consecutive[idx(curD, j)] = max_consecutive[idx(curD, j)] = 1;
            }
        }
    }
    private:
    int min;
    int d, w, k;
    int *arr;
    int *chemical;
    int *consecutive;
    int *max_consecutive;
    int *bak_consecutive;
    int *bak_max_consecutive;
};

void solve(int idx) {
    solver sol;
    int ans = 0;
    ans = sol.run();

    printf("#%d %d\n", idx, ans);
}
int main() {
#ifdef DBG_STDIN
    freopen("inputs/swea_2112_input.txt", "r", stdin);
#endif
    int t;
    scanf("%d", &t);
#ifdef DBG_STDIN
    //t = 1;
#endif
    for (int i = 0; i < t; ++i) {
        solve(i+1);
    }
    return 0;
}
