#include <cstdio>

//#define DBG
#define DBG_STDIN

#ifdef DBG
#define dbg_msg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg_msg(fmt, ...)
#endif

const static int A = 0;
const static int B = 1;
const static int const_max_value = 100000;
const static int const_err_code = 0x3f3f3f3f;

template <typename T>
class xstack {
    public:
    xstack(int _capa=const_max_value) : capa(_capa), sz(0) {
        arr = new T[capa]();
    }
    virtual ~xstack() {
        delete[] arr;
    }
    int push_back(T data) {
        if (sz < capa) {
            arr[sz++] = data;
            return 0;
        } else {
            return const_err_code;
        }
    }
    int pop_back() {
        if (sz > 0) {
            --sz;
            return 0;
        } else {
            return const_err_code;
        }
    }
    const T& top() {
        return arr[sz-1];

    }
    const T& operator[](int idx) {
        return arr[idx];
    }
    bool isEmpty() {
        return sz == 0;
    }
    int getSize() {
        return sz;
    }

    private:
    int capa, sz;
    T *arr;
};


class solver {
    public:
    solver() :ans(const_max_value) {
        scanf("%d %d %d", &d, &w, &k);
        arr = new int[d*w];
        arrbak = new int[d*w];
        visited = new bool[d];
        int tmp;
        for(int i=0; i<d; ++i) {
            for (int j=0; j<w; ++j) {
                scanf("%d", &tmp);
                arr[idx(i, j)] = tmp;
                arrbak[idx(i, j)] = 0;
            }
        }
    }
    virtual ~solver() {
        delete[] arr;
        delete[] visited;
    }
    void init() {
        for (int i=0; i<d; ++i) {
            visited[i] = false;
        }
    }
    void backup(int lev) {
        for(int i=0; i<w; ++i) {
            arrbak[idx(lev, i)] = arr[idx(lev, i)];
        }

    }
    void fill(int lev, int medicine) {
        for(int i=0; i<w; ++i) {
            arr[idx(lev, i)] = medicine;
        }
    }
    void restore(int lev) {
        for(int i=0; i<w; ++i) {
            arr[idx(lev, i)] = arrbak[idx(lev, i)];
        }
    }
    int idx(int i, int j) {
        return i*w + j;
    }
    int run() {
        init();
        dbg_msg("dfs..\n");
        dfs(0);
        dbg_msg("ans..%d\n", ans);
        return ans;
    }
    void dfs(int c) {
#ifdef DBG
        for(int i=0; i<st.getSize(); ++i) {
            dbg_msg("%d ", st[i]);
        }
        dbg_msg("\n");
#endif
        if (meetCriteria() == true && st.getSize() < ans) {
            ans = st.getSize();
        }
        for (int i=c; i<d; ++i) {
            if (visited[i] == false) {
                visited[i] = true;
                backup(i);

                fill(i, A);
                st.push_back(i);
                dfs(i+1);
                st.pop_back();

                fill(i, B);
                st.push_back(i);
                dfs(i+1);
                st.pop_back();

                restore(i);
                visited[i] = false;
            }
        }
    }

    bool meetCriteria() {
        int sum = 0;
        bool inspect = true;
        for (int j = 0; j < w; ++j) {
            for (int i = 0; i < d - k; ++i) {
                inspect = true;
                sum = 0;
                for (int s = i; s < k; ++s) {
                    sum += arr[idx(s, j)];
                }
                if (sum == arr[idx(i, j)] * 3) {
                    break;
                } else {
                    inspect = false;
                }
            }
            if (inspect == false) {
                return false;
            }
        }
        return true;
    }
    void print() {
#ifdef DBG
        dbg_msg("d(%d) w(%d) k(%d)\n", d, w, k);
        for(int i=0; i<d; ++i) {
            for (int j=0; j<w; ++j) {
                printf("%d ", arr[idx(i, j)]);
            }
            printf("\n");
        }
#endif
    }

   private:
    int d, w, k;
    int ans;
    int *arr;
    int *arrbak;
    bool *visited;
    xstack<int> st;
};


void solve(int t) {
    solver sol;
    int ans = sol.run();
    sol.print();
    
    printf("#%d %d\n", t, ans);
}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/swe_pretest_2112_input.txt", "r", stdin);
#endif
    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        solve(i+1);
    }
    return 0;
}
