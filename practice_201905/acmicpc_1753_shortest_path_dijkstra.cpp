/* time limit <= 1sec
 * weight w, w <= 10 자연수
 * vertexes V, edges E (1<=V<=20'000, 1<=E<=300'000)
 *
 * input
 * V E
 * K (1<=K<=V)
 * u v w
 * ...
 *
 * output
 * value(the distance of shortest path from k to ith vertex)
 * 0 (if ith = k)
 * INF (no shortest path)
 */
#include <cstdio>

//#define DBG_STDIN
//#define DBG

#ifdef DBG
#define dbg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg(fmt, ...)
#endif

const static int const_max_sz = 20001;
const static int const_err_code = 0x3f3f3f3f;
const static int INF = 0x7FFFFFFF;

struct vertex {
    vertex(int _v=0, int _w=0) : v(_v), w(_w) {}
    int v, w;
};

template <typename T>
struct node {
    node(T &_data) : data(_data), next(nullptr) {}
    T data;
    node<T> *next;
};

template <typename T>
class xlist_iterator {
    public:
    xlist_iterator(node<T> *it) : current(it) {}
    T& operator*() {
        return current->data;
    }
    xlist_iterator& operator++() {
        current = current->next;
        return *this;
    }
    bool operator==(const xlist_iterator<T>& it) const {
        return current == it.current;
    }
    bool operator!=(const xlist_iterator<T>& it) const {
        return current != it.current;
    }
    private:
    node<T> *current;
};

template <typename T>
class xlist {
    public:
        using iterator = xlist_iterator<T>;
        xlist() : sz(0), head(nullptr), tail(nullptr) {}
        virtual ~xlist() {
            while(head != nullptr) {
                node<T> *tmp = head;
                head = head->next;
                delete tmp;
            }
        }
        iterator begin() {
            return xlist_iterator<T>(head);
        }
        iterator end() {
            return xlist_iterator<T>(nullptr);
        }
        int push_back(T data) {
            node<T> *tmp = new node<T>(data);
            ++sz;
            if (head == nullptr) {
                head = tail = tmp;
            } else {
                tail->next = tmp;
                tail = tmp;
            }
            return 0;
       }
        int getSize() {
            return sz;
        }
        node<T> *getHead() {
            return head;
        }
        bool isEmpty() {
            return sz == 0;
        }

    private:
        int sz;
        node<T> *head;
        node<T> *tail;
};

// adjacent graph
template <typename T>
class graph {
    public:
        void init(int _cntV) {
            cntV = _cntV;
            adj = new xlist<T>[cntV]();
       }
        virtual ~graph() {
            delete[] adj;
        }
        void addEdge(int u, int v, int w) {
            adj[u].push_back(vertex(v, w));
        }
        xlist<T>& operator[] (int idx) {
            return adj[idx];
        }
    private:
        xlist<T>* adj;
        int cntV;
};

class solver {
    public:
        solver() {
            //input
            scanf("%d %d", &cntV, &cntE);
            scanf("%d", &k);
            g.init(cntV+1);
            for(int i=0; i<cntE; ++i) {
                int u, v, w;
                scanf("%d %d %d", &u, &v, &w);
                g.addEdge(u, v, w);
            }

            //init
            sptSet = new bool[cntV+1];
            dist = new int[cntV+1];
            for(int i=0; i<cntV+1; ++i) {
                sptSet[i] = false;
                dist[i] = INF;
            }
 
        }
        virtual ~solver() {
            delete[] dist;
            delete[] sptSet;
        }
        void run() {
#ifdef DBG
            info();
#endif
            dijkstra(k);
            printspt();
        }
        void dijkstra(int s) {
            dist[s] = 0;

            //for all vertexes
            for(int cnt=0; cnt<cntV-1; ++cnt) {
                //pick a vertex that has min edge in sptSet
                int u = getMinimumEdge();
                if (u == -1) {
                    continue;
                }
                sptSet[u] = true;
                dbg("pick %d as min and insert to sptSet\n", u);
                //traverse all adjacent nodes of the vertex picked
                xlist<vertex>::iterator _end  = g[u].end();
                xlist<vertex>::iterator it = g[u].begin();
                for(; it != _end; ++it) {
                    int v = (*it).v;
                    int w = (*it).w;
                    dbg("search neighbor %d .. dist[%d]=%d, w=%d <? dist[%d]=%d\n", v, u, dist[u], w, v, dist[v]);
                    if (sptSet[v] == false && dist[u] != INF && dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        dbg("update dist[%d] to %d(dist[%d] + %d\n", v, dist[u] + w, u, w);
                    }
                }
            }
        }
        int getMinimumEdge() {
            //iterative -> todo priority_queue
            int min = INF;
            int u = -1;
            for(int i=1; i<cntV+1; ++i) {
                if (sptSet[i] == false && dist[i] < min) {
                    min = dist[i];
                    u = i;
                }
            }
            return u;
        }

        void info() {
            printf("info.. V:%d E:%d k:%d\n", cntV, cntE, k);
            for(int i=1; i<=cntV; ++i) {
                printf("%d(sz:%d) -> ", i, g[i].getSize());
                xlist<vertex>::iterator _end = g[i].end();
                for(xlist<vertex>::iterator it = g[i].begin(); it != _end; ++it) {
                    printf("%d(%d) ", (*it).v, (*it).w);
                }
               printf("\n");
            }
        }
        void printspt() {
            for (int i=1; i<=cntV; ++i) {
                if (dist[i] == INF) {
                    printf("INF\n");
                } else {
                    printf("%d\n", dist[i]);
                }
            }
        }
    private:
        int cntV, cntE, k;
        bool *sptSet;
        int *dist;
        graph<vertex> g;
};

void solve() {
    solver sol;
    sol.run();
}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/acmicpc_1753_input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
