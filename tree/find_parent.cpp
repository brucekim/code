/* https://www.acmicpc.net/problem/11725
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

namespace kim {
    struct node {
        int k;
        vector<node *>e;
        node *parent = nullptr;
        node(int _k) : k(_k) {}
        void link(node *n) {
            e.push_back(n);
        }
    };
    class graph {
    public:
        graph(int _sz) : sz(_sz) {
            for (int i=1; i<=sz; i++) {
                g.push_back(new node(i));
            }
        }
        ~graph() {
            for (int i=0; i<sz; i++) {
                delete g[i];
            }
        }
        void insert(int n1, int n2) {
            
            g[n1-1]->link(g[n2-1]);
            g[n2-1]->link(g[n1-1]);
        }
        
        void bfs() {
            queue<node *> q;
            q.push(g[0]);
            int *visit = new int[sz]();
            visit[0] = 1;
            
            while(!q.empty()) {
                node *pop = q.front();
                q.pop();
                //cout << pop->k << " ";
                
                
                for(int i=0; i<pop->e.size(); i++) {
                    node* it = pop->e[i];
                    if (visit[it->k-1] == 0) {
                        q.push(it);
                        visit[it->k-1] = 1;
                        it->parent = pop;
                    }
                }
            }
            delete []visit;
        }
        int get_parent(int idx) {
            return g[idx-1]->parent->k;
        }
        
    private:
        int sz;
        vector<node*> g;
    };
}
void test() {
    int n;
    int n1, n2;
    cin >> n;
    kim::graph g(n);
    for(int i=0; i<n-1; i++) {
        cin >> n1 >> n2;
        g.insert(n1, n2);
    }
    
    g.bfs();
    for( int i=2; i<=n; i++) {
        cout << g.get_parent(i) << "\n";
    }
}
int main(int argc, const char * argv[]) {
    test();
    return 0;
}
