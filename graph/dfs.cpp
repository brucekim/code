/* 
 https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
 */

#include <iostream>
#include <list>

using namespace std;

namespace b {
    class graph {
    public:
        graph(int _V);
        ~graph();
        void addEdge(int v, int w);
        void DFS(int v);
    private:
        int V;
        list<int> *adj;
        
        void DFSUtil(int v, bool visited[]);
    };
    
    graph::graph(int _V) : V(_V){
        adj = new list<int>[V];
    }
    graph::~graph() {
        delete [] adj;
    }
    void graph::addEdge(int v, int w) {
        adj[v].push_back(w);
    }
    
    void graph::DFS(int v) {
        bool *visited = new bool[V];
        for(int i=0; i<V; i++)
            visited[i] = false;
        DFSUtil(v, visited);
        delete [] visited;
    }
    void graph::DFSUtil(int v, bool *visited) {
        visited[v] = true;
        cout << v << " ";
        list<int>::iterator it = begin(adj[v]);
        while(it != end(adj[v])) {
            if (visited[*it] == false) {
                visited[*it] = true;
                DFSUtil(*it, visited);
            }
            ++it;
        }
    }
}

void test() {
    b::graph g(4);
    
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 0);
    g.addEdge(3, 3);
    
    g.DFS(2);
    
}

int main() {
    test();
    return 0;
}
