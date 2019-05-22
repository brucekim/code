#include <cstdio>

const static int const_max_depth = 1000;
const static int const_err_code = 0x3f3f3f3f;

template <typename T>
class xstack {
    public:
        xstack(int _capa=const_max_depth) : capa(_capa), sz(0) {
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
        T *arr;
        int capa, sz;
};

class solver {
    public:
        solver() {
            scanf("%d %d", &n, &m);
        }
        virtual ~solver() {
        }
        void run() {
            dfs();
        }
        void dfs() {
            if (st.getSize() == m) {
                for(int i=0; i< st.getSize(); ++i) {
                    printf("%d ", st[i]);
                }
                printf("\n");
                return;
            }
            for(int i=1; i<=n; ++i) {
                st.push_back(i);
                dfs();
                st.pop_back();
            }
            return;
        }
    private:
        xstack<int> st;
        int n, m;
};

int main() {
    solver sol;
    sol.run();
    return 0;
}
