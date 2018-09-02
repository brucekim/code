#include <iostream>

using namespace std;

#define NODE 5
class Graph {
   public:
    Graph() {
        for (int i = 0; i <= NODE; ++i) {
            for (int j = 0; j <= NODE; ++j) {
                g[i][j] = false;
            }
        }
    }
    void insert(int u, int v) {
        g[u][v] = true;
        g[v][u] = true;
    }
    bool hasLink(int u, int v) {
        return g[u][v];
    }
    bool hasAnyLink(int u) {
        bool ret = false;
        for (int i = 1; i <= NODE; ++i) {
            ret |= g[u][i];
        }
        return ret;
    }

   private:
    bool g[NODE + 1][NODE + 1];
};
int main() {
    int n, u, v;
    Graph g;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> u >> v;
        g.insert(u, v);
    }
    bool positive = g.hasLink(1, 3) &&
                    g.hasLink(1, 4) &&
                    g.hasLink(3, 4);

    bool negative = g.hasAnyLink(2) ||
                    g.hasAnyLink(5);

    if (positive == true && negative == false) {
        cout << "Wa-pa-pa-pa-pa-pa-pow!";
    } else {
        cout << "Woof-meow-tweet-squeek";
    }

    return 0;
}
