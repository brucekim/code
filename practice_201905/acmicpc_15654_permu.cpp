/* given n numbers, m
 * find non-duplicated permu. of length m in n numbers
 *
 * 1 <= n, m <= 8
 *
 * e.g, 
 * 3 1
 * 4 5 2
 *
 * output
 * 4
 * 5
 * 2
 *
 * stack or bitmasking
 */
#include <cstdio>

const int const_err_code = 0x3f3f3f3f;
const int const_max_depth = 1000;

int arr[const_max_depth]{0};

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
        void pop() {
            if (sz > 0) {
                --sz;
            }
        }
        int top() {
            if (sz > 0) {
                return arr[sz-1];
            } else {
                return const_err_code;
            }
        }
        bool isEmpty() {
            return sz ==  0;
        }
        int getSize() {
            return sz;
        }
        int &operator[](int idx) {
            return arr[idx];
        }
    private:
        int capa;
        int sz;
        int *arr;
};

xstack st;

void dfs(int n, int m, bool *visited) {
    if (st.getSize() == m) {
        for(int i=0; i<st.getSize(); ++i) {
            printf("%d ", st[i]);
        }
        printf("\n");
        return;
    }

    for (int i=0; i <n; ++i) {
        if(visited[i] == false) {
            visited[i] = true;
            st.push_back(arr[i]);
            dfs(n, m, visited);
            st.pop();
            visited[i] = false;
        }
    }
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
int partition(int arr[], int l, int r) {
    int pivot = arr[r];
    int i=l-1;
    if (l < r) {
        for(int j=l; j<r; ++j) {
            if (arr[j] < pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i+1], arr[r]);
    }
    return i+1;
}
void quick_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = partition(arr, l, r);
        quick_sort(arr, l, m-1);
        quick_sort(arr, m+1, r);
    }
}
void solve() {
    int n, m;
    bool visited[const_max_depth]{false};
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; ++i) {
        scanf("%d", arr+i);
    }
    /* sort */
    quick_sort(arr, 0, n-1);
    /*
    for(int i=0; i<n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    */
    dfs(n, m, visited);
}

int main() {
    solve();
    return 0;
}
