/* 3d array on 1d array: how-to 
https://stackoverflow.com/questions/7367770/how-to-flatten-or-index-3d-array-in-1d-array*/
#include <cstdio>

//#define DBG
#define DBG_STDIN

#ifdef DBG
#define dbg_msg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg_msg(fmt, ...)
#endif


const static int const_fresh = 0;
const static int const_mature = 1;
const static int const_empty = -1;

const static int const_max_val = 1000000;
const static int const_err_code = 0x3f3f3f3f;

struct coord {
    coord(int _h=0, int _r=0, int _c=0) : r(_r), c(_c), h(_h) {}
    int h, r, c;
};
template <typename T>
class xqueue {
    public:
        xqueue(int _capa=const_max_val) : capa(_capa), sz(0), front(-1), rear(-1) {
            arr = new T[capa]();
        }
        virtual ~xqueue() {
            delete[] arr;
        }
        int enque(T data) {
            if ((rear == capa-1 && front == 0) || (rear == (front-1)%capa)) {
                return const_err_code;
            } else if (front == -1) {
                front = rear = 0;
            }else if (rear == capa-1 && front != 0) {
                rear = 0;
            } else {
                ++rear;
            } arr[rear] = data; ++sz;
            return 0;
        }
        int deque() {
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
        int capa, sz;
        int front, rear;
        T *arr;
};

int h1[] = {1, -1, 0, 0, 0, 0};
int n1[] = {0, 0, 0, 0, 1, -1};
int m1[] = {0, 0, 1, -1, 0, 0};
class solver {
    public:
        solver() : fresh(0), ans(-1) {
            scanf("%d %d %d", &m, &n, &h);
            arr = new int[m*n*h]{0};
            int tmp;
            for(int i=0; i<h; ++i) {
                for(int j=0; j<n; ++j) {
                    for(int k=0; k<m; ++k) {
                        scanf("%d", &tmp);
                        arr[idx(i, j, k)] = tmp;
                        if (tmp == const_fresh) {
                            ++fresh;
                        } else if (tmp == const_mature) {
                            q.enque(coord(i, j, k));
                        }
                    }
                }
            }
            if (fresh == 0) {
                ans = 0;
            }
        }
        virtual ~solver() {
            delete[] arr;
        }
        void print() {
#ifdef DBG
            printf("h:%d n:%d m:%d\n", h, n, m);
            for(int i=0; i<h; ++i) {
                for(int j=0; j<n; ++j) {
                    for(int k=0; k<m; ++k) {
                        printf("%d ", arr[idx(i, j, k)]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
#endif
        }
        int idx(int i, int j, int k) {
            return i*m*n + j*m + k;
        }
        bool valid(int i, int j, int k) {
            return i>=0 && i < h && j >= 0 && j < n && k >= 0 && k < m;
        }
        int run() {
            if (ans == 0) {
                return ans;
            }
            while(!q.isEmpty()) {
                const coord pop = q.getFront();
                q.deque();

                for(int i=0; i<6; ++i) {
                    int ival = pop.h + h1[i];
                    int jval = pop.r + n1[i];
                    int kval = pop.c + m1[i];
                    if (valid(ival, jval, kval) == true && arr[idx(ival, jval, kval)] == const_fresh) {
                        dbg_msg("if valid(%d %d %d):%d == true && arr[%d] == %d\n", ival, jval, kval, valid(ival, jval, kval), idx(ival, jval, kval), arr[idx(ival, jval, kval)]);
                        ans = arr[idx(ival, jval, kval)] = arr[idx(pop.h, pop.r, pop.c)] + 1;
                        dbg_msg("enq coord(%d, %d, %d) val(%d)\n", ival, jval, kval, ans);
                        q.enque(coord(ival, jval, kval));
                        --fresh;
                    }
                }
            }
            return fresh == 0 ? ans - 1 : -1;
        }
    private:
        int m, n, h, fresh;
        int *arr;
        int ans;
        xqueue<coord> q;
};
int main() {
#ifdef DBG_STDIN
    freopen("inputs/acmicpc_7569_input.txt", "r", stdin);
#endif
    solver sol;
    dbg_msg("before:\n");
    sol.print();
    printf("%d\n", sol.run());
    dbg_msg("after:\n");
    sol.print();
    return 0;
}
