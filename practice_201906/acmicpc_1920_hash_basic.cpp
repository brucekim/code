#include <stdio.h>

#define DBG_STDIN
//#define DBG

#ifdef DBG
#define dbg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define dbg(fmt, ...)
#endif

const static int const_max_sz = 100000;

template <typename T>
struct node {
    node(T _data) : data(_data), next(nullptr) {}
    T data;
    node<T> *next;
};

template <typename T>
class xlist {
    public:
    xlist() : head(nullptr), tail(nullptr), sz(0) {}
    virtual ~xlist() {
        while(head) {
            node<T>* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    bool push_back(T data) {
        if (head == nullptr) {
            node<T> *tmp = new node<T>(data);
            head = tail = tmp;
            ++sz;
        } else {
            node<T> *tmp = head;
            while(tmp) {
                if (tmp->data == data) {
                    return false;
                }
                tmp = tmp->next;
            }
            tmp = new node<T>(data);
            tail->next = tmp;
            tail = tail->next;
            ++sz;
        }
        return true;
    }
    bool has(T data) {
        if (sz == 0) {
            return false;
        }
        node<T> *tmp = head;
        while (tmp) {
            if (tmp->data == data) {
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

   private:
    node<T> *head;
    node<T> *tail;
    int sz;
};
class hashtable {
   public:
    hashtable() : capa(const_max_sz*3), sz(0) {
        arr = new xlist<int>[capa];
    }
    virtual ~hashtable() {
        delete[] arr;
    }

    void insert(int data) {
        int idx = hashval(data);
        if (arr[idx].push_back(data) == true) {
            ++sz;
            dbg("inserted (hashval:%d) %d\n", idx, data);
        }
    }
    bool find(int data) {
        int idx = hashval(data);
        dbg("find (hashval:%d) %d\n", idx, data);
        return arr[idx].has(data);
    }

   private:
    int hashval(int data) {
        if (data < 0) {
            data = data * -1;
        }
        unsigned int tmp = (data * 12345)%capa;
        return (tmp * 54321)%capa;
    }
    xlist<int> *arr;
    int capa, sz;
};

void solve() {
    int N, M, tmp;
    hashtable ht;
    scanf("%d", &N);
    for(int i=0; i<N; ++i) {
        scanf("%d", &tmp);
        ht.insert(tmp);
    }
    scanf("%d", &M);
    for(int i=0; i<M; ++i) {
        scanf("%d", &tmp);
        printf("%d\n", ht.find(tmp) == true ? 1 : 0);
    }
}
int main() {
#ifdef DBG_STDIN
    freopen("inputs/acmicpc_1920_input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
