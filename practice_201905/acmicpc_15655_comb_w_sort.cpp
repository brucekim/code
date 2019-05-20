/*
input
4 2
9 8 7 1
output
1 7
1 8
1 9
7 8
7 9
8 9
*/
#include <cstdio>

const static int const_max_n = 8;
const static int const_max_depth = 1000;
const static int const_err_code = 0x3f3f3f3f;

template <typename T>
class xstack {
   public:
    xstack(int _capa = const_max_depth) : capa(_capa), sz(0) {
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
    T &top() {
        return arr[sz - 1];
    }
    T &operator[](int idx) {
        return arr[idx];
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
    T *arr;
};
void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
int partition(int *arr, int l, int r) {
    if (l < r) {
        int pivot = arr[r];
        int i = l - 1;
        for (int j = l; j < r; ++j) {
            if (arr[j] < pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[r]);
        return i + 1;
    }
    return l;
}
void quick_sort(int *arr, int l, int r) {
    if (l < r) {
        int m = partition(arr, l, r);
        quick_sort(arr, l, m - 1);
        quick_sort(arr, m + 1, r);
    }
}

class solver {
   public:
    solver(int *_arr, int _n, int _m) : arr(_arr), n(_n), m(_m) {
        visited = new bool[n];
        for (int i = 0; i < n; ++i) {
            visited[i] = false;
        }
    }

    void dfs(int s) {
        if (st.getSize() == m) {
            for (int i = 0; i < st.getSize(); ++i) {
                printf("%d ", st[i]);
            }
            printf("\n");
        }
        for (int i = s; i < n; ++i) {
            if (visited[i] == false) {
                visited[i] = true;
                st.push_back(arr[i]);
                dfs(i + 1);
                st.pop_back();
                visited[i] = false;
            }
        }
    }

   private:
    xstack<int> st;
    int *arr;
    bool *visited;
    int n, m;
};

void solve() {
    int n, m;
    int arr[const_max_n]{0};

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    quick_sort(arr, 0, n - 1);
    solver sol(arr, n, m);
    sol.dfs(0);
}
int main() {
    solve();
    return 0;
}
