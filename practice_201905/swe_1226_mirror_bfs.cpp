#include <cstdio>

#define DBG_STDIN
//#define DBG

#ifdef DBG
#define dbg_msg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg_msg(fmt, ...)
#endif

const static int const_max_n = 16;
const static int const_max_sz = 1000;
const static int const_err_code = 0x3f3f3f3f;

int rcheck[] = {-1, 1, 0, 0};
int ccheck[] = {0, 0, -1, 1};

struct coord {
    coord(int _r=0, int _c=0) : r(_r), c(_c) {}
    int r, c;
};

template <typename T>
class xqueue {
    public:
    xqueue(int _capa=const_max_sz) : capa(_capa), sz(0), front(-1), rear(-1) {
        arr = new T[capa]();
    }
    virtual ~xqueue() {
        delete[] arr;
    }
    int enq(T data) {
        if ((rear == capa-1 && front ==0) || (rear == (front-1)%capa)) {
            return const_err_code;
        } else if (front == -1) {
            front = rear = 0;
        } else if (rear == capa -1 && front != 0) {
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
        } else if (front == capa - 1) {
            front = 0;
        } else {
            ++front;
        }
        --sz;
        return 0;

    }
    const T& getFront() {
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
    int capa, sz;
    int front, rear;
};

class solver {
    public:
    solver() {
        char tarr[const_max_n+1]{0};
        for (int i = 0; i < const_max_n; ++i) {
            scanf("%s", tarr);
            for (int j = 0; j < const_max_n; ++j) {
                arr[i][j] = tarr[j] - '0';
            }
        }
        dbg_msg("input done..\n");
    }

    int run() {
        q.enq(coord(1, 1));

        while (!q.isEmpty()) {
            coord tmp = q.getFront();
            q.deq();
            dbg_msg("--deq (%d %d)\n", tmp.r, tmp.c);
            for (int i = 0; i < 4; ++i) {
                int r1 = tmp.r + rcheck[i];
                int c1 = tmp.c + ccheck[i];
                if (arr[r1][c1] == 3) {
                    return 1;
                }
                if (valid(r1, c1) == true && arr[r1][c1] == 0) {
                    dbg_msg("enq (%d %d)\n", r1, c1);
                    arr[r1][c1] = 4;
                    q.enq(coord(r1, c1));
                }
            }
        }
        return 0;
    }
    bool valid(int r, int c) {
        return r >= 0 && r < const_max_n && c >= 0 && c < const_max_n;
    }
    void print() {
#ifdef DBG
        for (int i = 0; i < const_max_n; ++i) {
            for (int j = 0; j < const_max_n; ++j) {
                dbg_msg("%d ", arr[i][j]);
            }
            dbg_msg("\n");
        }
#endif
    }

    private:
    int arr[const_max_n][const_max_n];
    xqueue<coord> q;
};

void solve() {
    int ans;
    int idx;
    scanf("%d", &idx);
    dbg_msg("test.. %d\n", idx);

    solver sol;
    dbg_msg("before..\n");
    sol.print();
    ans = sol.run();
    dbg_msg("after..\n");
    sol.print();
    printf("#%d %d\n", idx, ans);
}
int main() {
#ifdef DBG_STDIN
    freopen("inputs/swe_1226_input.txt", "r", stdin);
#endif
    for(int i=0; i<10; ++i) {
        solve();
    }
    return 0;
}
