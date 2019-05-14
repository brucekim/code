 /* given n, find all possible permutation from 1 to n
  * */
#include <cstdio>

const int const_max_depth = 1000;
const int const_err_code = 0x3f3f3f3f;

class xstack {
    public:
        xstack(int _capa=const_max_depth) : capa(_capa), sz(0) {
            arr = new int[capa]{0};
        }
        virtual ~xstack() {
            delete []arr;
        }
        void push_back(int t) {
            if (sz < capa) {
                arr[sz++] = t;
            }
        }
        int top() {
            if (sz > 0) {
                return arr[sz-1];
            } else {
                return const_err_code;
            }
        }
        void pop() {
            if (sz > 0) {
                --sz;
            }
        }
        int& operator[](int idx) {
            return arr[idx];
        }
        int getSize() {
            return sz;
        }
    private:
        int capa;
        int sz;
        int *arr;
};


bool visited[const_max_depth]{false};
xstack st;

void dfs(int n) {
    if (st.getSize() == n) {
        for(int i=0; i<st.getSize(); ++i) {
            printf("%d ", st[i]);
        }
        printf("\n");
    }
    for(int i=1; i<=n; ++i) {
        if (visited[i] == false) {
            visited[i] = true;
            st.push_back(i);
            dfs(n);
            st.pop();
            visited[i] = false;
        }
    }
}

void solve() {
    int n;
    scanf("%d", &n);
    dfs(n);
}

int main() {
    solve();
    return 0;
}
