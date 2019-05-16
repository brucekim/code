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
    xstack(int _capa=const_max_depth) : capa(_capa), sz(0) {
        arr = new coord[capa]();
    }
    virtual ~xstack() {
        delete[] arr;
    }
    void push_back (T &&c) {
        if (sz < capa) {
            arr[sz++] = c;
        }
    }
    void pop() {
        if (sz > 0) {
            --sz;
        }
    }
    T &top() {
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

class solver {
    public:
        solver(int _n, int _k, int (*_arr)[const_max_n], xstack<coord> *_st) :
            n(_n), k(_k), arr(_arr), st(_st) {}
        void print() {
            printf("map:\n");
            for (int i=0; i<n; ++i) {
                for (int j=0; j<n; ++j) {
                    printf("%d ", arr[i][j]);
                }
                printf("\n");
            }
            printf("highest::\n");
            for(int i=0; i<st->getSize(); ++i) {
                printf("(%d %d)", (*st)[i].x, (*st)[i].y);
            }
            printf("\n");
        }
        void dfs() {
            for 
        }
    private:
        int n, k;
        int (*arr)[const_max_n];
        xstack<coord> *st;
};

void solve() {
    int ans = 0;
    int n, k;
    int arr[const_max_n][const_max_n]{0};
    int highest = -1;
    int max_trail = -1;
    xstack<coord> st;

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
            if (arr[i][j] == highest) {
                st.push_back(coord(i, j));
            }
        }
    }
    solver sol(n, k, arr, &st);
    sol.print();
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
