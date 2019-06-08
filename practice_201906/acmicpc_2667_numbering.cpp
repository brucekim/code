#include <stdio.h>

#define DBG_STDIN

const static int const_max_sz = 1000;
const static int const_err_code = 0x3f3f3f3f;

int dc[] = {-1, 1, 0, 0};
int dr[] = {0, 0, -1, 1};

struct coord {
    coord(int _r=0, int _c=0) : r(_r), c(_c) {}
    int r, c;
};

template <typename T>
class xqueue {
    public:
        xqueue() : capa(const_max_sz), sz(0), front(-1), rear(-1) {
            arr = new T[capa];
        }
        virtual ~xqueue() {
            delete[] arr;
        }
        int push_back(T data) {
            if ((rear == capa-1 && front == 0) || (rear == (front-1)%capa)) {
                return const_err_code;
            } else if (front == -1) {
                front = rear = 0;
            } else if (rear == capa-1 && front != 0) {
                rear = 0;
            } else {
                ++rear;
            }
            ++sz;
            arr[rear] = data;
            return 0;
        }
        int pop_front() {
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
        T& get_front() {
            return arr[front];
        }
        bool isEmpty() {
            return sz == 0;
        }
    private:
        int capa, sz, front, rear;
        T *arr;
};

class solver {
    public:
        solver() : cnt_group(0) {
            scanf("%d", &N);

            int sz_max_cell = N*N;
            arr = new int[sz_max_cell];
            group = new int[sz_max_cell];
            visited = new int[sz_max_cell];

            char *tmp = new char[N+1];
            for(int i=0; i<N; ++i) {
                scanf("%s", tmp);
                for(int j=0; j<N; ++j) {
                    arr[idx(i, j)] = tmp[j] - '0';
                    visited[idx(i, j)] = 0;
                }
            }
            delete[] tmp;
        }
        virtual ~solver() {
            delete[] arr;
            delete[] group;
            delete[] visited;
        }
        inline int idx(int i, int j) {
            return i*N + j;
        }
        void run() {

            find();
            qsort(group, 0, cnt_group-1);

            printf("%d\n", cnt_group);
            for(int i=0; i<cnt_group; ++i) {
                printf("%d\n", group[i]);
            }
        }
        void find() {
            for(int i=0; i<N; ++i) {
                for(int j=0; j<N; ++j) {
                    if (visited[idx(i, j)] == 0 && arr[idx(i, j)] != 0) {
                        ++cnt_group;
                        bfs(i, j);
                    }
                }
            }
        }
        bool valid(int r, int c) {
            return r >= 0 && r < N && c >= 0 && c < N;
        }
        void bfs(int i, int j) {
            xqueue<coord> q;
            q.push_back(coord(i, j));
            visited[idx(i, j)] = cnt_group;
            int cnt = 1;

            while(!q.isEmpty()) {
                coord t = q.get_front();
                q.pop_front();
                for(int i=0; i<4; ++i) {
                    int r2 = dr[i] + t.r;
                    int c2 = dc[i] + t.c;
                    if (valid(r2, c2) == true && visited[idx(r2, c2)] == 0 && arr[idx(r2, c2)] != 0) {
                        q.push_back(coord(r2, c2));
                        visited[idx(r2, c2)] = cnt_group;
                        ++cnt;
                    }
                }
            }
            group[cnt_group-1] = cnt;
        }

        void swap(int &a, int &b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        int partition(int *arr, int l, int r) {
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
        void qsort(int *arr, int l, int r) {
            if (l < r) {
                int m = partition(arr, l, r);
                qsort(arr, l, m-1);
                qsort(arr, m+1, r);
            }
        }
    private:
        int N;
        int *arr;
        int cnt_group;
        int *group;
        int *visited;
};

void solve() {
    solver sol;
    sol.run();
}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/acmicpc_2667_input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
