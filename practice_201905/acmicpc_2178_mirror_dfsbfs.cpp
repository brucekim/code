/* 
1 : move possible
0: move no possible

start (1, 1)
dest (n, m)
minimum number of cells from start to dest

2 <= n, m <= 100
*/
#include <cstdio>

#define DBG

const static int const_max_sz = 10002;
const static int const_err_code = 0x3f3f3f3f;

struct vertex {
    vertex(int _r=0, int _c=0) : r(_r), c(_c) {}
    int r, c;
};

template <typename T>
class xqueue {
    public:
    xqueue() : capa(const_max_sz), sz(0), front(-1), rear(-1) {
        arr = new T[capa]();
    }
    virtual ~xqueue() {
        delete[] arr;
    }
    int enq(T data) { if ((rear == capa-1 && front == 0) || (rear == (front-1)%capa)) {
            return const_err_code;
        } else if (front == -1) {
            front = rear = 0;
        } else if (rear == capa-1 && front != 0) {
            rear = 0;
        } else {
            ++rear;
        }
        arr[rear] = data;
        ++sz;
        return 0;
    }
    int deq() {
        if (front == -1) {
            return const_err_code;
        } else if (front == rear) {
            front = rear = -1;
        } else if (front == capa-1) {
            front = 0;
        } else {
            ++front;
        }
        --sz;
        return 0;
    }
    T& operator[] (int idx) {
        return arr[idx];
    }
    T& getFront() {
        return arr[front];
    }
    bool isEmpty() {
        return sz == 0;
    }
    int getSize() {
        return sz;
    }
    private:
    T *arr;
    int front, rear, sz, capa;
};

class solver {
    public:
    solver() : ans(0) {
        scanf("%d %d", &n, &m);
        arr = new int[n*m];
        char line[const_max_sz]{0};
        for(int i=0; i<n; ++i) {
            scanf("%s", line);
            for(int j=0; j<m; ++j) {
                arr[idx(i, j)] = line[j] - '0';
            }
        }
    }
    virtual ~solver() {
        delete[] arr;
    }
    void info() {
        printf("n:%d m:%d ..\n", n, m);
        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {
                printf("%d ", arr[idx(i, j)]);
            }
            printf("\n");
        }
    }
    int idx(int r, int c) {
        return r*m + c;
    }
    int run() {
#ifdef DBG
        info();
#endif

        dfs();
#ifdef DBG
        info();
#endif
        return ans;
    }
    bool valid(int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < m;
    }
    void dfs() {
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        bool visited[n*m];
        for(int i=0; i < n*m; ++i) {
            visited[i] = false;
        }

        q.enq(vertex(0, 0));
        visited[idx(0, 0)] = true;
        while(!q.isEmpty()) {
            vertex tmp = q.getFront();
            q.deq();
            for(int i=0; i<4; ++i) {
                int r2 = tmp.r+dr[i];
                int c2 = tmp.c+dc[i];
                if (valid(r2, c2) == true && arr[idx(r2, c2)] == 1 && visited[idx(r2, c2)] == false) {
                    arr[idx(r2, c2)] = arr[idx(tmp.r, tmp.c)] + 1;
                    visited[idx(r2,c2)] = true;
                    q.enq(vertex(r2, c2));
                }
            }
        }
        ans = arr[idx(n-1, m-1)];
    }
    private:
    int *arr;
    int n, m;
    int ans;
    xqueue<vertex> q;
};

void solve() {
    solver sol;
    int ans = sol.run();
    printf("%d\n", ans);
}
int main() {
#ifdef DBG
    freopen("inputs/acmicpc_2178_input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
