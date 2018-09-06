/* 
* link: https://www.acmicpc.net/problem/2479
인접한 노드의 해밍거리가 1인 노드들을 해밍경로라고 하며, 시작점과 끝점이 주어졌을 때 가장 짧은 경로를 찾아서 출력하는 문제다.
* 해밍거리는 두 노드의 값을 서로 xor하고 1인 bit가 1개인지 찾는데
( (n & (n-1)) == 0)
* 해밍거리가 1인 인접한 노드 사이에는 양방향 경로가 존재하는 그래프를 만든다
* 시작점부터 그래프를 bfs로 순회하면서 도착점을 찾기 시작한다.
* visit 배열을 두고, 방문하려는 노드에 현재 노드를 표시한다.
* 도착점을 찾으면 visit배열 기록을 보고 솔루션을 만든다
*/

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class Graph {
   public:
    Graph(int n) : sz(n + 1) {
        adj = new vector<int>[n + 1];
    }
    ~Graph() {
        delete[] adj;
    }
    void insert(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void findShortestPath(int u, int v) {
        int visited[sz];
        for (auto &&it : visited) {
            it = -1;
        }
        queue<int> q;
        q.push(u);
        visited[u] = 0;
        while (!q.empty()) {
            int t = q.front();
            q.pop();
            for (auto &&it : adj[t]) {
                if (visited[it] == -1) {
                    visited[it] = t;
                    q.push(it);
                }
            }
        }
        if (visited[v] == -1) {
            cout << "-1";
        } else {
            stack<int> st;
            int t = v;
            st.push(v);
            while (visited[t] != 0) {
                st.push(visited[t]);
                t = visited[t];
            }
            while (!st.empty()) {
                cout << st.top() << " ";
                st.pop();
            }
        }
    }

   private:
    vector<int> *adj;
    const int sz;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int arr[1002] = {0};
    int n, k, a, b;
    string bits;
    auto strbin_2_int = [](const int &k, const string &bits) -> int {
        int ret = 0;
        for (int i = 0; i < k; ++i) {
            ret |= (bits[k - i - 1] - '0') << i;
        }
        return ret;
    };
    auto one_haming = [](const int &u, const int &v) -> bool {
        if (u == 0 && v == 0) {
            return false;
        }
        int n = u ^ v;
        return (n & (n - 1)) == 0;
    };

    /* input */
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> bits;
        arr[i] = strbin_2_int(k, bits);
    }
    cin >> a >> b;

    /* build graph */
    Graph g(n);
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j < n + 1; ++j) {
            if (i == j) {
                continue;
            }
            if (one_haming(arr[i], arr[j]) == true) {
                g.insert(i, j);
            }
        }
    }
    g.findShortestPath(a, b);

    return 0;
}
