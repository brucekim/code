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
#define DBG_STDIN
#define DBG_TIME

#include <stdio.h>

#ifdef DBG_TIME
#include <time.h>
#endif

const static int const_max_sz_row = 50;
const static int const_max_sz = 1000;
const static int const_err_code = 0x3f3f3f3f;

int costperk[const_max_sz_row];

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
};

class solver {
    public:
    solver() {
        scanf("%d %d", &n, &m);
        int sz_city = n*n;
        int tmp;
        arr = new int[sz_city];
        visited = new int[sz_city];

        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                scanf("%d", &tmp);
                arr[idx(i, j)] = tmp;
                if (tmp == 1) {
                    q_homes.push_back(coord(i, j));
                }
            }
        }
    }
    virtual ~solver() {
        delete[] arr;
    }
    void info() {
        printf("info..n(%d) m(%d)\n", n, m);
        printf("constperk..: ");
        for(int i=1; i<const_max_sz_row+1; ++i) {
            printf("%d(%d) ", i, costperk[i]);
        }
        printf("\n..\n");
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                printf("%d ", arr[idx(i, j)]);
            }
            printf("\n");
        }
    }
    inline int idx(int r, int c) {
        return r*n + c;
    }
    void init_visited() {
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                visited[idx(i, j)] = 0;
            }
        }
    }

    int run() {
        info();
        int max = 0;
        while(!q_homes.isEmpty()) {
            coord h = q_homes.get_front();
            q_homes.pop_front();
            init_visited();
            printf("start find..(%d %d)\n", h.r, h.c);
            xqueue<coord> q1;
            xqueue<coord> q2;
            int cnt = find(h, q1, q2);

            if (max < cnt) {
                max = cnt;
            }
        }
        return max;
    }
    bool valid(int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < n;
    }
    int find(coord h, xqueue<coord> &q1, xqueue<coord> &q2) {
        q1.push_back(h);
        visited[idx(h.r, h.c)] = 1;
        int k = 1;
        int cnt_home_tmp = 1;
        int cnt_home = 1;
        while(!q1.isEmpty()) {

            while(!q1.isEmpty()) {
                coord h2 = q1.get_front();
                q1.pop_front();
                printf("pop (%d %d) then search neighbor..\n", h2.r, h2.c);
                for(int i=0; i<4; ++i) {
                    int r2 = h2.r + dr[i];
                    int c2 = h2.c + dc[i];
                    printf("neighbor (%d %d) \n", r2, c2);
                    if (valid(r2, c2) == true && visited[idx(r2, c2)] == 0) {
                        visited[idx(r2, c2)] = 1;
                        //found home
                        if (arr[idx(r2, c2)] == 1)  {
                            printf("found home (%d %d) - current k=%d\n", r2, c2, k);
                            ++cnt_home_tmp;
                        }
                        printf("pushback to q2 (%d %d)\n", r2, c2);
                        q2.push_back(coord(r2, c2));
                    }
                }
            }
            //increse k;
            ++k;
            if ((cnt_home_tmp * m) < costperk[k]) {
                printf("return(%d)..cost(%d] < costperk[%d]=%d\n", cnt_home, cnt_home_tmp*m, k, costperk[k]);
                return cnt_home;
            } else {
                cnt_home = cnt_home_tmp;
            }
            while(!q2.isEmpty()) {
                q1.push_back(q2.get_front());
                q2.pop_front();
            }
        }
        return cnt_home;
    }
    private:
    int n, m;
    int *arr;
    int *visited;
    xqueue<coord> q_homes;
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
        costperk[i] = i*i + (i-1)*(i-1);
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
    t=3;
#endif
    for(int i=0; i<t; ++i) {
        solve(i+1);
    }
    return 0;
}
