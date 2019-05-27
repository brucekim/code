#include <cstdio>
#include <string>
#include <sstream>
#include <map>

const static int const_max_n = 8;
const static int const_max_depth = 1000;
const static int const_err_code = 0x3f3f3f3f;

template <typename T>
class xstack {
    public:
    xstack() : capa(const_max_depth), sz(0), arr(nullptr) {
        arr = new int[capa]();
    }
    xstack(const xstack<T> &copy) : capa(const_max_depth), sz(copy.sz) {
        if (arr != nullptr) {
            arr = new int[capa]();
        }
        for(int i=0; i<copy.getSize(); ++i) {
            (*this)[i] = copy[i];
        }
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
        return arr[sz];
    }
    const T& operator[] (int idx) {
        return arr[idx];
    }
    int getSize() {
        return sz;
    }
    bool isEmpty() {
        return sz == 0;
    }
    std::string tostring() {
        std::stringstream ss;
        for(int i=0; i<sz; ++i) {
            ss << static_cast<int>(arr[i]);
        }
        return ss.str();
    }
    private:
    int capa, sz;
    T *arr;
};


class solver {
    public:
    solver() {
        scanf("%d %d", &n, &m);
        arr = new int[n]();
        visited = new bool[n]();
        for (int i=0; i<n; ++i) {
            scanf("%d", arr+i);
            visited[i] = false;
        }
    }
    virtual ~solver() {
        delete[] arr;
    }
    void run() {
        quick_sort(0, n-1);
        dfs(0);
    }
    void dfs(int c) {
        if (st.getSize() == m && mm.count(st.tostring()) == 0) {
            mm.insert(make_pair(st.tostring(), 1));
            for(int i=0; i<st.getSize(); ++i) {
                printf("%d ", st[i]);
            }
            printf("\n");
            return;
        }
        for(int i=c; i<n; ++i) {
            if (visited[i] == false) {
                visited[i] = true;
                st.push_back(arr[i]);
                dfs(i+1);
                st.pop_back();
                visited[i] = false;
            }

        }
    }
    void swap(int &a, int &b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int partition(int l, int r) {
        if (l < r) {
            int pivot = arr[r];
            int i = l-1;
            for(int j=l; j<r; ++j) {
                if (arr[j] < pivot) {
                    ++i;
                    swap(arr[i], arr[j]);
                }
            }
            swap(arr[i+1], arr[r]);
            return i+1;
        }
        return l;
    }
    void quick_sort(int l, int r) {
        if (l < r) {
            int m = partition(l, r);
            quick_sort(l, m-1);
            quick_sort(m+1, r);
        }
    }
    private:
    int n, m;
    int *arr;
    xstack<int> st;
    bool *visited;
    std::map<std::string, int> mm;
};

int main() {
    solver sol;
    sol.run();
    return 0;
}
