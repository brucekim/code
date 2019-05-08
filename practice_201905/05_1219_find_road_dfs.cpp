/* start 0
   dest  99
   no. of vertex <= 98 (excluding start and dest)
   no. of road at a vertex <= 2

   input
   first line: test case no. # + no. of roads
   next line: edge pair

   output
   #tc no. # 1 or 0 where 1 means there is road between 0 - 99 whereas 0 means there is no road 

expected ans
#1 1
#2 1
#3 1
#4 0
#5 1
#6 1
#7 0
#8 0
#9 0
#10 0

to do
* graph implementation
* traverse graph - dfs
   */
#include <cstdio>

const static int err_code = 0x3030'3030;

struct node {
    node(int _v) : v(_v) {}
    int v;
    node *prev = nullptr;
    node *next = nullptr;
};

class xstack {
    public:
        virtual ~xstack() {
            while(top != nullptr) {
                node *tmp = top;
                top = top->prev;
                delete tmp;
            }
        }
        void push(int n) {
            node *tmp = new node(n);
            if (top == nullptr) {
                top = tmp;
            } else {
                top->next = tmp;
                tmp->prev = top;
                top = top->next;
            }
            ++sz;
        }
        void pop() {
            if (top != nullptr) {
                node *tmp = top;
                top = top->prev;
                top->next = nullptr;
                delete tmp;
                --sz;
            }
        }
        int gettop() {
            if (top == nullptr) {
                return err_code;
            } else {
                return top->v;
            }
        }
        bool isEmpty() {
            return sz > 0 ? false : true;
        }
    private:
        int sz = 0;
        node *top = nullptr;
};

class xlist {
    public:
        virtual ~xlist() {
            while(head != nullptr) {
                node *tmp = head;
                head = head->next;
                delete tmp;
            }
        }
        void push_back(int w) {
            node *n = new node(w);
            if (head == nullptr) {
                head = tail = n;
            } else {
                tail->next = n;
                tail = tail->next;
            }
        }
        void print() {
            node *tmp = head;
            while(tmp != nullptr) {
                printf("%d->", tmp->v);
                tmp = tmp->next;
            }
            printf("\n");
        }
    private:
        node *head = nullptr;
        node *tail = nullptr;
};
class graph {
    public:
        graph(int _cntV): cntV(_cntV) {
            adj = new xlist[cntV];
            visited = new bool[cntV]{0};
        }
        virtual ~graph() {
            delete[] adj;
            delete[] visited;
        }
        void addEdge(int v, int w) {
            adj[v].push_back(w);
        }
        void print() {
            for (int i=0; i<cntV; ++i) {
                printf("%d :", i);
                adj[i].print();
            }
        }
        bool dfs(int s, int d) {
            visited[s] = true;
            xstack s;
            s.push(s);
            while(!s.isEmpty()) {
            }
        }
    private:
        int cntV;
        xlist *adj;
        bool *visited;
};

void test() {
    /*    0
     * 1    4
     *   2    3
     * 
     */
    graph g(5);
    g.addEdge(0, 4);
    g.addEdge(0, 1);
    g.addEdge(1, 0);
    g.addEdge(1, 2);
    g.addEdge(2, 1);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(4, 0);
    g.addEdge(4, 2);
    g.addEdge(4, 3);
    g.print();
    g.dfs(0, 3);
}

void solve() {
}

int main() {
    test();
    return 0;
}
