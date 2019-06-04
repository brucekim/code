/*
list combination 3^D
d, w, k
a = 0
b = 1
x = 2
output
#x cnt
*/
#define DBG_STDIN
//#define DBG_TIME

#include <stdio.h>
#ifdef DBG_TIME
#include <time.h>
#endif


const static int const_max_sz = 1000;
const static int const_err_code = 0x3f3f3f3f;
const static int const_a = 0;
const static int const_b = 1;
const static int const_x = 2;

struct vertex {
    vertex(int _d=0, int _c=0) : d(_d), c(_c) {}
    int d, c;
};
template <typename T>
class xstack {
    public:
        xstack() : capa(const_max_sz), sz(0) {
            arr = new T[capa];
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
        T& operator[] (int idx) {
            return arr[idx];
        }
        bool isEmpty() {
            return sz == 0;
        }
        int getSize() {
            return sz;
        }
    private:
        int sz, capa;
        T *arr;
};

class solver {
    public:
        solver() : min(0x7fffffff), test_cnt(0) {
#ifdef DBG_TIME
            start = clock();
#endif
            scanf("%d %d %d", &d, &w, &k);
            int sz_arr = d*w;
            arr = new int[sz_arr];
            bak = new int[sz_arr];
            for(int i=0; i<d; ++i) {
                for(int j=0; j<w; ++j) {
                    scanf("%d", arr + idx(i, j));
                }
            }
        }
        virtual ~solver() {
            delete[] arr;
            delete[] bak;
#ifdef DBG_TIME
            end = clock();
            double duration = static_cast<double>(end-start);
            printf(" consume %lf\n", duration/CLOCKS_PER_SEC);
#endif
        }
        inline int idx(int r, int c) {
            return r*w + c;
        }
        void info() {
            printf("info.. d(%d) w(%d) k(%d)\n", d, w, k);
            for(int i=0; i<d; ++i) {
                for(int j=0; j<w; ++j) {
                    printf("%d ", arr[idx(i, j)]);
                }
                printf("\n");
            }
        }


        int run() {
            //info();
            dfs(0, 0);
            return min;
        }
        void backup(int curD) {
            for(int i=0; i<w; ++i) {
                bak[idx(curD, i)] = arr[idx(curD, i)];
            }
        }
        void restore(int curD) {
            for(int i=0; i<w; ++i) {
                arr[idx(curD, i)] = bak[idx(curD, i)];
            }
        }
        void fill(int curD, int chemical) {
            for(int i=0; i<w; ++i) {
                arr[idx(curD, i)] = chemical;
            }
        }
        bool passCriteria() {
            for(int j=0; j<w; ++j) {
                bool flag = false;
                int cnt = 1;
                for(int i=1; i<d; ++i) {
                    if (arr[idx(i, j)] == arr[idx(i-1, j)]) {
                        ++cnt;
                    } else {
                        cnt = 1;
                    }

                    if (cnt >= k) {
                        flag = true;
                        break;
                    }
                }
                if (flag == false) {
                    return false;
                }
            }
            return true;
        }
        void printStack(int cnt) {
            printf("cum cnt:%d ..\n", cnt);
            for(int i=0; i<st.getSize(); ++i) {
                printf("%d(%d) ", st[i].d, st[i].c);
            }
            printf("\n");
        }
        void dfs(int curD, int cnt_chemical) {
            if (cnt_chemical >= min) {
                return;
            }
            if (curD == d) {
                //printStack(cnt_chemical);
                //info();
                if (passCriteria() == true) {
                    if (cnt_chemical < min) {
                        //printf("update min(%d) cnt_chemical(%d)\n", min, cnt_chemical);
                        min = cnt_chemical;
                    }
                }
                return;
            }

            //st.push_back(vertex(curD, const_x));
            dfs(curD+1, cnt_chemical);
            //st.pop_back();

            //st.push_back(vertex(curD, const_a));
            backup(curD);
            fill(curD, const_a);
            dfs(curD+1, cnt_chemical+1);
            restore(curD);
            //st.pop_back();

            //st.push_back(vertex(curD, const_b));
            backup(curD);
            fill(curD, const_b);
            dfs(curD+1, cnt_chemical+1);
            restore(curD);
            //st.pop_back();

        }
    private:
        int min;
        int d, w, k;
        int *arr;
        int *bak;
        xstack<vertex> st;
        int test_cnt;
#ifdef DBG_TIME
        time_t start, end;
#endif
};

void solve(int idx) {
    int ans = 0;
    solver sol;
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
    t = t;
#endif
    for(int i=0; i<t; ++i) {
        solve(i+1);
    }

    return 0;
}
