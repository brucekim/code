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

#define DBG

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
class xlist {
    public:
        xlist() : capa(const_max_sz), sz(0) {
            arr = new T[capa]();
        }
        virtual ~xlist() {
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
        int getSize() {
            return sz;
        }
        bool isEmpty() {
            return sz == 0;
        }
        T& operator[] (int idx) {
            return arr[idx];
        }

    private:
        T *arr;
        int capa, sz;
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
            for(int cnt=0; cnt<cntV; ++cnt) {
                //pick a vertex that has min edge in sptSet
                int u = getMinimumEdge();
                if (u == -1) {
                    continue;
                }
                sptSet[u] = true;
                dbg("pick %d as min and insert to sptSet\n", u);
                //traverse all adjacent nodes of the vertex picked
                for(int i=0; i<g[u].getSize(); ++i) {
                    int v = g[u][i].v;
                    int w = g[u][i].w;
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
                printf("%d -> ", i);
                for(int j=0; j<g[i].getSize(); ++j) {
                    printf("%d(%d) ", g[i][j].v, g[i][j].w);
                }
                printf("\n");
            }
        }
        void printspt() {
            printf("spt...\n");
            for (int i=1; i<=cntV; ++i) {
                if (dist[i] == INF) {
                    printf("%d - INF\n", i);
                } else {
                    printf("%d - %d\n", i, dist[i]);
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
#ifdef DBG
    freopen("inputs/acmicpc_1753_input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
