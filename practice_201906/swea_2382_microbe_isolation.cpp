//#define DBG_STDIN
//#define DBG_TIME
//#define DBG

#include <stdio.h>
#ifdef DBG_TIME
#include <time.h>
#endif

#ifdef DBG
#define dbg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg(fmt, ...)
#endif

class meas {
#ifdef DBG_TIME
    public:
        meas() {
            start = clock(); 
        }
        virtual ~meas() {
            end = clock(); 
            printf("consume.. %lf\n", static_cast<double>((end-start)/CLOCKS_PER_SEC));
        }
    private:
        time_t start, end;
        double duration;
#endif
};

const static int const_err_code = 0x3f3f3f3f;

//up down left right 1 2 3 4
int dr[] = {0, -1, 1, 0, 0};
int dc[] = {0, 0, 0, -1, 1};
int invert[] = {0, 2, 1, 4, 3};

struct coord {
    coord(int _r=-1, int _c=-1) : r(_r), c(_c) {}
    int r, c;
};

struct microbe {
    microbe(int _cnt=-1, int _d=-1) : cnt(_cnt), d(_d) {}
    unsigned int cnt;
    int d; //direction
    bool operator >= (const microbe &b) {
        return cnt >= b.cnt;
    }

    bool operator < (const microbe &b) {
        return cnt < b.cnt;
    }
    operator int() {
        return cnt;
    }
};

template <typename T>
struct node {
    node(T _data) : data(_data), next(nullptr) {}
    T data;
    node<T> *next;
};

template <typename T>
class xqueue_iterator {
    public:
        xqueue_iterator(node<T> *it) : current(it) {}
        T& operator*() {
            return current->data;
        }
        xqueue_iterator& operator++() {
            current = current->next;
            return *this;
        }
        bool operator==(const xqueue_iterator<T> &it) {
            return current == it.current;
        }
        bool operator!=(const xqueue_iterator<T> &it) {
            return current != it.current;
        }
    private:
        node<T> *current;
};
template <typename T>
class xqueue {
    public:
        using iterator = xqueue_iterator<T>;
        xqueue() : head(nullptr), tail(nullptr), sz(0) {}
        virtual ~xqueue() {
            flush();
        }
        void flush() {
            while(head != nullptr) {
                node<T> *tmp = head;
                head = head->next;
                delete tmp;
            }
            head = tail = nullptr;
            sz=0;
        }
        void push_back(T data) {
            node<T> *tmp = new node<T>(data);
            ++sz;
            if (head == nullptr) {
                head = tail = tmp;
            } else {
                tail->next = tmp;
                tail = tail->next;
            }
        }
        void pop_front() {
            if (head != nullptr) {
                node<T> *tmp = head;
                head = head->next;
                if (head == nullptr) {
                    tail = nullptr;
                }
                delete tmp;
                --sz;
            }
        }
        T& get_front() {
            return head->data;
        }
        int getSize() { return sz; }
        bool isEmpty() { return sz == 0; }
        iterator begin() { return iterator(head); }
        iterator end() { return iterator(nullptr); }

        int get_sum() {
            iterator _end = end();
            int sum = 0;
            for (iterator it = begin(); it != _end; ++it) {
                sum += (*it);
            }
            return sum;
        }
        T get_max() {
            iterator _end = end();
            T tmp = *(begin());
            for (iterator it = begin(); it != _end; ++it) {
                if (tmp < (*it)) {
                    tmp = *it;
                }
            }
            return tmp;
        }

    private:
        node<T> *head, *tail;
        int sz;
};

