/* 
https://www.acmicpc.net/problem/7569
*/
#include <cstdio>

struct tomato {
    tomato(int _x, int _y) : x(_x), y(_y) {}
    int x;
    int y;
};

template <typename T>
struct node {
    node(T _data) : data(_data), next(nullptr) {}
    T data;
    node *next;
};

template <typename T>
class xqueue {
    public:
    xqueue() : sz(0), head(nullptr), tail(nullptr) {}
    virtual ~xqueue() {
        while(head != nullptr) {
            node<T>* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    void enq(T data) {
        node<T>* tmp = new node<T>(data);
        ++sz;
        if (head == nullptr) {
            head = tail = tmp;
        } else {
            tail->next = tmp;
            tail = tail->next;
        }
    }
    void deq() {
        if (head != nullptr) {
            node<T> *tmp = head;
            head = head->next;
            delete tmp;
            --sz;
        }
    }
    bool isEmpty() {
        return sz == 0;
    }
    int getSize() {
        return sz;
    }

    T& front() {
        return head->data;
    }
    private:
    int sz;
    node<T>* head;
    node<T>* tail;
};

void solve() {
    const int max_len = 1000;
    int m, n, k;
    int arr[max_len][max_len]{0};
    int fresh = 0;
    xqueue<tomato> q;

    /* input */
    scanf("%d %d", &m, &n);

    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            scanf("%d", &k);
            arr[j][i] = k;
            if (k == 1) {
                q.enq(tomato(j, i));
            } else if (k == 0) {
                ++fresh;
            }
        }
    }
    if (fresh == 0) {
        printf("0");
        return;
    }

    int lx[] = {-1, 1, 0, 0};
    int ly[] = {0, 0, -1, 1};
    auto valid_boundary = [](int x, int y, int m, int n) -> bool {
        if ((x >= 0 && x < m) && (y >=0 && y < n)) {
            return true;
        } else {
            return false;
        }
    };

    int max = 0;

    while(q.isEmpty() != true) {
        tomato t = q.front();
        q.deq();
        /* find fresh -> mark old */
        for (int i=0; i<4; ++i) {
            int x = t.x + lx[i];
            int y= t.y + ly[i];
            if(valid_boundary(x, y, m, n) == true) {
                if (arr[x][y] == 0) {
                    arr[x][y] = arr[t.x][t.y] + 1;
                    q.enq(tomato(x, y));
                    --fresh;
                    if (max < arr[x][y]) {
                        max = arr[x][y];
                    }
                }
            }
        }
    }

    int ans = fresh != 0 ? -1 : max -1;
    printf("%d\n", ans);

    /*
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            printf("%d ", arr[j][i]);
        }
        printf("\n");
    }
    */
}

int main() {
    freopen("inputs/acmicpc_7576_tomato_input.txt", "r", stdin);
    solve();
    return 0;
}
