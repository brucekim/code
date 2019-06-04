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
        arr = new int[sz_city];
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                scanf("%d", arr + idx(i, j));
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

    int run() {
        info();
        return 0;
    }
    private:
    int n, m;
    int *arr;
    xqueue<coord> q_homes;
    xqueue<coord> q1;
    xqueue<coord> q2;
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
    t=1;
#endif
    for(int i=0; i<t; ++i) {
        solve(i+1);
    }
    return 0;
}
