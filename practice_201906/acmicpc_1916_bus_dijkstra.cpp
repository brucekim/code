#include <stdio.h>

#define DBG_STDIN

const static int const_max_sz = 100001;
const static int const_err_code = 0x3f3f3f3f;
const static int INF = 0x7FFFFFFF;

template <typename T>
struct node {
    node(T _data) : data(_data), next(nullptr) {}
    T data;
    node<T> *next;
};

struct vertex {
    vertex(int _v, int _w) : v(_v), w(_w) {}
    int v, w;
};

template <typename T>
class xlist_iterator {
    public:
        xlist_iterator(node<T> *it) : current(it) {}
        xlist_iterator& operator++() {
            current = current->next;
            return *this;
        }
        T& operator*() {
            return current->data;
        }
        bool operator != (const xlist_iterator &it) {
            return current != it.current;
        }
        bool operator == (const xlist_iterator &it) {
            return current == it.current;
        }
    private:
        node<T> *current;
};

template <typename T>
class xlist {
    public:
        using iterator = xlist_iterator<T>;
        xlist() : head(nullptr), tail(nullptr), sz(0) {}
        virtual ~xlist() {
            while(head != nullptr) {
                node<T> *tmp = head;
                head = head->next;
                delete tmp;
            }
        }
        void push_back(T data) {
            node<T>* tmp = new node<T>(data);
            ++sz;
            if (head == nullptr) {
                head = tail = tmp;
            } else {
                tail->next = tmp;
                tail = tail->next;
            }
        }
        iterator begin() {
            return iterator(head);
        }
        iterator end() {
            return iterator(nullptr);
        }
    private:
        node<T> *head, *tail;
        int sz;
};

template <typename T>
struct pv {
    pv(int _p=0, T _v=T()) : p(_p), v(_v) {}
    int p;
    T v;
};

template <typename T>
class priority_queue {
    public:
        priority_queue() : capa(const_max_sz), sz(0) {
            arr = new pv<T>[capa];
        }
        virtual ~priority_queue() {
            delete[] arr;
        }
        int push(int priority, T data) {
            pv<T> tmp(priority, data);

            if (sz == capa) {
                return const_err_code;
            }
            int i= sz++;

            arr[i] = tmp;
            while(i != 0 && arr[i].p < arr[parent(i)].p) {
                swap(arr[i], arr[parent(i)]);
                i = parent(i);
            }
            return 0;
        }
        int pop() {
            if (sz == 0) {
                return const_err_code;
            } else if (sz == 1) {
                --sz;
            } else {
                arr[0] = arr[sz-1];
                --sz;
                heapify(0);
            }
            return 0;
        }
        T& top() {
            return arr[0].v;
        }
        bool isEmpty() {
            return sz == 0;
        }
    private:
        int parent(int v) { return (v-1)/2; }
        int left(int v) { return v*2+1; }
        int right(int v) { return v*2+2; }
        void heapify(int v) {
            int l = left(v);
            int r = right(v);
            int smallest = v;
            if (l < sz && arr[l].p < arr[smallest].p) {
                smallest = l;
            }
            if (r < sz && arr[r].p < arr[smallest].p) {
                smallest = r;
            }
            if (smallest != v) {
                swap(arr[smallest], arr[v]);
                heapify(smallest);
            }
        }
        void swap(pv<T> &a, pv<T> &b) {
            pv<T> tmp = a;
            a = b;
            b = tmp;
        }

        int sz, capa;
        pv<T> *arr;
};

class graph {
    public:
        void init(int _cntV) {
            cntV = _cntV;
            adjlist = new xlist<vertex>[cntV];
        }
        virtual ~graph() {
            if (adjlist != nullptr) {
                delete[] adjlist;
            }
        }
        void addEdge(int src, int dest, int weight) {
            adjlist[src].push_back(vertex(dest, weight));
        }
        xlist<vertex> &operator[] (int idx) {
            return adjlist[idx];
        }
    private:
        int cntV;
        xlist<vertex> *adjlist;
};

class solver {
    public:
        solver() : ans(0) {
            scanf("%d", &N);
            scanf("%d", &M);
            g.init(N+1);
            dist = new int[N+1];
            sptSet = new bool[N+1];
            //init
            for(int i=0; i<N+1; ++i) {
                dist[i] = INF;
                sptSet[i] = false;
            }

            int src, dest, w;
            for(int i=0; i<M; ++i) {
                scanf("%d %d %d", &src, &dest, &w);
                g.addEdge(src, dest, w);
            }

            scanf("%d %d", &SRC, &DEST);
        }
        virtual ~solver() {
            delete[] dist;
            delete[] sptSet;
        }
        int run() {
            dijkstra(SRC, DEST);
            return ans;
        }
        void dijkstra(int s, int d) {
            priority_queue<int> pq;
            dist[s] = 0;
            pq.push(0, s);

            while(!pq.isEmpty()) {
                int u = pq.top();
                pq.pop();

                sptSet[u] = true;
                //visit neighbors of u
                xlist<vertex>::iterator _end = g[u].end();
                for(xlist<vertex>::iterator it = g[u].begin(); it != _end; ++it) {
                    int v = (*it).v;
                    int w = (*it).w;
                    if (sptSet[v] == false && dist[u] != INF && dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        pq.push(dist[v], v);
                    }
                }
            }
            ans = dist[d];
        }
    private:
        graph g;
        int ans;
        int N, M, SRC, DEST;
        int *dist;
        bool *sptSet;
};

void solve() {
    solver sol;
    int ans = 0;
    ans = sol.run();
    printf("%d\n", ans);
}

int main() {
#ifdef DBG_STDIN
    freopen("inputs/acmicpc_1916_input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
