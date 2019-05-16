/*
 * input
 * 4 2
 * output
 * 1 2
 * 1 3
 * 1 4
 * 2 3
 * 2 4
 * 3 4
 *
 * 2C4
 *
 * 4! / (2!(4-2)!) = 4!/2!2! = 6
 */

#include <cstdio>

const static int const_max_depth = 1000;

template <typename T>
class xstack {
    public:
        xstack(int _capa=const_max_depth) : capa(_capa), sz(0) {
            arr = new T[capa]{};
        }
        virtual ~xstack() {
            delete[] arr;
        }
        void push_back(T data) {
            if (sz < capa) {
                arr[sz++] = data;
            }
        }
        void pop_back() {
            if (sz > 0) {
                --sz;
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
        int capa;
        int sz;
};
void dfs(int m, int n, int p, xstack<int> *st, bool *visited) {
    if (st->getSize() == n) {
        for(int i=0; i<st->getSize(); ++i) {
            printf("%d ", (*st)[i]);
        }
        printf("\n");
    }

    for(int i=p; i<m; ++i) {
        if (visited[i] == false) {
            visited[i] = true;
            st->push_back(i);
            dfs(m, n, i, st, visited);
            st->pop_back();
            visited[i] = false;
        }
    };
}

void solve() {
    int m, n;
    xstack<int> st;
    bool visited[const_max_depth]{};
    scanf("%d %d", &m, &n);
    dfs(m+1, n, 1, &st, visited);
}

int main() {
    solve();
    return 0;
}
