#include <cstdio>

const static int const_max_depth = 1000;
const static int const_err_code = 0x3f3f3f3f;

class xstack {
    public:
    xstack(int _capa=const_max_depth) : capa(_capa), sz(0) {
        arr = new int[capa]{0};
    }
    virtual ~xstack() {
        delete []arr;
    }
    int top() {
        if (sz > 0) {
            return arr[sz-1];
        } else {
            return const_err_code;
        }
    }
    int &operator[](int idx) {
        return arr[idx];
    }
    void push_back(int t) {
        if (sz < capa) {
            arr[sz++] = t;
        }
    }
    void pop() {
        if (sz > 0) {
            --sz;
        }
    }
    bool isEmpty() {
        return sz == 0;
    }
    int getSize() {
        return sz;
    }
    
    private:
    int capa;
    int sz;
    int *arr;
};

void dfs(int n, bool *visited, xstack &st) {
    if (st.getSize() == n) {
        for(int i=0; i<st.getSize(); ++i) {
            printf("%d ", st[i]);
        }
        printf("\n");
    }
    for (int i=1; i<n+1; ++i) {
        if (visited[i] == false) {
            visited[i] = true;
            st.push_back(i);
            dfs(n, visited, st);
            st.pop();
            visited[i] = false;
        }
    }
}

void solve() {
    int n;
    bool visited[const_max_depth]{false};
    xstack st;
    scanf("%d", &n);
    dfs(n, visited, st);
}

int main() {
    solve();
    return 0;
}
