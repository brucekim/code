#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>

using namespace std;

#define MAX_N 1000
class Graph
{
  public:
    Graph(int _n) : n(_n)
    {
        for (int i = 0; i < n + 1; ++i)
        {
            for (int j = 0; j < n + 1; ++j)
            {
                mat[i][j] = 0;
            }
        }
    }
    void AddEdge(int u, int v)
    {
        mat[u][v] = mat[v][u] = 1;
    }

    void Bfs(int u)
    {
        queue<int> q;
        InitVisited();
        q.push(u);
        visited[u] = true;
        while (!q.empty())
        {
            int t = q.front();
            cout << t << " ";
            q.pop();
            for (int i = 1; i <= n; ++i)
            {
                if ((mat[t][i] == 1) && visited[i] == false)
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << "\n";
    }
    void Dfs(int u)
    {
        InitVisited();
        visited[u] = true;
        DfsUtil(u);
        cout << "\n";
    }
    void DfsUtil(int u)
    {
        cout << u << " ";
        for (int i = 1; i <= n; ++i)
        {
            if ((mat[u][i] == 1) && visited[i] == false)
            {
                visited[i] = true;
                DfsUtil(i);
            }
        }
    }

  private:
    int n;
    int mat[MAX_N + 1][MAX_N + 1];
    bool visited[MAX_N + 1];
    void InitVisited()
    {
        for (int i = 0; i < n + 1; ++i)
        {
            visited[i] = false;
        }
    }
};
void test()
{
    int N, M, V;
    int u, v;
    cin >> N >> M >> V;
    Graph g(N);
    for (int i = 0; i < M; ++i)
    {
        cin >> u >> v;
        g.AddEdge(u, v);
    }
    g.Dfs(V);
    g.Bfs(V);
}
int main()
{
    test();
    return 0;
}
