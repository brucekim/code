#include <stdio.h>

#define DBG_STDIN

const static int const_sz_max = 6000;
const static int const_inf = 0x7fffffff;

struct edge {
    edge(int _src=0, int _dest=0, int _w=0) : src(_src), dest(_dest), w(_w) {}
    int src, dest, w;
};

template <typename T>
class xlist {
    public:
        xlist() : capa(const_sz_max), sz(0) {
            arr = new T[capa];
        }
        virtual ~xlist() {
            delete[] arr;
        }
        void push_back(T data) {
            if (sz < capa) {
                arr[sz++] = data;
            }
        }
        int getSize() {
            return sz;
        }
        T& operator[] (int idx) {
            return arr[idx];
        }
    private:
        int capa, sz;
        T *arr;
};

class graph {
    public:
        graph(int _cntV) : cntV(_cntV) {}

        void addEdge(int src, int dest, int w) {
            edgeList.push_back(edge(src, dest, w));
            cntE = edgeList.getSize();
        }
        edge& operator[] (int idx) {
            return edgeList[idx];
        }
        int cntV, cntE;
        xlist<edge> edgeList;
};

bool bf(graph &g, int src) {
    int dist[g.cntV+1];
    for(int i=0; i<g.cntV; ++i) {
        dist[i] = const_inf;
    }
    dist[src] = 0;

    for (int i=0; i<g.cntV-1; ++i) {
        for (int j=0; j<g.cntE; ++j) {
            int u = g[j].src;
            int v = g[j].dest;
            int w = g[j].w;
            if (dist[u] != const_inf && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    for (int j=0; j<g.cntE; ++j) {
        int u = g[j].src;
        int v = g[j].dest;
        int w = g[j].w;
        if (dist[u] != const_inf && dist[u] + w < dist[v]) {
            return true;
        }
    }
    return false;
}

void solve() {
    int n, m, w;
    scanf("%d %d %d", &n, &m, &w);
    graph g(n);

    int s, e, t;
    for(int i=0; i<m; ++i) {
        scanf("%d %d %d", &s, &e, &t);
        g.addEdge(s, e, t);
        g.addEdge(e, s, t);
    }
    for(int i=0; i<w; ++i) {
        scanf("%d %d %d", &s, &e, &t);
        g.addEdge(s, e, t * -1);
    }

    if (bf(g, 1) == true) {
        printf("YES\n");
        return;
    }
    printf("NO\n");
}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/acmicpc_1865_input.txt", "r", stdin);
#endif
    int tc;
    scanf("%d", &tc);

    for (int i=0; i<tc; ++i) {
        solve();
    }
    return 0;
}
