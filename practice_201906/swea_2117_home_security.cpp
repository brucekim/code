/*

#1 5
#2 4
#3 24
#4 48
#5 3
#6 65
#7 22
#8 22
#9 78
#10 400
*/
//#define DBG
//#define DBG_STDIN
//#define DBG_TIME

#include <stdio.h>

#ifdef DBG_TIME
#include <time.h>
#endif

#ifdef DBG
#define dbg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg(fmt, ...)
#endif

const static int const_max_sz_row = 50;
const static int const_max_sz = 1000;
const static int const_err_code = 0x3f3f3f3f;

int operation_cost[const_max_sz_row];

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

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
    const T& get_front() {
        return arr[front];
    }
    T& operator[] (int idx) {
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
    int front, rear;
};

class meas {
#ifdef DBG_TIME
    public:
    meas() {
        start = clock();
    }
    ~meas() {
        end = clock();
        double duration = static_cast<double>(end - start);
        printf("run time: %lf\n", duration / CLOCKS_PER_SEC);
    }
    private:
    time_t start, end;
#endif
};

class solver {
    public:
    solver() : max_possible_fee(0) {
        scanf("%d %d", &N, &M);
        int sz_city = N*N;
        int tmp;
        arr = new int[sz_city];
        visited = new int[sz_city];

        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                scanf("%d", &tmp);
                arr[idx(i, j)] = tmp;
                if (tmp == 1) {
                    max_possible_fee += M;
                }
            }
        }
    }
    virtual ~solver() {
        delete[] arr;
    }
    void info() {
        dbg("info..N(%d) M(%d)\n", N, M);
        dbg("operation_cost..: ");
        for(int i=1; i<const_max_sz_row+1; ++i) {
            dbg("%d(%d) ", i, operation_cost[i]);
        }
        dbg("\n..max_possible_fee:%d\n", max_possible_fee);
        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                dbg("%d ", arr[idx(i, j)]);
            }
            dbg("\n");
        }
    }
    void info_visited() {
        dbg("visited\n");
        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                dbg("%d ", visited[idx(i, j)]);
            }
            dbg("\n");
        }
 
    }
    inline int idx(int r, int c) {
        return r*N + c;
    }
    void init_visited() {
        int sz_city = N*N;
        for(int i=0; i<sz_city; ++i) {
            visited[i] = 0;
        }
    }

    int run() {
        info();
        int max = 0;
        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {

                dbg("start find..(%d %d)\n", i, j);
                int local_max = find(coord(i, j));
                dbg("local_max = %d\n", local_max);
                if (max < local_max) {
                    max = local_max;
                }
            }
        }
        return max;
    }
    bool valid(int r, int c) {
        return r >= 0 && r < N && c >= 0 && c < N;
    }
    int find(coord s) {
        xqueue<coord> q;
        init_visited();

        q.push_back(s);
        visited[idx(s.r, s.c)] = 2;
        int cnt_home = arr[idx(s.r, s.c)] == 1 ? 1 : 0;
        int cnt_max_home = 0;
        int k = 1;
        int max_k = 0;

        while(!q.isEmpty()) {
            if (max_possible_fee < operation_cost[k]) {
                break;
            }
            if (cnt_home*M - operation_cost[k] >= 0 && cnt_home > cnt_max_home) {
                cnt_max_home = cnt_home;
                max_k = k;
            }

            int sz_q = q.getSize();
            for(int i=0; i< sz_q; ++i) {
                coord h = q.get_front();
                q.pop_front();
                for(int j=0; j<4; ++j) {
                    int r2 = h.r + dr[j];
                    int c2 = h.c + dc[j];

                    if (valid(r2, c2) == true && visited[idx(r2, c2)] == 0) {
                        visited[idx(r2, c2)] = 2;
                        q.push_back(coord(r2, c2));
                        if (arr[idx(r2, c2)] == 1) {
                            ++cnt_home;
                        }
                    }
                }
            }
            ++k;
        }
        dbg("k = %d, cnt_max_home=%d max_k=%d \n", k, cnt_max_home, max_k);
        return cnt_max_home;
    }
    private:
    int N, M;
    int *arr;
    int *visited;
    int max_possible_fee;
#ifdef DBG_TIME
    meas meas_time;
#endif
};


void solve(int idx) {
    solver sol;
    int ans = 0;
    ans = sol.run();

    printf("#%d %d\n", idx, ans);
}

void ready() {
    for(int i=1; i<const_max_sz_row+1; ++i) {
        operation_cost[i] = i*i + (i-1)*(i-1);
    }
}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/swea_2117_input.txt", "r", stdin);
#endif
    ready();
    int t;
    scanf("%d", &t);
#ifdef DBG_STDIN
    t=t;
#endif
    for(int i=0; i<t; ++i) {
        solve(i+1);
    }
    return 0;
}
