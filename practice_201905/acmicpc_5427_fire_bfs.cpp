#include <cstdio>

//#define DBG
//#define DBG_STDIN

#ifdef DBG
#define dbg_msg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg_msg(fmt, ...)
#endif

const static int const_max_row = 1001;
const static int const_max_sz = 1000001;
const static int const_err_code = 0x3f3f3f3f;
const static char c_fire = '*';
const static int const_fire = 1;
const static char c_wall = '#';
const static int const_wall = -2;
const static char c_sangun = '@';
const static int const_sangun = 0;
const static char c_empty = '.';
const static int const_empty = 0;


struct coord {
    coord(int _r=0, int _c=0) : r(_r), c(_c) {}
    int r, c;
};

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

//circular q
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
        if ((rear == capa-1 && front == 0) || (rear == (front-1)%capa)) {
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
        } else if (front == capa -1) {
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
    int capa, sz, front, rear;

};

//solver
class solver {
    public:
    solver() {
        scanf("%d %d", &w, &h);
        char *row = new char[const_max_row]{0};
        arr = new int[const_max_row*const_max_row]{0};
        arr_exit = new int[const_max_row*const_max_row]{0};

        for(int i=0; i<h; ++i) {
            scanf("%s", row);
            for(int j=0; j<w; ++j) {
                int tmp;
                arr_exit[idx(i, j)] = 0;
                switch(row[j]) {
                    case c_fire: {
                        qfire.enq(coord(i, j));
                        dbg_msg("enq (%d %d)\n", i, j);
                        tmp = const_fire;
                        break;
                    }
                    case c_empty: {
                        tmp = const_empty;
                        break;
                    }
                    case c_wall: {
                        tmp = const_wall;
                        break;
                    }
                    case c_sangun: {
                        tmp = const_sangun;
                        qmen.enq(coord(i, j));
                        arr_exit[idx(i, j)] = 1;
                        dbg_msg("sangun (%d %d)\n", i, j);
                        break;
                    }
                }
                arr[idx(i, j)] = tmp;
            }
        }
        delete[] row;
        dbg_msg("input done..\n");

    }
    void print() {
#ifdef DBG
        for(int i=0; i<h; ++i) {
            for(int j=0; j<w; ++j) {
                dbg_msg("%d ", arr[idx(i, j)]);
            }
            dbg_msg("\n");
        }
#endif
    }
    void printSangun() {
#ifdef DBG
        for(int i=0; i<h; ++i) {
            for(int j=0; j<w; ++j) {
                dbg_msg("%d ", arr_exit[idx(i, j)]);
            }
            dbg_msg("\n");
        }
#endif
    }
    void run() {
        /*
        updateFire();
        int ans = searchExit();
        */
        int ans = find();
        if (ans > 0) {
            printf("%d\n", ans);
        } else {
            printf("IMPOSSIBLE\n");
        }
    }

    int find() {
        while (true) {
            int qFireSz = qfire.getSize();
            while (qFireSz--) {
                coord t = qfire.getFront();
                qfire.deq();
                for (int i = 0; i < 4; ++i) {
                    int r1 = t.r + dr[i];
                    int c1 = t.c + dc[i];
                    if (valid(r1, c1) == true && arr[idx(r1, c1)] == const_empty) {
                        arr[idx(r1, c1)] = arr[idx(t.r, t.c)] + 1;
                        qfire.enq(coord(r1, c1));
                    }
                }
            }

            int qMenSz = qmen.getSize();
            while (qMenSz--) {
                coord t = qmen.getFront();
                qmen.deq();
                for (int i = 0; i < 4; ++i) {
                    int r1 = t.r + dr[i];
                    int c1 = t.c + dc[i];
                    if (valid(r1, c1) == false) {
                        //found
                        return arr_exit[idx(t.r, t.c)];
                    }
                    if (arr[idx(r1, c1)]  == 0 && arr_exit[idx(r1, c1)] == 0) {
                        arr_exit[idx(r1, c1)] = arr_exit[idx(t.r, t.c)] + 1;
                        qmen.enq(coord(r1, c1));
                    }
                }
            }
            if (qmen.isEmpty() == true) {
                return 0;
            }
        }
    }

    void updateFire() {
        while(!qfire.isEmpty()) {
            coord t = qfire.getFront();
            qfire.deq();
            for(int i=0; i<4; ++i) {
                int r1 = t.r + dr[i];
                int c1 = t.c + dc[i];
                if (valid(r1, c1) == true && arr[idx(r1, c1)] == const_empty) {
                    arr[idx(r1, c1)] = arr[idx(t.r, t.c)] + 1;
                    qfire.enq(coord(r1, c1));
                }
            }
        }
    }
    bool valid(int r, int c) {
        return r >=0 && r < h && c >=0 && c < w;
    }
    int searchExit() {
        while(!qmen.isEmpty()) {
            coord t = qmen.getFront();
            qmen.deq();
            for(int i=0; i<4; ++i) {
                int r1 = t.r + dr[i];
                int c1 = t.c + dc[i];
                if (valid(r1, c1) == false) {
                    //found
                    return arr_exit[idx(t.r, t.c)];
                }
                if (arr_exit[idx(t.r, t.c)] + 1 < arr[idx(r1, c1)] &&
                   arr_exit[idx(r1, c1)] == 0) {
                    arr_exit[idx(r1, c1)] = arr_exit[idx(t.r, t.c)] + 1;
                    qmen.enq(coord(r1, c1));
                }
            }
        }
        return 0;
    }
    virtual ~solver() {
        delete[] arr;
        delete[] arr_exit;
    }
    int idx(int r, int c) {
        return r*w + c;
    }

    private:
    int w, h;
    int *arr;
    int *arr_exit;
    xqueue<coord> qfire;
    xqueue<coord> qmen;
};

//solve
void solve() {
    solver sol;
    sol.print();
    sol.run();
    dbg_msg("update file\n");
    sol.print();
    dbg_msg("update sangun\n");
    sol.printSangun();
}

//main
int main() {
#ifdef DBG_STDIN
    freopen("inputs/acmicpc_5427_input.txt", "r", stdin);
#endif
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i) {
        solve();
    }
    return 0;
}
