/* https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
 * https://www.geeksforgeeks.org/detect-negative-cycle-graph-bellman-ford/
 */

#include <cstdio>

const static int const_sz_max = 1000;
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
        T *arr;
        int capa, sz;
};

class graph {
    public:
        graph(int _cntV) : cntV(_cntV) {
        }
        virtual ~graph() {
        }

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

void bellmanford(graph &g, int src) {
    int dist[g.cntV];


    // step 1 init
    for(int i=0; i<g.cntV; ++i) {
        dist[i] = const_inf;
    }
    dist[src] = 0;

    for(int i=0; i<g.cntV-1; ++i) {
        for (int j=0; j<g.cntE; ++j) {
            int u = g[j].src;
            int v = g[j].dest;
            int w = g[j].w;
            if (dist[u] != const_inf && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int j=0; j<g.cntE; ++j) {
        int u = g[j].src;
        int v = g[j].dest;
        int w = g[j].w;
        if (dist[v] > dist[u] + w) {
            printf("graph contains negative weight cycle\n");
        }
    }

    printf("dist\n");
    for(int i=0; i<g.cntV; ++i) {
        printf("%d \t %d\n", i, dist[i]);
    }
}

void solve() {
    graph g(5);
    g.addEdge(0, 1, -1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 2, 5);
    g.addEdge(3, 1, 1);
    g.addEdge(4, 3, -3);

    bellmanford(g, 0);

}
int main() {
    solve();
    return 0;
}