class solver {
    public:
        solver() : ans(0) {
            scanf("%d %d %d", &N, &M, &K);
            int sz_nbyn = N*N;
            arr = new xqueue<microbe>[sz_nbyn];
            visited = new bool[sz_nbyn];

            int r, c, cnt, d;
            for(int i=0; i<K; ++i) {
                scanf("%d %d %d %d", &r, &c, &cnt, &d);
                arr[idx(r, c)].push_back(microbe(cnt, d));
                q.push_back(coord(r, c));
            }
        }
        virtual ~solver() {
            delete[] arr;
        }
        inline int idx(int r, int c) {
            return r*N + c;
        }
        void init_visited() {
            int sz_nbyn = N*N;
            for(int i=0; i<sz_nbyn; ++i) {
                visited[i] = false;
            }
        }
        void info() {
            printf("info..N(%d), M(%d), K(%d) qsz(%d)\n", N, M, K, q.getSize());
            for(int i=0; i<N; ++i) {
                for(int j=0; j<N; ++j) {
                    xqueue<microbe> &mblist = arr[idx(i, j)];
                    if (mblist.isEmpty() == true) {
                        printf("(        ) ");
                    } else {
                        printf("(%4d %d:%d) ", mblist.get_front().cnt, mblist.get_front().d, mblist.getSize());
                    }
                }
                printf("\n");
            }
        }
        bool isEdge(int r, int c) {
            return r == N-1 || r == 0 || c == 0 || c == N-1;
        }
        int run() {
            int round = 0;

            for(int k=0; k<M; ++k) {

                //move
                init_visited();
                int sz_mb = q.getSize();
                for(int i=0; i<sz_mb; ++i) {
                    coord ch = q.get_front();
                    q.pop_front();
                    xqueue<microbe> &mblist = arr[idx(ch.r, ch.c)];

                    if (mblist.isEmpty() == true) {
                        continue;
                    }
                    microbe t_mb = mblist.get_front();
                    mblist.pop_front();
                    int r2 = ch.r + dr[t_mb.d];
                    int c2 = ch.c + dc[t_mb.d];
                    arr[idx(r2, c2)].push_back(t_mb);
                    q.push_back(coord(r2, c2));
                }

                sz_mb = q.getSize();
                for(int i=0; i<sz_mb; ++i) {
                    coord ch = q.get_front();
                    q.pop_front();
                    xqueue<microbe> &mblist = arr[idx(ch.r, ch.c)];
                    if (mblist.isEmpty() == true) {
                        continue;
                    }
                    
                    microbe t_mb = mblist.get_front();
                    mblist.pop_front();
                    if (isEdge(ch.r, ch.c) == true) {
                        t_mb.cnt = t_mb.cnt/2;
                        if (t_mb.cnt == 0) {
                            continue;
                        }
                        t_mb.d = invert[t_mb.d];
                    }
                    arr[idx(ch.r, ch.c)].push_back(t_mb);
                    q.push_back(ch);
                }

                sz_mb = q.getSize();
                for(int i=0; i<sz_mb; ++i) {
                    coord ch = q.get_front();
                    q.pop_front();
                    xqueue<microbe> &mblist = arr[idx(ch.r, ch.c)];

                    //sort & choose d & delete microbes except first one
                    if (mblist.getSize() > 1) {
                        int t_cnt  = mblist.get_sum();
                        microbe t_mb = mblist.get_max();
                        int t_d = t_mb.d;
                        mblist.flush();
                        mblist.push_back(microbe(t_cnt, t_d));
                        dbg("sorted(%d %d) sumcnt(%d) front d(%d) frontcnt(%d)..\n", ch.r, ch.c, t_cnt, t_d, mblist.get_front().cnt);
                    }
                    if (visited[idx(ch.r, ch.c)] == false) {
                        visited[idx(ch.r, ch.c)] = true;
                        q.push_back(ch);
                    }
                }

            }

           int sz_mb = q.getSize();
            for(int i=0; i<sz_mb; ++i) {
                coord ch = q.get_front();
                q.pop_front();
                xqueue<microbe> &mblist = arr[idx(ch.r, ch.c)];
                if (mblist.getSize() > 0) {
                    ans += mblist.get_sum();
                    mblist.flush();
                }
            }

            return ans;
        }
    private:
        int ans;
        int N, M, K;
        xqueue<microbe> *arr;
        bool *visited;
        xqueue<coord> q;
        meas meas_test;
};

void solve(int idx) {
    int ans = 0;
    solver sol;
    ans = sol.run();
    printf("#%d %d\n", idx, ans);
}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/swea_2382_input.txt", "r", stdin);
#endif
    int t;
    scanf("%d", &t);
#ifdef DBG_STDIN
    t = t;
#endif
    for(int i=0; i<t; ++i) {
        solve(i+1);
    }
    return 0;
}
