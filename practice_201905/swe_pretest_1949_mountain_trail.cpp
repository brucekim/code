/*
*/
#include <cstdio>

const static int const_max_depth = 10000;
const static int const_err_code = 0x3f3f3f3f;

const static int const_max_n = 8;
const static int const_max_k = 5;

struct coord {
    coord(int _x=0, int _y=0) : x(_x), y(_y) {}
    int x;
    int y;
};

template <typename T>
class xstack {
    public:
    xstack(int _capa) : capa(_capa), sz(0) {
        arr = new coord[capa]();
    }
    virtual ~xstack() {
        delete[] arr;
    }
    void push_back (coord &c) {
        if (sz < capa) {
            arr[sz++] = c;
        }
    }
    void pop() {
        if (sz > 0) {
            --sz;
        }
    }
    coord &top() {
        return arr[sz-1];
    }
    bool isEmpty() {
        return sz == 0;

    }
    int getSize() {
        return sz;
    }
    coord& operator[](int idx) {
        return arr[idx];
    }

    private:
    int capa;
    int sz;
    T *arr;
};

void solve() {
    int ans = 0;
    int n, k;
    int arr[const_max_n][const_max_k]{0};
    int highest = -1;

    // input
    scanf("%d %d", &n, &k);
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            int t;
            scanf("%d", &t);
            arr[i][j] = t;
            if (highest < t) {
                highest = t;
            }
        }
    }

    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            if (arr[i])
        }
        printf("\n");
    }
    //printf("%d\n", ans);
}
int main() {
    int t;
    //scanf("%d", &t);
    for (int i = 0; i < 1; ++i) {
        //printf("#%d ", i+1);
        freopen("inputs/swe_pretest_1949_input.txt", "r", stdin);
    }
    solve();
    return 0;
}
