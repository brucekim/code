/* 4.2 Given a directed graph, design an algorithm to find out where there is a route between two nodes. */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
  public:
    Graph(int _n) : n(_n + 1)
    {
        adj = new vector<int>[n];
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }
    bool hasRoute(int u, int v)
    {
        queue<int> qu;
        int visited[n];
        for (auto &&it : visited)
        {
            it = -1;
        }
        qu.push(u);
        visited[u] = u;
        auto bfs = [](int s, int d, int visited[], queue<int> &q, vector<int> *adj) -> bool {
            int t = q.front();
            q.pop();
            for (auto &&it : adj[t])
            {
                if (it == d)
                    return true;
                if (visited[it] == -1)
                {
                    visited[it] = s;
                    q.push(it);
                }
            }
            return false;
        };

        while (!qu.empty())
        {
            if (bfs(u, v, visited, qu, adj) == true)
                return true;
        }
        return false;
    }

  private:
    vector<int> *adj;
    int n;
};

void test()
{
    Graph g(10);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(6, 1);

    cout << g.hasRoute(1, 1) << endl;
    cout << g.hasRoute(1, 6) << endl;
    cout << g.hasRoute(1, 5) << endl;

    g.addEdge(5, 1);
    cout << g.hasRoute(1, 1) << endl;
}

int main()
{
    test();
    return 0;
}
