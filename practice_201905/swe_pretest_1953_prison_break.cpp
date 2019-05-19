#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>

#define DBG
#define DBG_STDIN

#ifdef DBG
#define dbg_msg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg_msg(fmt, ...)
#endif
const static int const_max_depth = 1000;
const static int const_max_sz = 50;

struct coord {
    coord(int _r=0, int _c=0) : r(_r), c(_c) {}
    int r, c;
    operator std::string() {
        std::stringstream ss;
        ss << "(" << r << ", " << c << ")";
        return ss.str();
    }
};

template <typename T>
class xqueue {
    public:
    xqueue(int _capa=const_max_depth) : capa(_capa), head(-1), tail(-1), sz(0) {
        arr = new T[capa]();
    }
    int enque(T data) {
        coord tmp = static_cast<coord>(data);
        dbg_msg("enque (%d %d)\n", tmp.r, tmp.c);
        if ((tail == capa-1 && head == 0) || (tail == (head-1) % capa)) {
            dbg_msg("buf full\n");
            return -1;
        } else if (head == -1) {
            head = tail = 0;
        } else if (tail == capa-1 && head != 0) {
            tail = 0;
        } else {
            ++tail;
        }
        arr[tail] = data;
        ++sz;
        return 0;

    }
    int deque() {
        if (head == -1) {
            return -1;
        } else if (head == tail) {
            head = tail = -1;
        } else if (head == capa-1) {
            head = 0;
        } else {
            ++head;
        }
        --sz;
        return 0;
    }
    const T& front() {
        return arr[head];

    }
    const T& operator[](int idx) {
        return arr[idx];
    }
    bool isEmpty() {
        return sz == 0;
    }
    int getSize() {
        return sz;
    }
    void print() {
        if (head < tail) {
            for(int i = head; i<=tail; ++i) {
                printf("%s ", arr[i]);
            }
            printf("\n");
        } else {
            for (int i=head; i<capa; ++i) {
                printf("%s ", arr[i]);
            }
            printf("\n");
            for (int i=0; i<=tail; ++i) {
                std::cout << arr[i] << " ";
            }
            printf("\n");
        }
    }
    private:
    T *arr;
    int capa, head, tail, sz;
};

bool tunnel [8][4] = {
    {},
    // up, left, down, right
    {true, true, true, true},   //1
    {true, false, true, false}, //2
    {false, true, false, true}, //3
    {true, false, false, true}, //4
    {false, false, true, true}, //5
    {false, true, true, false}, //6
    {true, true, false, false}, //7
};
int connected[4] = { 2, 3, 0, 1 };

// up, left, down, right
int row[4] = {-1, 0, 1, 0};
int col[4] = {0, -1, 0, 1};

bool isValid(int r, int c, int n, int m) {
    return r >= 0 && r < n && c >= 0 && c < m;
}
void solve() {
    int n, m, r, c, l, t;
    int ans = 0;
    int map[const_max_sz][const_max_sz]{{0}};
    int visited[const_max_sz][const_max_sz]{{0}};

    xqueue<coord> q;

    scanf("%d %d %d %d %d", &n, &m, &r, &c, &l);
    for(int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            scanf("%d", &t);
            visited[i][j] = 0;
            map[i][j] = t;
        }
    }

    dbg_msg("\n");
    visited[r][c] = 1;
    ++ans;
    q.enque(coord(r, c));

    while(q.isEmpty() != true) {
        coord tmp = q.front();
        q.deque();
        int r1 = tmp.r;
        int c1 = tmp.c;
        int d1 = map[r1][c1];
        dbg_msg("now (%d %d):[%d %d]\n", r1, c1, d1, visited[r1][c1]);
        if (visited[r1][c1] == l) {
            dbg_msg("break (%d %d) = %d\n", r1, c1, l);
            break;
        }
        for (int i = 0; i < 4; ++i) {
            if (tunnel[d1][i] == true) {
                int r2 = r1 + row[i];
                int c2 = c1 + col[i];
                int d2 = map[r2][c2];
                if (isValid(r2, c2, n, m) == true && visited[r2][c2] == 0 && tunnel[d2][connected[i]] == true) {
                    visited[r2][c2] = visited[r1][c1]+1;
                    ++ans;
                    q.enque(coord(r2, c2));
                }
            }
        }
    }
    //map
    dbg_msg("map: \n");
    for(int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            dbg_msg("%d ", map[i][j]);
        }
        dbg_msg("\n");
    }
    //visited
    dbg_msg("visited: \n");
    for(int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            dbg_msg("%d ", visited[i][j]);
        }
        dbg_msg("\n");
    }
 
    printf("%d\n", ans);
}
int main() {
#ifdef DBG_STDIN
    freopen("inputs/swe_pretest_1953_input.txt", "r", stdin);
#endif
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        printf("#%d ", i+1);
        solve();
    }
    return 0;
}
