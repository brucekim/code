/*
*/
#include <cstdio>

#define DBG_STDIN
#define DBG

#ifdef DBG
#define dbg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg(fmt, ...)
#endif

const static int const_max_n = 50;
const static int const_max_sz = 2502;
const static int const_err_code = 0x3f3f3f3f;
const static int const_left = 0;
const static int const_up = 1;
const static int const_right = 2;
const static int const_down = 3;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

template <typename T>
struct coord {
    coord(int _r=0, int _c=0) : r(_r), c(_c) {}
    int r, c;
};

template <typename T>
class xstack {
    public:
    xstack(int _capa=const_max_sz) : capa(const_max_sz), sz(0) {
        arr = new T[capa]();
    }
    virtual ~xstack() {
        delete[] arr;
    }
    int push_back(T& data) {
        if (sz < capa) {
            arr[sz++] = data;
            return 0;
        } else {
            return const_err_code;
        }
    }
    int pop_back() {
        if (sz == 0) {
            return const_err_code;
        } else {
            --sz;
        }
        return 0;
    }
    T& operator[] (int idx) {
        return arr[idx];
    }
    T& top() {
        return arr[sz-1];
    }
    bool isEmpty() {
        return sz == 0;
    }
    int getSize() {

    }
    private:
    int capa, sz;
    T *arr;
};

class solver{
    public:
    solver() {
        scanf("%d", &n);

        int sz_arr = n*n;
        arr = new int[sz_arr];
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                scanf("%d", arr+idx(i, j));
            }
        }
    }
    virtual ~solver() {

    }
    void info() {
        dbg("info.. n:%d\n", n);
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                printf("%d ", arr[idx(i, j)]);
            }
            printf("\n");
        }
    }
    int idx(int r, int c) {
        return r*n + c;
    }
    int run() {
        info();
        return 0;
    }
    private:
    int *arr;
    int n;
};

void solve(int idx) {
    solver sol;
    int ans = 0;

    ans = sol.run();

    printf("#%d %d\n", idx, ans);
}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/swea_4340_input.txt", "r", stdin);
#endif
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i) {
        solve(i+1);
    }
    return 0;
}
