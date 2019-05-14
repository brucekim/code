/* given n, m
 *
 * find non-duplicated 'm' numbers from 1 to n natural number.
 * 
 * 1 <= m <= n <= 8
 * printf permutation in increasing order
 */

#include <cstdio>

template <typename T>
struct node {
    node(int _data) : data(_data), prev(nullptr), next(nullptr) {}
    T data;
    node<T> *next;
    node<T> *prev;
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
        bool operator !=(const xlist_iterator<T> &it) {
            return current != it.current;
        }
        bool operator ==(const xlist_iterator<T> &it) {
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
        T top() const {
            if (tail != nullptr) {
                return tail->data;
            } else {
                return err_code;
            }
        }
        T front() const {
            if (tail != nullptr) {
                return tail->data;
            } else {
                return err_code;
            }
        }
        void push_back(T data) {
            node<T> *tmp = new node<T>(data);
            ++sz;
            if (tail == nullptr) {
                head = tail = tmp;
            } else {
                tail->next = tmp;
                tmp->prev = tail;
                tail = tail->next;
            }
        }
        void pop_back() {
            if (tail != nullptr) {
                node<T> *tmp = tail;
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
        void push_front(T data) {
            node<T> *tmp = new node<T>(data);
            ++sz;
            if (head == nullptr) {
                head = tail = tmp;
            } else {
                head->prev = tmp;
                tmp->next = head;
                head = head->prev;
            }
        }
        void pop_front() {
            if (head != nullptr) {
                node<T> *tmp = head;
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
        bool isEmpty() {
            return sz == 0;
        }
        int getSize() {
            return sz;
        }
        iterator begin() {
            return iterator(head);
        }
        iterator end() {
            return iterator(nullptr);
        }
    private:
        node<T> *head;
        node<T> *tail;
        int sz;
        int err_code = static_cast<T>(0x3f3f3f3f);
};


class permu {
    public:
        permu(int _n, int _m) : n(_n), m(_m) {
            visited = new bool[n]{false};
        }

        virtual ~permu() {
            delete[] visited;
        }

        void dfs() {

            if (stack.getSize() == m) {
                const xlist<int>::iterator end = stack.end();
                for (xlist<int>::iterator it = stack.begin(); it != end; ++it) {
                    printf("%d ", *it);
                }
                printf("\n");
            }

            for(int i=1; i<=n; ++i) {
                if (visited[i] != true) {
                    stack.push_back(i);
                    visited[i] = true;
                    dfs();
                    visited[i] = false;
                    stack.pop_back();
                }
            }
        }
    private:
        int m, n;
        bool *visited;
        xlist<int> stack;
};

void solve() {
    int n, m;
    
    scanf("%d", &n);
    scanf("%d", &m);

    permu p(n, m);
    p.dfs();

}

int main() {
    solve();
    return 0;
}
