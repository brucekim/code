/* 0 empty, 1 wall, 2 virus 
 * n(row) x m(col)
 * no. of new walls to be built: 3
 * virus can pollute to up/down/left and right
 * given map , find max. size of safety zone with best construction of 3 walls
 *
 * design:
 * 1. dfs for possible permutation regarding virus given to map
 * 2. once building up 3 walls in possible permutation, start bfs for polluting empty zones
 * 3. get the size of safety zone after step. 2
 * 4. repeat from step 1 till exhausting all possible permutation
 *
 * required ds: stack, queue, list
 *
 * */
#include <cstdio>

const int empty = 0;
const int wall = 1;
const int virus = 2;
const int max_map = 8;

template <typename T>
struct node {
    node(T _data) : data(_data), prev(nullptr), next(nullptr) {}
    T data;
    node<T> *prev;
    node<T> *next;
};

template <typename T>
class xlist_iterator {
    public:
        xlist_iterator(node<T> *it) : current(it) {}
        xlist_iterator<T>& operator++() {
            current = current->next;
            return *this;
        }
        T& operator*() {
            return current->data;
        }
        bool operator!=(const xlist_iterator<T> &it) {
            return current != it.current;
        }
        bool operator==(const xlist_iterator<T> &it) {
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
            node<T> *tmp = new node<T>(data);
            ++sz;
            if (head == nullptr) {
                head = tail = tmp;
            } else {
                tail->next = tmp;
                tmp->prev = tail;
                tail = tail->next;
            }
        }
        void pop() {
            if (tail != nullptr) {
                node<T> * tmp = tail;
                tail = tail->prev;
                if (tail != nullptr) {
                    tail->next = nullptr;
                } else {
                    head = nullptr;
                }
                delete tmp;
                --sz;
            }
        }
        void pop_front() {
            if (head != nullptr) {
                node<T>* tmp = head;
                head = head->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                } else {
                    tail = nullptr;
                }
                delete tmp;
                --sz;
            }
        }
        T& top() {
            if (tail == nullptr) {
                printf("empty top\n");
                return err_code;
            } else {
                return tail->data;
            }
        }
        bool isEmpty() {
            return sz == 0;
        }

    private:
        int sz;
        T err_code = static_cast<T>(0xFFFFFFFF);
        node<T> *head;
        node<T> *tail;
};

template <typename T>
class xstack : public xlist<T>{
    public:

};

template <typename T>
class xqueue : public xlist<T> {
    public:
        void enq(T data) {
            this->push_back(data);
        }
        void deq() {
            this->pop_front();
        }
};

void solve() {
    int n, m;
    int arr[max_map][max_map]{0};
    scanf("%d", &n);
    scanf("%d", &m);
    for(int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            scanf("%d", &arr[i][j]);
        }
    }
}

int main() {
    solve();
    return 0;
}

