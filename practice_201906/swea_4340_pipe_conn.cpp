/*
*/
#include <stdio.h>

#define DBG_STDIN
//#define DBG

#ifdef DBG
#define dbg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg(fmt, ...)
#endif

const static int const_max_n = 50;
const static int const_max_sz = 1000000;
const static int const_err_code = 0x3f3f3f3f;
const static int const_left = -1;
const static int const_up = -1;
const static int const_right = 1;
const static int const_down = 1;
const static int const_non = 0;
const static int const_empty_block = 0;

int dr[7][2] = {
    {0, 0},     //not-used
    {const_non, const_non},     //1
    {const_up, const_down},    //2
    {const_down, const_non},    //3
    {const_down, const_non},    //4
    {const_non, const_up},    //5
    {const_non, const_up},    //6
};
int dc[7][2] = {
    {0, 0},     //not-used
    {const_left, const_right},    //1
    {const_non, const_non},     //2
    {const_non, const_right},     //3
    {const_non, const_left},     //4
    {const_left, const_non},     //5
    {const_right, const_non},     //6
};

int dd[7][2] = {
    {0, 0},
    {0, 2}, //1
    {1, 3}, //2
    {3, 2}, //3
    {3, 0}, //4
    {0, 1}, //5
    {2, 1}, //6
};

//left, up, right, down
bool block[7][4] = {
    {false, false, false, false}, //0
    {true, false, true, false},   //1
    {false, true, false, true},   //2
    {false, false, true, true},   //3
    {true, false, false, true},   //4
    {true, true, false, false},   //5
    {false, true, true, false}    //6
};

//up - down, left - right
int isconn[4] = {2, 3, 0, 1};



//row, column, direction to be connected
struct coord {
    coord(int _r=0, int _c=0, int _d=0) : r(_r), c(_c), d(_d) {}
    int r, c, d;
};

template <typename T>
class xstack {
    public:
    xstack(int _capa=const_max_sz) : capa(const_max_sz), sz(0) {
        arr = new T[capa]();
    }
    virtual ~xstack() {
        delete[] arr;
    }
    int push_back(const T& data) {
        if (sz < capa) {
            arr[sz++] = data;
            return 0;
        } else {
            return const_err_code;
        }
    }
    int pop_back() {
        if (sz == 0) {
            return const_err_code;
        } else {
            --sz;
        }
        return 0;
    }
    T& operator[] (int idx) {
        return arr[idx];
    }
    T& top() {
        return arr[sz-1];
    }
    bool isEmpty() {
        return sz == 0;
    }
    int getSize() {
        return sz;
    }
    private:
    int capa, sz;
    T *arr;
};

class solver{
    public:
    solver() : ans(0x7fffffff) {
        scanf("%d", &n);

        int sz_arr = n*n;
        arr = new int[sz_arr];
        visited = new int[sz_arr];
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                scanf("%d", arr+idx(i, j));
                visited[idx(i, j)] = false;
            }
        }

        rotatable[1].push_back(1);
        rotatable[1].push_back(2);
        rotatable[2].push_back(1);
        rotatable[2].push_back(2);

        rotatable[3].push_back(3);
        rotatable[3].push_back(4);
        rotatable[3].push_back(5);
        rotatable[3].push_back(6);

        rotatable[4].push_back(3);
        rotatable[4].push_back(4);
        rotatable[4].push_back(5);
        rotatable[4].push_back(6);

        rotatable[5].push_back(3);
        rotatable[5].push_back(4);
        rotatable[5].push_back(5);
        rotatable[5].push_back(6);
        
        rotatable[6].push_back(3);
        rotatable[6].push_back(4);
        rotatable[6].push_back(5);
        rotatable[6].push_back(6);
    }
    virtual ~solver() {
        delete[] arr;
        delete[] visited;
    }
    void info() {
        dbg("info.. n:%d\n", n);
        dbg("map.. n:%d\n", n);
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                printf("%d ", arr[idx(i, j)]);
            }
            printf("\n");
        }
        dbg("visited.. n:%d\n", n);
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                printf("%d ", visited[idx(i, j)]);
            }
            printf("\n");
        }
 
    }
    inline int idx(int r, int c) {
        return r*n + c;
    }
    int run() {
        visited[idx(0, 0)] = true;
        st.push_back(coord(0, 0, 2));
        dfs(1);
        st.pop_back();
#ifdef DBG
        info();
#endif
        return ans;
    }
    bool valid(int r, int c) {
        return r >= 0 && r < n && c >=0 && c < n;
    }
    void dfs(int pathlen) {
        coord tmp = st.top();
        //check last block
        if (tmp.r == n-1 && tmp.c == n-1) {
            dbg("last block..\n");
            
            int b = arr[idx(tmp.r, tmp.c)];
            int cnt = rotatable[b].getSize();
            for(int i=0; i< cnt; ++i) {
                int b2 = rotatable[b][i];
                if (block[b2][isconn[tmp.d]] == true && block[b2][2] == true) {
                    if (pathlen < ans) {
                        ans = pathlen;
                        dbg("updating.. b:%d b2:%d tmp.d:%d\n", b, b2, tmp.d);
                        dbg("update ans = %d\n", ans);
                    }
                    return;
                }
            }
        }

        //list up the rotatable to be rotated
        //then, check whether the current pipe is connected to the previous pipe
        //if so, keep jump into
        int b = arr[idx(tmp.r, tmp.c)];
        int cnt = rotatable[b].getSize();
        dbg("pop (%d %d %d) b:%d cnt:%d \n", tmp.r, tmp.c, tmp.d, b, cnt);
        for(int i=0; i< cnt; ++i) {
            // is connected?
            int b2 = rotatable[b][i];
            if (block[b2][isconn[tmp.d]] == true ) {
                dbg("b2=%d tmp.d=%d connected ok\n", b2, tmp.d);
                //search pipe to jump
                for(int i=0; i<2; ++i) {
                    int r2 = tmp.r + dr[b2][i];
                    int c2 = tmp.c + dc[b2][i];
                    dbg("search (%d %d %d)\n", r2, c2, dd[b2][i]);
                    if (valid(r2, c2) == true && arr[idx(r2, c2)] != const_empty_block && visited[idx(r2, c2)] == false) {
                        visited[idx(r2,c2)] = true;
                        dbg("push (%d %d %d)\n", r2, c2, dd[b2][i]);
                        st.push_back(coord(r2, c2, dd[b2][i]));
                        dfs(pathlen+1);
                        st.pop_back();
                        visited[idx(r2,c2)] = false;
                    }
                }
            }
        }
    }
    private:
    int *arr;
    int *visited;
    int n;
    int ans;
    xstack<coord> st;
    xstack<int> rotatable[7];
};

void solve(int idx) {
    solver sol;
    int ans = 0;

    ans = sol.run();

    printf("#%d %d\n", idx, ans);
}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/swea_4340_input.txt", "r", stdin);
#endif
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i) {
        solve(i+1);
    }
    return 0;
}
