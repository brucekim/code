#include <cstdio>

//#define DBG
#define DBG_STDIN

#ifdef DBG
#define dbg_msg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg_msg(fmt, ...)
#endif

const static int const_max_depth = 10000;
const static int const_err_code = 0x3f3f3f3f;

const static int const_max_n = 8;
const static int const_max_k = 5;

struct coord {
    coord(int _r=0, int _c=0) : r(_r), c(_c) {}
    int r;
    int c;
};

template <typename T>
struct node {
    node(T _data) : data(_data), prev(nullptr), next(nullptr) {}
    T data;
    node<T> *prev;
    node<T> *next;
};

template <typename T>
class xlist_iterator {
    public:
    xlist_iterator(node<T> *it) : current(it) {}
    xlist_iterator& operator++() {
        current = current->next;
        return *this;
    }
    T& operator*() {
        return current->data;
    }
    bool operator!=(const xlist_iterator<T> &it) const {
        return current != it.current;
    }
    bool operator==(const xlist_iterator<T> &it) const {
        return current == it.current;
    }
    private:
    node<T> *current;

};

template <typename T>
class xlist {
    public:
    using iterator = xlist_iterator<T>;
    xlist() : head(nullptr), tail(nullptr), sz(0) {}
    virtual ~xlist() {
        while(head != nullptr) {
            node<T> *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    void push_back(T data) {
        node<T> *tmp = new node<T>(data);
        ++sz;
        if (head == nullptr) {
            head = tail = tmp;
        } else {
            tmp->prev = tail;
            tail->next = tmp;
            tail = tail->next;
        }
    }
    void pop_front() {
        if (head != nullptr) {
            node<T> *tmp = head;
            head = head->next;
            head->prev = nullptr;
            delete tmp;
            --sz;
        }
    }
    T &&front() {
        return head->data;
    }
    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(nullptr);
    }

    private:
    int sz;
    node<T> *head;
    node<T> *tail;
};

class solver {
    public:
        solver(int _n, int _k, int (*_arr)[const_max_n], xlist<coord> *_list_peak) :
            n(_n), k(_k), arr(_arr), list_peak(_list_peak), max(-1) {}

        void print() {
            dbg_msg("map:\n");
            for (int i=0; i<n; ++i) {
                for (int j=0; j<n; ++j) {
                    dbg_msg("%d ", arr[i][j]);
                }
                dbg_msg("\n");
            }
            dbg_msg("highest::\n");
            xlist<coord>::iterator end = list_peak->end();
            for(xlist<coord>::iterator it = list_peak->begin(); it != end; ++it) {
                dbg_msg("(%d %d)", (*it).c, (*it).r);
            }
            dbg_msg("\n");
        }
        void solve() {
            xlist<coord>::iterator end = list_peak->end();
            for(xlist<coord>::iterator it = list_peak->begin(); it != end; ++it) {
                int r1 = (*it).r;
                int c1 = (*it).c;
                int h1 = arr[c1][r1];
                dbg_msg("peak..(%d %d) h(%d)\n", c1, r1, h1);
                visited[c1][r1] = true;
                dfs(h1, r1, c1, false, 1);
                visited[c1][r1] = false;
            }
        }
        void dfs(int h1, int r1, int c1, bool kcut, int dist) {
            dbg_msg("(%d %d) h(%d) l(%d) ->", c1, r1, h1, dist);
            if (max < dist) {
                max = dist;
            }
            for (int i=0; i<4; ++i) {
                int r2 = r1 + mat_row[i];
                int c2 = c1 + mat_col[i];
                if (isValid(r2, c2) == true) {
                    int h2 = arr[c2][r2];
                    if (h2 < h1) {
                        visited[c2][r2] = true;
                        dfs(h2, r2, c2, kcut, dist+1);
                        visited[c2][r2] = false;
                    } else if (kcut == false && ((h2-h1) < k)) {
                        visited[c2][r2] = true;
                        dfs(h1-1, r2, c2, true, dist+1);
                        visited[c2][r2] = false;
                    }
                }
            }
            dbg_msg("backtrack!\n");
        }
        int answer() {
            return max;
        }

        bool isValid(int row, int col) {
            return row >= 0 && row < n && col >= 0 && col < n && visited[col][row] == false;
        }
    private:
        int mat_row[4]{-1, 1, 0, 0};
        int mat_col[4]{0, 0, -1, 1};
        int n, k, max;
        int (*arr)[const_max_n];
        bool visited[const_max_n][const_max_n]{{false}};
        xlist<coord> *list_peak;
};

void solve() {
    int ans = 0;
    int n, k;
    int arr[const_max_n][const_max_n]{0};
    int highest = -1;
    int max_trail = -1;
    xlist<coord> list_peak;

    // input
    scanf("%d %d", &n, &k);
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            int t;
            scanf("%d", &t);
            arr[i][j] = t;
            if (highest < t) {
                highest = t;
            }
        }
    }

    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            if (arr[i][j] == highest) {
                list_peak.push_back(coord(j, i));
            }
        }
    }
    solver sol(n, k, arr, &list_peak);
    sol.print();
    sol.solve();
    dbg_msg("ans:%d\n", sol.answer());
    printf("%d\n", sol.answer());
}
int main() {
#ifdef DBG_STDIN
    freopen("inputs/swe_pretest_1949_input.txt", "r", stdin);
#endif
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        //dbg_msg("#%d ", i+1);
        printf("#%d ", i+1);
        solve();
    }
    return 0;
}
