#include <cstdio>

const static int const_max_capa = 1000;
const static int const_err_code = 0x3f3f3f3f;

template <typename T>
class xstack {
    public:
        xstack() : capa(const_max_capa), sz(0) {
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
        int getSize() {
            return sz;
        }
    private:
        T *arr;
        int capa, sz;
};

class solver {
    public:
        solver() {
            scanf("%d %d", &n, &m);
        }
        void run() {
            dfs(1);
        }
        void dfs(int c) {
            if (st.getSize() == m) {
                for(int i=0; i<st.getSize(); ++i) {
                    printf("%d ", st[i]);
                }
                printf("\n");
                return;
            }
            for(int i=c; i<=n; ++i) {
                st.push_back(i);
                dfs(i);
                st.pop_back();
            }
        }

    private:
        int n, m;
        xstack<int> st;
};

int main() {
    solver sol;
    sol.run();
    return 0;
}

