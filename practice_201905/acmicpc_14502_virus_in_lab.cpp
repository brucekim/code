/* 0 empty, 1 wall, 2 virus 
 * n(row) x m(col)
 * no. of new walls to be built: 3
 * virus can pollute to up/down/left and right
 * given map , find max. size of safety zone with best construction of 3 walls
 *
 * design:
 * 1. dfs for possible permutation regarding virus given to map
 * 2. once building up 3 walls in possible permutation, start bfs for polluting empty zones
 * 3. get the size of safety zone after step. 2
 * 4. repeat from step 1 till exhausting all possible permutation
 *
 * input
 *  - n, m (3<= n, m <= 8)
 *  - n row by m column <- value
 *
 *
 * */
#include <cstdio>

//#define DBG

const static int const_max_sz = 1000;
const static int const_err_code = 0x3f3f3f3f;
const static int const_empty = 0;
const static int const_wall = 1;
const static int const_virus = 2;

struct coord {
    coord (int _r=0, int _c=0) : r(_r), c(_c) {}
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
            ++sz;
            arr[rear] = data;
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
        const T& getFront() {
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
        int front, rear, capa, sz;
};

template <typename T>
class xstack {
    public:
        xstack() : capa(const_max_sz), sz(0) {
            arr = new T[capa]();
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
        const T& getTop() {
            return arr[sz-1];
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
};

class solver {
    public:
        solver() : max(0) {
            scanf("%d %d", &n, &m);
            arr = new int[n*m];
            t_arr = new int[n*m];

            for(int i=0; i<n; ++i) {
                for(int j=0; j<m; ++j) {
                    scanf("%d", arr + idx(i, j));
                    switch (arr[idx(i, j)]) {
                        case const_virus: {
                                              q_virus.enq(coord(i, j));
                                              break;
                                          }
                        case const_empty: {
                                              q_empty.enq(coord(i, j));
                                              break;
                                          }
                    }
                }
            }
            sz_walls = q_empty.getSize();
            sz_virus = q_virus.getSize();
            visited = new bool[sz_walls];
            for(int i=0; i<sz_walls; ++i) {
                visited[i] = false;
            }
        }
        virtual ~solver() {
            delete arr;
            delete t_arr;
            delete visited;
        }
        void print() {
            printf("map..\n");
            printf("n:%d m:%d sz_walls:%d sz_virus:%d \n", n, m, sz_walls, sz_virus);
            for(int i=0; i<n; ++i) {
                for(int j=0; j<m; ++j) {
                    printf("%d ", arr[idx(i, j)]);
                }
                printf("\n");
            }
            printf("\n");
        }
        
        void printtmp(int cnt) {
            printf("tmp map..safezone:%d\n", cnt);
            for(int i=0; i<n; ++i) {
                for(int j=0; j<m; ++j) {
                    printf("%d ", t_arr[idx(i, j)]);
                }
                printf("\n");
            }
            printf("\n");
        }

        int idx(int r, int c) {
            return r*m+c;
        }
        int run() {
#ifdef DBG
            print();
#endif
            find3walls(0);
            return max;
        }
        void find3walls(int c) {
            if (st.getSize() == 3) {
                int tmp = spread();
                if (max < tmp) {
                    max = tmp;
                }
#ifdef DBG
                for(int i=0; i<3; ++i) {
                    printf("(%d %d) ", st[i].r, st[i].c);
                }
                printf("\n");
                printtmp(tmp);
#endif
                return;
            }
            for(int i=c; i<q_empty.getSize(); ++i) {
                if (visited[i] == false) {
                    visited[i] = true;
                    st.push_back(q_empty[i]);
                    find3walls(i+1);
                    st.pop_back();
                    visited[i] = false;
                }
            }
        }
        bool withinRange(int r, int c) {
            return r >= 0 && r < n && c >= 0 && c < m;
        }
        int spread() {
            int dr[] = {-1, 1, 0, 0};
            int dc[] = {0, 0, -1, 1};

            //copy arr
            for(int i=0; i<n*m; ++i) {
                t_arr[i] = arr[i];
            }
            //build walls
            for(int i=0; i<st.getSize(); ++i) {
                int r = st[i].r;
                int c = st[i].c;
                t_arr[idx(r, c)] = const_wall;
            }
            //spread virus
            xqueue<coord> q_spread;
            int cnt = 0;

            for(int i=0; i<sz_virus; ++i) {
                q_spread.enq(q_virus[i]);
            }
            while(!q_spread.isEmpty()) {
                coord v = q_spread.getFront();
                q_spread.deq();
                for(int i=0; i<4; ++i) {
                    int r2 = v.r+dr[i];
                    int c2 = v.c+dc[i];
                    if (withinRange(r2, c2) == true && t_arr[idx(r2, c2)] == const_empty) {
                        q_spread.enq(coord(r2,c2));
                        t_arr[idx(r2, c2)] = const_virus;
                        ++cnt;
                    }
                }
            }
            return sz_walls - cnt - 3;
        }
    private:
        int n, m, max;
        int sz_walls;
        int sz_virus;
        int *arr;
        int *t_arr;
        bool *visited;
        xqueue<coord> q_virus;
        xqueue<coord> q_empty;
        xstack<coord> st;
};

void solve(){
    solver sol;
    int ans = sol.run();
    printf("%d\n", ans);
}
int main() {
#ifdef DBG
    freopen("inputs/acmicpc_14502_input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
