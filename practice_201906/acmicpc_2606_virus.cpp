#include <cstdio>
//#define DBG_STDIN
//#define DBG

#ifdef DBG
#define dbg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg(fmt, ...)
#endif

const static int const_err_code = 0x3f3f3f3f;

template <typename T>
struct node {
    node(T _data) : data(_data), next(nullptr) {}
    T data;
    node<T> *next;
};
template <typename T>
class xqueue {
    public:
    xqueue() : sz(0), head(nullptr), tail(nullptr) {}
    virtual ~xqueue() {
        while(head) {
            node<T> *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    int push_back(T data) {
        node<T> *tmp = new node<T>(data);
        ++sz;
        if (head == nullptr) {
            head = tail = tmp;
        } else {
            tail->next = tmp;
            tail = tail->next;
        }
        return 0;
    }
    int pop_front() {
        if (head == nullptr) {
            return const_err_code;
        } else {
            node<T> *tmp = head;
            head = head->next;
            delete tmp;
            --sz;
        }
        return 0;
    }
    const T& getFront() {
        return head->data;
    }
    bool isEmpty() {
        return sz == 0;
    }
    int getSize() {
        return sz;
    }
    private:
    node<T> *head;
    node<T> *tail;
    int sz;
};
class solver {
    public:
    solver() {
        scanf("%d", &cntV);
        scanf("%d", &cntE);

        int sz = (cntV+1)*(cntV+1);
        arr = new bool[sz];
        visited = new bool[cntV+1];

        for(int i=0; i<sz; ++i) {
            arr[i] = 0;
        }
        for(int i=0; i<=cntV; ++i) {
            visited[i] = false;
        }
        for(int i=0; i<cntE; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            arr[idx(u, v)] = true;
            arr[idx(v, u)] = true;
        }
    }
    virtual ~solver() {
        delete[] arr;
        delete[] visited;
    }
    void info() {
        dbg("map..v(%d) e(%d)\n", cntV, cntE);
        for(int i=0; i<=cntV; ++i) {
            for(int j=0; j<=cntV; ++j) {
                dbg("%d ", arr[idx(i, j)]);
            }
            dbg("\n");
        }
    }
    int idx(int u, int v) {
        return u*(cntV+1) + v;
    }
    int run() {
        int ans = 0;
        visited[1] = true;
        q.push_back(1);

        while(!q.isEmpty()) {
            int t = q.getFront();
            q.pop_front();
            dbg("pop %d\n", t);
            for(int i=1; i<=cntV; ++i) {
                if (arr[idx(t, i)] == true && visited[i] == false) {
                    dbg("visited %d\n", i);
                    visited[i] = true;
                    q.push_back(i);
                    ++ans;
                }
            }
        }
        return ans;
    }
    private:
    int cntV, cntE;
    bool *arr;
    bool *visited;
    xqueue<int> q;
};
void solve() {
    solver sol;
    int ans = 0;
    ans = sol.run();
    printf("%d\n", ans);
}
int main() {
#ifdef DBG_STDIN
    freopen("inputs/acmicpc_2606_input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
