#include <cstdio>

const static int const_max_n = 8;
const static int const_max_sz = 1000;
const static int const_err_code = 0x3f3f3f3f;

template <typename T>
class xstack {
    public:
    xstack() : capa(const_max_sz), sz(0) {
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
    const T& operator[] (int idx) {
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

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int partition(int *arr, int l, int r) {
    if (l<r) {
        int pivot = arr[r];
        int i = l-1;
        for(int j=l; j<r; ++j) {
            if (arr[j]<pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i+1], arr[r]);
        return i+1;
    }
    return l;
}

void quick_sort(int *arr, int l, int r) {
    if (l < r) {
        int m = partition(arr, l, r);
        quick_sort(arr, l, m-1);
        quick_sort(arr, m+1, r);
    }
}

class solver {
    public:
    solver() {
        arr = new int[const_max_n]{0};
        for(int i=0; i<const_max_n; ++i) {
            arr[i] = 0;
        }

        scanf("%d %d", &n, &m);
        for(int i=0; i<n; ++i) {
            scanf("%d", arr+i);
        }
    }
    virtual ~solver() {
        delete[] arr;
    }

    void run() {
        quick_sort(arr, 0, n-1);
        dfs(0);
    }

    void dfs(int c) {
        if (st.getSize() == m) {
            for(int i=0; i<m; ++i) {
                printf("%d ", st[i]);
            }
            printf("\n");
            return;
        }
        for(int i=c; i<n; ++i) {
            st.push_back(arr[i]);
            dfs(i);
            st.pop_back();
        }
    }
    private:
    int *arr;
    int n, m;
    xstack<int> st;
};

int main() {
    solver sol;
    sol.run();
    return 0;
}
